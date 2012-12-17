//
//  CSAPI+Clients.h
//  CreateSend
//
//  Copyright (c) 2012 Freshview Pty Ltd. All rights reserved.
//

#import "CSAPI.h"
#import "CSClient.h"
#import "CSCampaign.h"
#import "CSPerson.h"
#import "CSSuppressedRecipient.h"
#import "CSTemplate.h"
#import "CSPaginatedResult.h"

/**
 Client-related APIs. See CSAPI for documentation of the other API categories.
 */
@interface CSAPI (Clients)

/**
 Create a new client in your account with basic information and no access to the application.
 
 http://www.campaignmonitor.com/api/clients/#creating_a_client
 
 @param companyName Company name of the new client
 @param contactName Contact name of the new client
 @param emailAddress Primary email address of the new client
 @param country Country (see getCountries:errorHandler:)
 @param timezone Timezone (see getTimezones:errorHandler:)
 @param completionHandler Completion callback, with ID of the successfully created client as the only argument
 @param errorHandler Error callback
 */
- (void)createClientWithCompanyName:(NSString *)companyName
                        contactName:(NSString *)contactName
                       emailAddress:(NSString *)emailAddress
                            country:(NSString *)country
                           timezone:(NSString *)timezone
                  completionHandler:(void (^)(NSString *clientID))completionHandler
                       errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Update the basic account details for an existing client in your account.
 
 http://www.campaignmonitor.com/api/clients/#setting_basic_details
 
 @param clientID The ID of the client for which basic details should be set
 @param companyName Company name of the client
 @param contactName Contact name of the client
 @param emailAddress Primary email address of the client
 @param country Country (see getCountries:errorHandler:)
 @param timezone Timezone (see getTimezones:errorHandler:)
 @param completionHandler Completion callback
 @param errorHandler Error callback
 */
- (void)updateClientWithClientID:(NSString *)clientID
                     companyName:(NSString *)companyName
                     contactName:(NSString *)contactName
                    emailAddress:(NSString *)emailAddress
                         country:(NSString *)country
                        timezone:(NSString *)timezone
               completionHandler:(void (^)(void))completionHandler
                    errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Delete an existing client from your account.
 
 http://www.campaignmonitor.com/api/clients/#deleting_a_client
 
 @param clientID The ID of the client to be deleted
 @param completionHandler Completion callback
 @param errorHandler Error callback
 */
- (void)deleteClientWithID:(NSString *)clientID
         completionHandler:(void (^)(void))completionHandler
              errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Set if a client can pay for their own campaigns and design and spam tests using
 our PAYG billing. Set the mark-up percentage on each type of fee, and if the
 client can purchase their own email credits to access bulk discounts.
 
 http://www.campaignmonitor.com/api/clients/#setting_payg_billing
 
 @param clientID The ID of the client for which PAYG billing settings should be set
 @param currency The currency to bill in. Values accepted are:
 
 - `USD` (US Dollars)
 - `GBP` (Great Britain Pounds)
 - `EUR` (Euros)
 - `CAD` (Canadian Dollars)
 - `AUD` (Australian Dollars)
 - `NZD` (New Zealand Dollars)
 
 @param canPurchaseCredits Whether or not the client can purchase their own email credits to access bulk discounts
 @param clientPays Whether or not the client can pay for their own campaigns and design and spam tests
 @param markupPercentage Markup as a percentage
 @param markupOnDelivery Markup in the major unit for the specified currency (e.g. `6.5f` means $6.50)
 @param markupPerRecipient Markup in the minor unit for the specified currency (e.g. `6.5f` means 6.5 cents)
 @param markupOnDesignSpamTest Markup in the major unit for the specified currency (e.g. `6.5f` means $6.50)
 @param completionHandler Completion callback
 @param errorHandler Error callback
 */
- (void)setClientPAYGBillingSettingsWithClientID:(NSString *)clientID
                                        currency:(NSString *)currency
                              canPurchaseCredits:(BOOL)canPurchaseCredits
                                      clientPays:(BOOL)clientPays
                                markupPercentage:(float)markupPercentage
                                markupOnDelivery:(float)markupOnDelivery
                              markupPerRecipient:(float)markupPerRecipient
                          markupOnDesignSpamTest:(float)markupOnDesignSpamTest
                               completionHandler:(void (^)(void))completionHandler
                                    errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Set if a client can pay for their own campaigns and design and spam tests using
 our monthly billing. Set the currency they should pay in plus mark-up
 percentage that will apply to the base prices at each pricing tier.
 
 http://www.campaignmonitor.com/api/clients/#setting_monthly_billing
 
 @param clientID The ID of the client for which monthly billing settings should be set
 @param currency The currency to bill in. Values accepted are:
 
 - `USD` (US Dollars)
 - `GBP` (Great Britain Pounds)
 - `EUR` (Euros)
 - `CAD` (Canadian Dollars)
 - `AUD` (Australian Dollars)
 - `NZD` (New Zealand Dollars)
 
 @param clientPays Whether or not the client can pay for their own campaigns and design and spam tests
 @param markupPercentage Markup as a percentage
 @param completionHandler Completion callback
 @param errorHandler Error callback
 */
- (void)setClientMonthlyBillingWithClientID:(NSString *)clientID
                                   currency:(NSString *)currency
                                 clientPays:(BOOL)clientPays
                           markupPercentage:(float)markupPercentage
                          completionHandler:(void (^)(void))completionHandler
                               errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Get the complete details for a client including their API key, access level,
 contact details and billing settings.
 
 http://www.campaignmonitor.com/api/clients/#client_details
 
 @param clientID The ID of the client to be retrieved
 @param completionHandler Completion callback, with a `CSClient` object as the first and only argument
 @param errorHandler Error callback
 */
- (void)getClientDetailsWithClientID:(NSString *)clientID
                   completionHandler:(void (^)(CSClient *client))completionHandler
                        errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Get a list of all sent campaigns for a client.
 
 http://www.campaignmonitor.com/api/clients/#sent_campaigns
 
 @param clientID The ID of the client for which sent campaigns should be retrieved
 @param completionHandler Completion callback, with an array of `CSCampaign` objects as the first and only argument.
 @param errorHandler Error callback
 */
- (void)getSentCampaignsWithClientID:(NSString *)clientID
                   completionHandler:(void (^)(NSArray *campaigns))completionHandler
                        errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Get a list of all currently scheduled campaigns for a client.
 
 http://www.campaignmonitor.com/api/clients/#scheduled_campaigns
 
 @param clientID The ID of the client for which scheduled campaigns should be retrieved
 @param completionHandler Completion callback, with an array of `CSCampaign` objects as the first and only argument.
 @param errorHandler Error callback
 */
- (void)getScheduledCampaignsWithClientID:(NSString *)clientID
                        completionHandler:(void (^)(NSArray *campaigns))completionHandler
                             errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Get a list of all draft campaigns belonging to a client.
 
 http://www.campaignmonitor.com/api/clients/#draft_campaigns
 
 @param clientID The ID of the client for which draft campaigns should be retrieved
 @param completionHandler Completion callback, with an array of `CSCampaign` objects as the first and only argument.
 @param errorHandler Error callback
 */
- (void)getDraftCampaignsWithClientID:(NSString *)clientID
                    completionHandler:(void (^)(NSArray *campaigns))completionHandler
                         errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Get all the subscriber lists that belong to a client.
 
 http://www.campaignmonitor.com/api/clients/#subscriber_lists
 
 @param clientID The ID of the client for which subscriber lists should be retrieved
 @param completionHandler Completion callback, with an array of `CSList` objects as the first and only argument
 @param errorHandler Error callback
 */
- (void)getSubscriberListsWithClientID:(NSString *)clientID
                     completionHandler:(void (^)(NSArray *subscriberLists))completionHandler
                          errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Get a paged result representing the client's suppression list.
 
 http://www.campaignmonitor.com/api/clients/#suppression_list
 
 @param clientID The ID of the client for which the suppression list should be retrieved
 @param page The page to retrieve
 @param pageSize The number of records to retrieve per page. Values accepted are between `10` and `1000`.
 @param orderField The field which should be used to order the result. Values accepted are `email`, `name` or `date`.
 @param ascending Whether to sort the list (see `orderField`) in ascending order
 @param completionHandler Completion callback, with a `CSPaginatedResult` as the first and only argument. Items in the result list are `CSSuppressedRecipient`
 @param errorHandler Error callback
 */
- (void)getSuppressionListWithClientID:(NSString *)clientID
                                  page:(NSUInteger)page
                              pageSize:(NSUInteger)pageSize
                            orderField:(NSString *)orderField
                             ascending:(BOOL)ascending
                     completionHandler:(void (^)(CSPaginatedResult *paginatedResult))completionHandler
                          errorHandler:(CSAPIErrorHandler)errorHandler;


/**
 Get a list of all segments belonging to a particular client.
 
 http://www.campaignmonitor.com/api/clients/#segments
 
 @param clientID The ID of the client for which segments should be retrieved
 @param completionHandler Completion callback, with an array of `CSSegment` objects as the first and only argument
 @param errorHandler Error callback
 */
- (void)getSegmentsWithClientID:(NSString *)clientID
              completionHandler:(void (^)(NSArray *segments))completionHandler
                   errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Get a list of all templates belonging to a particular client.
 
 http://www.campaignmonitor.com/api/clients/#templates
 
 @param clientID The ID of the client for which templates should be retrieved
 @param completionHandler Completion callback, with an array of `CSTemplate` objects as the first and only argument
 @param errorHandler Error callback
 */
- (void)getTemplatesWithClientID:(NSString *)clientID
               completionHandler:(void (^)(NSArray *templates))completionHandler
                    errorHandler:(CSAPIErrorHandler)errorHandler;


/**
 Adds a new person to the client with the specified access.
 
 http://www.campaignmonitor.com/api/clients/#adding_a_person
 
 @param clientID The ID of the client to add the person to
 @param name Name of the person
 @param emailAddress Primary email address of the person
 @param password Optional password for the person
 @param accessLevel Access level as per documentation listed in discussion
 @param completionHandler Completion callback, with email address of the successfully added person as the only argument
 @param errorHandler Error callback
 */
- (void)addPersonWithClientID:(NSString *)clientID
                         name:(NSString *)name
                 emailAddress:(NSString *)emailAddress
                     password:(NSString *)password
                  accessLevel:(NSUInteger)accessLevel
            completionHandler:(void (^)(NSString *personEmailAddress))completionHandler
                 errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Updates any aspect of a person including their email address, name and access level.
 
 http://www.campaignmonitor.com/api/clients/#updating_a_person
 
 @param clientID The ID of the client to add the person to
 @param name Name of the person
 @param currentEmailAddress Existing email address of the person
 @param newEmailAddress New email address of the person
 @param password Optional password for the person
 @param accessLevel Access level as per documentation listed in discussion
 @param completionHandler Completion callback, with email address of the successfully added person as the only argument
 @param errorHandler Error callback
 */
- (void)updatePersonWithClientID:(NSString *)clientID
                            name:(NSString *)name
             currentEmailAddress:(NSString *)currentEmailAddress
                 newEmailAddress:(NSString *)newEmailAddress
                        password:(NSString *)password
                     accessLevel:(NSUInteger)accessLevel
               completionHandler:(void (^)(NSString *personEmailAddress))completionHandler
                    errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Get all the (active or invited) people associated with a particular client
 
 http://www.campaignmonitor.com/api/clients/#getting_client_people
 
 @param clientID The ID of the client for which the people should be retrieved
 @param completionHandler Completion callback, with an array of `CSPerson` objects as the first and only argument
 @param errorHandler Error callback
 */
- (void)getPeopleWithClientID:(NSString *)clientID completionHandler:(void (^)(NSArray *people))completionHandler errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Returns the details of a single person associated with a client.
 
 http://www.campaignmonitor.com/api/clients/#getting_client_person
 
 @param clientID The ID of the client for which the person details should be retrieved
 @param emailAddress The email address of the person whose information should be retrieved.
 @param completionHandler Completion callback, with a `CSPerson` as the only argument.
 @param errorHandler Error callback
 */
- (void)getPersonDetailsWithClientID:(NSString *)clientID emailAddress:(NSString *)emailAddress completionHandler:(void (^)(CSPerson *person))completionHandler errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Changes the status of an active person to a deleted person. They will no longer be able to log into this client.
 
 http://www.campaignmonitor.com/api/clients/#deleting_a_person
 
 @param clientID The ID of the client for which the person details should be deleted.
 @param emailAddress The email address of the person to be deleted.
 @param completionHandler Completion callback
 @param errorHandler Error callback
 */
- (void)deletePersonWithClientID:(NSString *)clientID emailAddress:(NSString *)emailAddress completionHandler:(void (^)(void))completionHandler errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Sets the primary contact for the client to be the person with the specified email address.
 
 http://www.campaignmonitor.com/api/clients/#setting_primary_contact
 
 @param clientID The ID of the client for which the primary contact is to be set.
 @param emailAddress The email address of the person to be assigned as the primary contact for the client.
 @param completionHandler Completion callback, with email address of the primary contact as the only argument
 @param errorHandler Error callback
 */
- (void)setPrimaryContactWithClientID:(NSString *)clientID emailAddress:(NSString *)emailAddress completionHandler:(void (^)(NSString *primaryContactEmailAddress))completionHandler errorHandler:(CSAPIErrorHandler)errorHandler;

/**
 Returns the email address of the person who is selected as the primary contact for this client.
 
 http://www.campaignmonitor.com/api/clients/#getting_primary_contact
 
 @param clientID The ID of the client for which the primary contact is to be set.
 @param completionHandler Completion callback, with email address of the primary contact as the only argument
 @param errorHandler Error callback
 */
- (void)getPrimaryContactWithClientID:(NSString *)clientID completionHandler:(void (^)(NSString *primaryContactEmailAddress))completionHandler errorHandler:(CSAPIErrorHandler)errorHandler;

@end