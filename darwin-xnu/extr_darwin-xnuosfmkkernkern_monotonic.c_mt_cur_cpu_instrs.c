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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */

uint64_t
mt_cur_cpu_instrs(void)
{
#ifdef MT_CORE_INSTRS
	uint64_t counts[MT_CORE_NFIXED];

	if (!mt_core_supported) {
		return 0;
	}

	mt_fixed_counts(counts);
	return counts[MT_CORE_INSTRS];
#else /* defined(MT_CORE_INSTRS) */
	return 0;
#endif /* !defined(MT_CORE_INSTRS) */
}