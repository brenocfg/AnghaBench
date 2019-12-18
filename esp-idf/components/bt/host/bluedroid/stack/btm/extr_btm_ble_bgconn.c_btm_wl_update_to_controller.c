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
 int /*<<< orphan*/  btm_execute_wl_dev_operation () ; 

__attribute__((used)) static void btm_wl_update_to_controller(void)
{
    /* whitelist will be added in the btm_ble_resume_bg_conn(), we do not
       support background connection now, so we nedd to use btm_execute_wl_dev_operation
       to add whitelist directly ,if we support background connection in the future,
       please delete btm_execute_wl_dev_operation(). */
    btm_execute_wl_dev_operation();

}