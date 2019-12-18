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
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* power_off ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ps3_sys_manager_halt () ; 
 TYPE_1__ ps3_sys_manager_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void ps3_sys_manager_power_off(void)
{
	if (ps3_sys_manager_ops.power_off)
		ps3_sys_manager_ops.power_off(ps3_sys_manager_ops.dev);

	ps3_sys_manager_halt();
}