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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_LLQUANTIZE_FACTOR (scalar_t__) ; 
 int /*<<< orphan*/  DTRACE_LLQUANTIZE_HIGH (scalar_t__) ; 
 int /*<<< orphan*/  DTRACE_LLQUANTIZE_LOW (scalar_t__) ; 
 int /*<<< orphan*/  DTRACE_LLQUANTIZE_NSTEP (scalar_t__) ; 
 size_t dtrace_aggregate_llquantize_bucket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
dtrace_aggregate_llquantize(uint64_t *llquanta, uint64_t nval, uint64_t incr)
{
	uint64_t arg    = *llquanta++;
	uint16_t factor = DTRACE_LLQUANTIZE_FACTOR(arg);
	uint16_t low    = DTRACE_LLQUANTIZE_LOW(arg);
	uint16_t high   = DTRACE_LLQUANTIZE_HIGH(arg);
	uint16_t nsteps = DTRACE_LLQUANTIZE_NSTEP(arg);

	llquanta[dtrace_aggregate_llquantize_bucket(factor, low, high, nsteps, nval)] += incr;
}