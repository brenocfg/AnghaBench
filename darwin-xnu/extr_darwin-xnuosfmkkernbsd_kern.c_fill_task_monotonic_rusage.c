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
typedef  int /*<<< orphan*/  task_t ;
typedef  int /*<<< orphan*/  rusage_info_current ;

/* Variables and functions */

void
fill_task_monotonic_rusage(task_t task, rusage_info_current *ri)
{
#if MONOTONIC
	if (!mt_core_supported) {
		return;
	}

	assert(task != TASK_NULL);

	uint64_t counts[MT_CORE_NFIXED] = {};
	mt_fixed_task_counts(task, counts);
#ifdef MT_CORE_INSTRS
	ri->ri_instructions = counts[MT_CORE_INSTRS];
#endif /* defined(MT_CORE_INSTRS) */
	ri->ri_cycles = counts[MT_CORE_CYCLES];
#else /* MONOTONIC */
#pragma unused(task, ri)
#endif /* !MONOTONIC */
}