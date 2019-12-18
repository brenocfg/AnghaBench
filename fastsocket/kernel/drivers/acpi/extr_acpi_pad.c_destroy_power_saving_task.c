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
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 size_t ps_tsk_num ; 
 int /*<<< orphan*/ * ps_tsks ; 

__attribute__((used)) static void destroy_power_saving_task(void)
{
	if (ps_tsk_num > 0) {
		ps_tsk_num--;
		kthread_stop(ps_tsks[ps_tsk_num]);
	}
}