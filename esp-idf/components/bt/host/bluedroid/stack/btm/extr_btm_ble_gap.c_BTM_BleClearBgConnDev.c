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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  btm_ble_clear_white_list () ; 
 int /*<<< orphan*/  btm_ble_start_auto_conn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_reset_bgdev_list () ; 

void BTM_BleClearBgConnDev(void)
{
    btm_ble_start_auto_conn(FALSE);
    btm_ble_clear_white_list();
    gatt_reset_bgdev_list();
}