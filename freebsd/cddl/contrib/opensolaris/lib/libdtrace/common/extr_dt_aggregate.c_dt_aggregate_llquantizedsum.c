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
typedef  int uint16_t ;
typedef  int int64_t ;

/* Variables and functions */
 int DTRACE_LLQUANTIZE_FACTOR (int) ; 
 int DTRACE_LLQUANTIZE_HIGH (int) ; 
 int DTRACE_LLQUANTIZE_LOW (int) ; 
 int DTRACE_LLQUANTIZE_NSTEP (int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static long double
dt_aggregate_llquantizedsum(int64_t *llquanta)
{
	int64_t arg = *llquanta++;
	uint16_t factor = DTRACE_LLQUANTIZE_FACTOR(arg);
	uint16_t low = DTRACE_LLQUANTIZE_LOW(arg);
	uint16_t high = DTRACE_LLQUANTIZE_HIGH(arg);
	uint16_t nsteps = DTRACE_LLQUANTIZE_NSTEP(arg);
	int bin = 0, order;
	int64_t value = 1, next, step;
	long double total;

	assert(nsteps >= factor);
	assert(nsteps % factor == 0);

	for (order = 0; order < low; order++)
		value *= factor;

	total = (long double)llquanta[bin++] * (long double)(value - 1);

	next = value * factor;
	step = next > nsteps ? next / nsteps : 1;

	while (order <= high) {
		assert(value < next);
		total += (long double)llquanta[bin++] * (long double)(value);

		if ((value += step) != next)
			continue;

		next = value * factor;
		step = next > nsteps ? next / nsteps : 1;
		order++;
	}

	return (total + (long double)llquanta[bin] * (long double)value);
}