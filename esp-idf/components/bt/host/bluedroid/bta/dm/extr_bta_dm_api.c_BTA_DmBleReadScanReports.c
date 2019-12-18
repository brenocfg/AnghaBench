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
struct TYPE_5__ {int /*<<< orphan*/  ref_value; int /*<<< orphan*/  scan_type; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_READ_SCAN_REPORTS ;
typedef  int /*<<< orphan*/  tBTA_BLE_BATCH_SCAN_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_BLE_READ_SCAN_REPORTS_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 scalar_t__ osi_malloc (int) ; 

extern void BTA_DmBleReadScanReports(tBTA_BLE_BATCH_SCAN_MODE scan_type,
                                     tBTA_DM_BLE_REF_VALUE ref_value)
{
    tBTA_DM_API_READ_SCAN_REPORTS  *p_msg;

    if ((p_msg = (tBTA_DM_API_READ_SCAN_REPORTS *)
                 osi_malloc(sizeof(tBTA_DM_API_READ_SCAN_REPORTS))) != NULL) {
        p_msg->hdr.event = BTA_DM_API_BLE_READ_SCAN_REPORTS_EVT;
        p_msg->scan_type = scan_type;
        p_msg->ref_value = ref_value;
        bta_sys_sendmsg(p_msg);
    }
}