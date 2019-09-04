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
typedef  int /*<<< orphan*/  task_inspect_t ;
typedef  int /*<<< orphan*/  task_inspect_info_t ;
typedef  int /*<<< orphan*/  task_inspect_flavor_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOT_SUPPORTED ; 

kern_return_t
task_inspect(task_inspect_t task_insp, task_inspect_flavor_t flavor,
		task_inspect_info_t info_out, mach_msg_type_number_t *size_in_out)
{
#if MONOTONIC
	task_t task = (task_t)task_insp;
	kern_return_t kr = KERN_SUCCESS;
	mach_msg_type_number_t size;

	if (task == TASK_NULL) {
		return KERN_INVALID_ARGUMENT;
	}

	size = *size_in_out;

	switch (flavor) {
	case TASK_INSPECT_BASIC_COUNTS: {
		struct task_inspect_basic_counts *bc;
		uint64_t task_counts[MT_CORE_NFIXED];

		if (size < TASK_INSPECT_BASIC_COUNTS_COUNT) {
			kr = KERN_INVALID_ARGUMENT;
			break;
		}

		mt_fixed_task_counts(task, task_counts);
		bc = (struct task_inspect_basic_counts *)info_out;
#ifdef MT_CORE_INSTRS
		bc->instructions = task_counts[MT_CORE_INSTRS];
#else /* defined(MT_CORE_INSTRS) */
		bc->instructions = 0;
#endif /* !defined(MT_CORE_INSTRS) */
		bc->cycles = task_counts[MT_CORE_CYCLES];
		size = TASK_INSPECT_BASIC_COUNTS_COUNT;
		break;
	}
	default:
		kr = KERN_INVALID_ARGUMENT;
		break;
	}

	if (kr == KERN_SUCCESS) {
		*size_in_out = size;
	}
	return kr;
#else /* MONOTONIC */
#pragma unused(task_insp, flavor, info_out, size_in_out)
	return KERN_NOT_SUPPORTED;
#endif /* !MONOTONIC */
}