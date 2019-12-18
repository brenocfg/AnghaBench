#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSDP_UUID ;
typedef  int /*<<< orphan*/  tBTA_DM_SEARCH_CBACK ;
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/ * p_uuid; scalar_t__ num_uuid; int /*<<< orphan*/  sdp_search; int /*<<< orphan*/ * p_cback; int /*<<< orphan*/  services; int /*<<< orphan*/  bd_addr; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_DISCOVER ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_DISCOVER_EVT ; 
 int /*<<< orphan*/  BTA_USER_SERVICE_MASK ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmDiscoverUUID(BD_ADDR bd_addr, tSDP_UUID *uuid,
                        tBTA_DM_SEARCH_CBACK *p_cback, BOOLEAN sdp_search)
{
    tBTA_DM_API_DISCOVER    *p_msg;

    if ((p_msg = (tBTA_DM_API_DISCOVER *) osi_malloc(sizeof(tBTA_DM_API_DISCOVER))) != NULL) {
        p_msg->hdr.event = BTA_DM_API_DISCOVER_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->services = BTA_USER_SERVICE_MASK; //Not exposed at API level
        p_msg->p_cback = p_cback;
        p_msg->sdp_search = sdp_search;

#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
        p_msg->num_uuid = 0;
        p_msg->p_uuid = NULL;
#endif
        memcpy( &p_msg->uuid, uuid, sizeof(tSDP_UUID) );
        bta_sys_sendmsg(p_msg);
    }
}