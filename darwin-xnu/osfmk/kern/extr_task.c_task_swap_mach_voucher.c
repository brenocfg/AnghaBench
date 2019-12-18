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
typedef  scalar_t__ task_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_voucher_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_TASK ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ TASK_NULL ; 

kern_return_t
task_swap_mach_voucher(
	task_t			task,
	ipc_voucher_t		new_voucher,
	ipc_voucher_t		*in_out_old_voucher)
{
	if (TASK_NULL == task)
		return KERN_INVALID_TASK;

	*in_out_old_voucher = new_voucher;
	return KERN_SUCCESS;
}