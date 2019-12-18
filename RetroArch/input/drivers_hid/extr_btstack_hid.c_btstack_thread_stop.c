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
 int /*<<< orphan*/  HCI_POWER_OFF ; 
 int /*<<< orphan*/  bt_send_cmd_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btstack_set_power_mode_ptr ; 

__attribute__((used)) static void btstack_thread_stop(void *data)
{
   (void)data;
   bt_send_cmd_ptr(btstack_set_power_mode_ptr, HCI_POWER_OFF);
}