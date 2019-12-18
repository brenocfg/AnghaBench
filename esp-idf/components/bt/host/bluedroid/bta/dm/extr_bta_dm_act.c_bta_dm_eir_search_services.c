#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * remote_bd_addr; } ;
typedef  TYPE_1__ tBTM_INQ_RESULTS ;
typedef  scalar_t__ tBTM_EIR_SEARCH_RESULT ;
typedef  int tBTA_SERVICE_MASK ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int,...) ; 
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*,int,int) ; 
 int BTA_MAX_SERVICE_ID ; 
 scalar_t__ BTA_SERVICE_ID_TO_SERVICE_MASK (int) ; 
 scalar_t__ BTM_EIR_FOUND ; 
 scalar_t__ BTM_EIR_NOT_FOUND ; 
 scalar_t__ BTM_HasInquiryEirService (TYPE_1__*,scalar_t__) ; 
 scalar_t__ UUID_SERVCLASS_HEADSET ; 
 scalar_t__ UUID_SERVCLASS_HEADSET_HS ; 
 scalar_t__ UUID_SERVCLASS_PNP_INFORMATION ; 
 scalar_t__* bta_service_id_to_uuid_lkup_tbl ; 

__attribute__((used)) static void bta_dm_eir_search_services( tBTM_INQ_RESULTS  *p_result,
                                        tBTA_SERVICE_MASK *p_services_to_search,
                                        tBTA_SERVICE_MASK *p_services_found)
{
    tBTA_SERVICE_MASK       service_index = 0;
    tBTM_EIR_SEARCH_RESULT  result;

    APPL_TRACE_DEBUG("BTA searching services in EIR of BDA:0x%02X%02X%02X%02X%02X%02X",
                     p_result->remote_bd_addr[0], p_result->remote_bd_addr[1],
                     p_result->remote_bd_addr[2], p_result->remote_bd_addr[3],
                     p_result->remote_bd_addr[4], p_result->remote_bd_addr[5]);

    APPL_TRACE_DEBUG("    with services_to_search=0x%08X", *p_services_to_search);

#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
    /* always do GATT based service discovery by SDP instead of from EIR    */
    /* if GATT based service is also to be put in EIR, need to modify this  */
    while (service_index < (BTA_MAX_SERVICE_ID - 1))
#else
    while (service_index < BTA_MAX_SERVICE_ID)
#endif
    {
        if ( *p_services_to_search
                & (tBTA_SERVICE_MASK)(BTA_SERVICE_ID_TO_SERVICE_MASK(service_index))) {
            result = BTM_HasInquiryEirService( p_result,
                                               bta_service_id_to_uuid_lkup_tbl[service_index] );

            /* Searching for HSP v1.2 only device */
            if ((result != BTM_EIR_FOUND) &&
                    (bta_service_id_to_uuid_lkup_tbl[service_index] == UUID_SERVCLASS_HEADSET)) {
                result = BTM_HasInquiryEirService (p_result, UUID_SERVCLASS_HEADSET_HS);
            }

            if ( result == BTM_EIR_FOUND ) {
                /* If Plug and Play service record, need to check to see if Broadcom stack */
                /* However, EIR data doesn't have EXT_BRCM_VERSION so just skip it */
                if ( bta_service_id_to_uuid_lkup_tbl[service_index]
                        != UUID_SERVCLASS_PNP_INFORMATION ) {

                    *p_services_found |=
                        (tBTA_SERVICE_MASK)(BTA_SERVICE_ID_TO_SERVICE_MASK(service_index));
                    /* remove the service from services to be searched  */
                    *p_services_to_search &=
                        (tBTA_SERVICE_MASK)(~(BTA_SERVICE_ID_TO_SERVICE_MASK(service_index)));
                }
            } else if ( result == BTM_EIR_NOT_FOUND ) {
                /* remove the service from services to be searched  */
                *p_services_to_search &=
                    (tBTA_SERVICE_MASK)(~(BTA_SERVICE_ID_TO_SERVICE_MASK(service_index)));
            }
        }

        service_index++;
    }

    APPL_TRACE_ERROR("BTA EIR search result, services_to_search=0x%08X, services_found=0x%08X",
                     *p_services_to_search, *p_services_found);
}