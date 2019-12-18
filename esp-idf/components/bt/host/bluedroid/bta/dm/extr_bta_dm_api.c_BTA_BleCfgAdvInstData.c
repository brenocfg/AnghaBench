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
struct TYPE_6__ {int /*<<< orphan*/ * p_data; int /*<<< orphan*/  data_mask; int /*<<< orphan*/  is_scan_rsp; int /*<<< orphan*/  inst_id; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_BLE_MULTI_ADV_DATA ;
typedef  int /*<<< orphan*/  tBTA_BLE_AD_MASK ;
typedef  int /*<<< orphan*/  tBTA_BLE_ADV_DATA ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_API (char*) ; 
 int /*<<< orphan*/  BTA_DM_API_BLE_MULTI_ADV_DATA_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_BleCfgAdvInstData (UINT8 inst_id, BOOLEAN is_scan_rsp,
                            tBTA_BLE_AD_MASK data_mask,
                            tBTA_BLE_ADV_DATA *p_data)
{
    ///This function just used for vendor debug
    tBTA_DM_API_BLE_MULTI_ADV_DATA    *p_msg;
    UINT16      len =  sizeof(tBTA_DM_API_BLE_MULTI_ADV_DATA) ;

    APPL_TRACE_API ("BTA_BleCfgAdvInstData");

    if ((p_msg = (tBTA_DM_API_BLE_MULTI_ADV_DATA *) osi_malloc(len)) != NULL) {
        memset(p_msg, 0, len);
        p_msg->hdr.event     = BTA_DM_API_BLE_MULTI_ADV_DATA_EVT;
        p_msg->inst_id      = inst_id;
        p_msg->is_scan_rsp  = is_scan_rsp;
        p_msg->data_mask     = data_mask;
        p_msg->p_data        = p_data;

        bta_sys_sendmsg(p_msg);
    }
}