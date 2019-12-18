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
 int /*<<< orphan*/  adv_data_lock ; 
 int /*<<< orphan*/  adv_enable_lock ; 
 int /*<<< orphan*/  adv_param_lock ; 
 int /*<<< orphan*/  osi_mutex_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_enable_lock ; 
 int /*<<< orphan*/  scan_param_lock ; 

void btm_ble_lock_init(void)
{
    osi_mutex_new(&adv_enable_lock);
    osi_mutex_new(&adv_data_lock);
    osi_mutex_new(&adv_param_lock);
    osi_mutex_new(&scan_enable_lock);
    osi_mutex_new(&scan_param_lock);
}