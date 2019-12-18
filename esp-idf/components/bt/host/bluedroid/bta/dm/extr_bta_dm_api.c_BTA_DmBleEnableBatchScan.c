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
typedef  int /*<<< orphan*/  tBTA_DM_BLE_REF_VALUE ;
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/  ref_value; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  discard_rule; void* scan_window; void* scan_int; int /*<<< orphan*/  scan_mode; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_ENABLE_SCAN ;
typedef  int /*<<< orphan*/  tBTA_BLE_DISCARD_RULE ;
typedef  int /*<<< orphan*/  tBTA_BLE_BATCH_SCAN_MODE ;
typedef  int /*<<< orphan*/  tBLE_ADDR_TYPE ;
typedef  void* UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_BLE_ENABLE_BATCH_SCAN_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 scalar_t__ osi_malloc (int) ; 

extern void BTA_DmBleEnableBatchScan(tBTA_BLE_BATCH_SCAN_MODE scan_mode,
                                     UINT32 scan_interval, UINT32 scan_window,
                                     tBTA_BLE_DISCARD_RULE discard_rule,
                                     tBLE_ADDR_TYPE        addr_type,
                                     tBTA_DM_BLE_REF_VALUE ref_value)
{
    tBTA_DM_API_ENABLE_SCAN  *p_msg;

    if ((p_msg = (tBTA_DM_API_ENABLE_SCAN *) osi_malloc(sizeof(tBTA_DM_API_ENABLE_SCAN))) != NULL) {
        p_msg->hdr.event = BTA_DM_API_BLE_ENABLE_BATCH_SCAN_EVT;
        p_msg->scan_mode = scan_mode;
        p_msg->scan_int = scan_interval;
        p_msg->scan_window = scan_window;
        p_msg->discard_rule = discard_rule;
        p_msg->addr_type = addr_type;
        p_msg->ref_value = ref_value;
        bta_sys_sendmsg(p_msg);
    }
}