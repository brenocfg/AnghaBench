#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  tBTA_START_STOP_SCAN_CMPL_CBACK ;
typedef  int /*<<< orphan*/  tBTA_DM_SEARCH_CBACK ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DmBleScan (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BTC_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  btc_adv_list_refresh () ; 

__attribute__((used)) static void btc_ble_start_scanning(uint32_t duration,
                                   tBTA_DM_SEARCH_CBACK *results_cb,
                                   tBTA_START_STOP_SCAN_CMPL_CBACK *start_scan_cb)
{
    if ((results_cb != NULL) && (start_scan_cb != NULL)) {
#if SCAN_QUEUE_CONGEST_CHECK
        btc_adv_list_refresh();
#endif
        //Start scan the device
        BTA_DmBleScan(true, duration, results_cb, start_scan_cb);
    } else {
        BTC_TRACE_ERROR("The start_scan_cb or results_cb invalid\n");
    }
}