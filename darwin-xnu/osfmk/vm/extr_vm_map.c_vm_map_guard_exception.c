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
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  mach_exception_data_type_t ;
typedef  int /*<<< orphan*/  mach_exception_code_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXC_GUARD_ENCODE_FLAVOR (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  EXC_GUARD_ENCODE_TARGET (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  EXC_GUARD_ENCODE_TYPE (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int GUARD_TYPE_VIRT_MEMORY ; 
 scalar_t__ current_task () ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ kernel_task ; 
 int /*<<< orphan*/  thread_guard_violation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_map_guard_exception(
	vm_map_offset_t gap_start,
	unsigned reason)
{
	mach_exception_code_t code = 0;
	unsigned int guard_type = GUARD_TYPE_VIRT_MEMORY;
	unsigned int target = 0; /* should we pass in pid associated with map? */
	mach_exception_data_type_t subcode = (uint64_t)gap_start;

	/* Can't deliver exceptions to kernel task */
	if (current_task() == kernel_task)
		return;

	EXC_GUARD_ENCODE_TYPE(code, guard_type);
	EXC_GUARD_ENCODE_FLAVOR(code, reason);
	EXC_GUARD_ENCODE_TARGET(code, target);
	thread_guard_violation(current_thread(), code, subcode);
}