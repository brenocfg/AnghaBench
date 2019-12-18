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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tBTA_START_STOP_SCAN_CMPL_CBACK ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DmBleScan (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btc_ble_stop_scanning(tBTA_START_STOP_SCAN_CMPL_CBACK *stop_scan_cb)
{
    uint8_t duration = 0;
    BTA_DmBleScan(false, duration, NULL, stop_scan_cb);
}