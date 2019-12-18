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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
GT(uint32_t x, uint32_t y)
{
	/*
	 * If both x < 2^31 and x < 2^31, then y-x will have its high
	 * bit set if x > y, cleared otherwise.
	 *
	 * If either x >= 2^31 or y >= 2^31 (but not both), then the
	 * result is the high bit of x.
	 *
	 * If both x >= 2^31 and y >= 2^31, then we can virtually
	 * subtract 2^31 from both, and we are back to the first case.
	 * Since (y-2^31)-(x-2^31) = y-x, the subtraction is already
	 * fine.
	 */
	uint32_t z;

	z = y - x;
	return (z ^ ((x ^ y) & (x ^ z))) >> 31;
}