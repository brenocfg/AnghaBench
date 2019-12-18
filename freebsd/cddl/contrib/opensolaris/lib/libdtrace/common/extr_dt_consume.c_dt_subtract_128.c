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

/* Variables and functions */

__attribute__((used)) static void
dt_subtract_128(uint64_t *minuend, uint64_t *subtrahend, uint64_t *difference)
{
	uint64_t result[2];

	result[0] = minuend[0] - subtrahend[0];
	result[1] = minuend[1] - subtrahend[1] -
	    (minuend[0] < subtrahend[0] ? 1 : 0);

	difference[0] = result[0];
	difference[1] = result[1];
}