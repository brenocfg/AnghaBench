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
struct kperf_context {int dummy; } ;

/* Variables and functions */

void
kperf_thread_inscyc_log(struct kperf_context *context)
{
#if MONOTONIC
	thread_t cur_thread = current_thread();

	if (context->cur_thread != cur_thread) {
		/* can't safely access another thread's counters */
		return;
	}

	uint64_t counts[MT_CORE_NFIXED];

	int ret = mt_fixed_thread_counts(cur_thread, counts);
	if (ret) {
		return;
	}

#if defined(__LP64__)
	BUF_DATA(PERF_TI_INSCYCDATA, counts[MT_CORE_INSTRS], counts[MT_CORE_CYCLES]);
#else /* defined(__LP64__) */
	/* 32-bit platforms don't count instructions */
	BUF_DATA(PERF_TI_INSCYCDATA_32, 0, 0, UPPER_32(counts[MT_CORE_CYCLES]),
			LOWER_32(counts[MT_CORE_CYCLES]));
#endif /* !defined(__LP64__) */

#else
#pragma unused(context)
#endif /* MONOTONIC */

}