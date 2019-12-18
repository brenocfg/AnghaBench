#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* supports_ble_privacy ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btm_ble_suspend_resolving_list_activity () ; 
 int /*<<< orphan*/  btm_ble_vendor_enable_irk_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btsnd_hcic_ble_set_addr_resolution_enable (int /*<<< orphan*/ ) ; 
 TYPE_1__* controller_get_interface () ; 
 int /*<<< orphan*/  stub1 () ; 

void btm_ble_exe_enable_resolving_list(void)
{
    if (!btm_ble_suspend_resolving_list_activity()) {
        return;
    }

    if (!controller_get_interface()->supports_ble_privacy()) {
        btm_ble_vendor_enable_irk_feature(TRUE);
    } else {
        btsnd_hcic_ble_set_addr_resolution_enable(TRUE);
    }
}