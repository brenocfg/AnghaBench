#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  event; } ;
struct TYPE_6__ {void* p_ref; void* p_params; void* p_cback; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_BLE_MULTI_ADV_ENB ;
typedef  int /*<<< orphan*/  tBTA_BLE_MULTI_ADV_CBACK ;
typedef  int /*<<< orphan*/  tBTA_BLE_ADV_PARAMS ;
typedef  int UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_API (char*) ; 
 int /*<<< orphan*/  BTA_DM_API_BLE_MULTI_ADV_ENB_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_BleEnableAdvInstance (tBTA_BLE_ADV_PARAMS *p_params,
                               tBTA_BLE_MULTI_ADV_CBACK *p_cback,
                               void *p_ref)
{
    ///This function just used for vendor debug
    tBTA_DM_API_BLE_MULTI_ADV_ENB    *p_msg;
    UINT16 len = sizeof(tBTA_BLE_ADV_PARAMS) + sizeof(tBTA_DM_API_BLE_MULTI_ADV_ENB);

    APPL_TRACE_API ("BTA_BleEnableAdvInstance");

    if ((p_msg = (tBTA_DM_API_BLE_MULTI_ADV_ENB *) osi_malloc(len)) != NULL) {
        memset(p_msg, 0, sizeof(tBTA_DM_API_BLE_MULTI_ADV_ENB));

        p_msg->hdr.event     = BTA_DM_API_BLE_MULTI_ADV_ENB_EVT;
        p_msg->p_cback      = (void *)p_cback;
        if (p_params != NULL) {
            p_msg->p_params =  (void *)(p_msg + 1);
            memcpy(p_msg->p_params, p_params, sizeof(tBTA_BLE_ADV_PARAMS));
        }
        p_msg->p_ref        = p_ref;

        bta_sys_sendmsg(p_msg);
    }
}