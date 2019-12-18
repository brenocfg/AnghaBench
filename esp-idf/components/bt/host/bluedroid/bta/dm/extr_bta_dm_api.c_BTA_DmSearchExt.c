#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBT_UUID ;
struct TYPE_14__ {int num_uuid; struct TYPE_14__* p_uuid; int /*<<< orphan*/  srvc_mask; } ;
typedef  TYPE_2__ tBTA_SERVICE_MASK_EXT ;
typedef  TYPE_2__ tBTA_DM_SEARCH_CBACK ;
typedef  TYPE_2__ tBTA_DM_INQ ;
struct TYPE_13__ {int /*<<< orphan*/  event; } ;
struct TYPE_15__ {int num_uuid; int /*<<< orphan*/ * p_uuid; int /*<<< orphan*/  services; int /*<<< orphan*/  rs_res; TYPE_2__* p_cback; int /*<<< orphan*/  inq_params; TYPE_1__ hdr; } ;
typedef  TYPE_5__ tBTA_DM_API_SEARCH ;
typedef  int UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_SEARCH_EVT ; 
 int /*<<< orphan*/  BTA_DM_RS_NONE ; 
 int /*<<< orphan*/  UNUSED (TYPE_2__*) ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmSearchExt(tBTA_DM_INQ *p_dm_inq, tBTA_SERVICE_MASK_EXT *p_services, tBTA_DM_SEARCH_CBACK *p_cback)
{
#if BLE_INCLUDED == TRUE && BTA_GATT_INCLUDED == TRUE
    tBTA_DM_API_SEARCH    *p_msg;
    UINT16  len = p_services ? (sizeof(tBTA_DM_API_SEARCH) + sizeof(tBT_UUID) * p_services->num_uuid) :
                  sizeof(tBTA_DM_API_SEARCH);

    if ((p_msg = (tBTA_DM_API_SEARCH *) osi_malloc(len)) != NULL) {
        memset(p_msg, 0, len);

        p_msg->hdr.event = BTA_DM_API_SEARCH_EVT;
        memcpy(&p_msg->inq_params, p_dm_inq, sizeof(tBTA_DM_INQ));
        p_msg->p_cback = p_cback;
        p_msg->rs_res  = BTA_DM_RS_NONE;


        if (p_services != NULL) {
            p_msg->services = p_services->srvc_mask;
            p_msg->num_uuid = p_services->num_uuid;

            if (p_services->num_uuid != 0) {
                p_msg->p_uuid = (tBT_UUID *)(p_msg + 1);
                memcpy(p_msg->p_uuid, p_services->p_uuid, sizeof(tBT_UUID) * p_services->num_uuid);
            } else {
                p_msg->p_uuid = NULL;
            }
        }

        bta_sys_sendmsg(p_msg);
    }
#else
    UNUSED(p_dm_inq);
    UNUSED(p_services);
    UNUSED(p_cback);
#endif
}