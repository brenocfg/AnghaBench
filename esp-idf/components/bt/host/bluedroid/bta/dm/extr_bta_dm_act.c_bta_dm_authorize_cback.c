#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t service; scalar_t__* bd_name; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bd_addr; } ;
struct TYPE_6__ {TYPE_1__ authorize; } ;
typedef  TYPE_2__ tBTA_DM_SEC ;
typedef  size_t UINT8 ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_sec_cback ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  DEV_CLASS ;
typedef  size_t* BOOLEAN ;
typedef  scalar_t__ BD_NAME ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_STRNCPY_S (char*,int,char*,int) ; 
 int BD_NAME_LEN ; 
 int /*<<< orphan*/  BTA_DM_AUTHORIZE_EVT ; 
 size_t BTA_FIRST_JV_SERVICE_ID ; 
 size_t BTA_LAST_JV_SERVICE_ID ; 
 size_t BTA_MAX_SERVICE_ID ; 
 size_t BTM_CMD_STARTED ; 
 size_t BTM_NOT_AUTHORIZED ; 
 int /*<<< orphan*/  DEV_CLASS_LEN ; 
 int /*<<< orphan*/  UNUSED (size_t*) ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ bta_dm_cb ; 
 size_t* bta_service_id_to_btm_srv_id_lkup_tbl ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static UINT8 bta_dm_authorize_cback (BD_ADDR bd_addr, DEV_CLASS dev_class, BD_NAME bd_name,
                                     UINT8 *service_name, UINT8 service_id, BOOLEAN is_originator)
{
    tBTA_DM_SEC sec_event;
    UINT8       index = 1;
    UNUSED(service_name);
    UNUSED(is_originator);

    bdcpy(sec_event.authorize.bd_addr, bd_addr);
    memcpy(sec_event.authorize.dev_class, dev_class, DEV_CLASS_LEN);

    BCM_STRNCPY_S((char *)sec_event.authorize.bd_name, sizeof(BD_NAME), (char *)bd_name, (BD_NAME_LEN - 1));

    /* make sure the string is null terminated */
    sec_event.authorize.bd_name[BD_NAME_LEN - 1] = 0;

#if ( defined(BTA_JV_INCLUDED) && BTA_JV_INCLUDED == TRUE )
    sec_event.authorize.service = service_id;
#endif

    while (index < BTA_MAX_SERVICE_ID) {
        /* get the BTA service id corresponding to BTM id */
        if (bta_service_id_to_btm_srv_id_lkup_tbl[index] == service_id) {
            sec_event.authorize.service = index;
            break;
        }
        index++;
    }


    /* if supported service callback otherwise not authorized */
    if (bta_dm_cb.p_sec_cback && (index < BTA_MAX_SERVICE_ID
#if ( defined(BTA_JV_INCLUDED) && BTA_JV_INCLUDED == TRUE )
                                  /* pass through JV service ID */
                                  || (service_id >= BTA_FIRST_JV_SERVICE_ID && service_id <= BTA_LAST_JV_SERVICE_ID)
#endif
                                 )) {
        bta_dm_cb.p_sec_cback(BTA_DM_AUTHORIZE_EVT, &sec_event);
        return BTM_CMD_STARTED;
    } else {
        return BTM_NOT_AUTHORIZED;
    }
}