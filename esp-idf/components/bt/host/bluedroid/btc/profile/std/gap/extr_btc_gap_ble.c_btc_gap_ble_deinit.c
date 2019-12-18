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

/* Variables and functions */
 int /*<<< orphan*/  btc_cleanup_adv_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_bta_adv_data ; 
 int /*<<< orphan*/  gl_bta_scan_rsp_data ; 

void btc_gap_ble_deinit(void)
{
    btc_cleanup_adv_data(&gl_bta_adv_data);
    btc_cleanup_adv_data(&gl_bta_scan_rsp_data);
}