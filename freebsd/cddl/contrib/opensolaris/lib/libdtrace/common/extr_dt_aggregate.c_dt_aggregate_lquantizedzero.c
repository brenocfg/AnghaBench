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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int DTRACE_LQUANTIZE_BASE (int /*<<< orphan*/ ) ; 
 int DTRACE_LQUANTIZE_LEVELS (int /*<<< orphan*/ ) ; 
 int DTRACE_LQUANTIZE_STEP (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t
dt_aggregate_lquantizedzero(int64_t *lquanta)
{
	int64_t arg = *lquanta++;
	int32_t base = DTRACE_LQUANTIZE_BASE(arg);
	uint16_t step = DTRACE_LQUANTIZE_STEP(arg);
	uint16_t levels = DTRACE_LQUANTIZE_LEVELS(arg), i;

	if (base - 1 == 0)
		return (lquanta[0]);

	for (i = 0; i < levels; base += step, i++) {
		if (base != 0)
			continue;

		return (lquanta[i + 1]);
	}

	if (base + 1 == 0)
		return (lquanta[levels + 1]);

	return (0);
}