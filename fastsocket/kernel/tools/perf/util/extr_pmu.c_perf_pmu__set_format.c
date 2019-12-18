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
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERF_PMU_FORMAT_BITS ; 
 int /*<<< orphan*/  memset (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (long,unsigned long*) ; 

void perf_pmu__set_format(unsigned long *bits, long from, long to)
{
	long b;

	if (!to)
		to = from;

	memset(bits, 0, BITS_TO_LONGS(PERF_PMU_FORMAT_BITS));
	for (b = from; b <= to; b++)
		set_bit(b, bits);
}