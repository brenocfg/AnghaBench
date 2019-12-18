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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dt_ge_128 (int*,int*) ; 
 int /*<<< orphan*/  dt_shift_128 (int*,int) ; 
 int /*<<< orphan*/  dt_subtract_128 (int*,int*,int*) ; 

__attribute__((used)) static void
dt_divide_128(uint64_t *dividend, uint64_t divisor, uint64_t *quotient)
{
	uint64_t result[2] = { 0, 0 };
	uint64_t remainder[2];
	uint64_t subtrahend[2];
	uint64_t divisor_128[2];
	uint64_t mask[2] = { 1, 0 };
	int log = 0;

	assert(divisor != 0);

	divisor_128[0] = divisor;
	divisor_128[1] = 0;

	remainder[0] = dividend[0];
	remainder[1] = dividend[1];

	subtrahend[0] = divisor;
	subtrahend[1] = 0;

	while (divisor > 0) {
		log++;
		divisor >>= 1;
	}

	dt_shift_128(subtrahend, 128 - log);
	dt_shift_128(mask, 128 - log);

	while (dt_ge_128(remainder, divisor_128)) {
		if (dt_ge_128(remainder, subtrahend)) {
			dt_subtract_128(remainder, subtrahend, remainder);
			result[0] |= mask[0];
			result[1] |= mask[1];
		}

		dt_shift_128(subtrahend, -1);
		dt_shift_128(mask, -1);
	}

	quotient[0] = result[0];
	quotient[1] = result[1];
}