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
typedef  scalar_t__ int32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
LE0(int32_t x)
{
	uint32_t q;

	/*
	 * ~-x has its high bit set if and only if -x is nonnegative (as
	 * a signed int), i.e. x is in the -(2^31-1) to 0 range. We must
	 * do an OR with x itself to account for x = -2^31.
	 */
	q = (uint32_t)x;
	return (q | ~-q) >> 31;
}