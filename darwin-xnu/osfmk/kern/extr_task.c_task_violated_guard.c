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
typedef  int /*<<< orphan*/  mach_exception_subcode_t ;
typedef  int /*<<< orphan*/  mach_exception_code_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_VIOLATED_GUARD__SEND_EXC_GUARD_AND_SUSPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

kern_return_t
task_violated_guard(
	mach_exception_code_t code,
	mach_exception_subcode_t subcode,
	void *reason)
{
	return PROC_VIOLATED_GUARD__SEND_EXC_GUARD_AND_SUSPEND(code, subcode, reason);
}