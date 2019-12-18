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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_2__ {int /*<<< orphan*/  (* supports_ble ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  btm_ble_start_adv () ; 
 int /*<<< orphan*/  btm_ble_stop_adv () ; 
 TYPE_1__* controller_get_interface () ; 
 int /*<<< orphan*/  stub1 () ; 

tBTM_STATUS BTM_BleStartAdv(void)
{
    tBTM_STATUS status = BTM_SUCCESS;
    if (!controller_get_interface()->supports_ble()) {
        return BTM_ILLEGAL_VALUE;
    }

    btm_ble_stop_adv();

    status = btm_ble_start_adv();

    return status;
}