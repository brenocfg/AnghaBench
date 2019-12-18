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

__attribute__((used)) static inline uint64_t
bmul64(uint64_t x, uint64_t y)
{
	uint64_t x0, x1, x2, x3;
	uint64_t y0, y1, y2, y3;
	uint64_t z0, z1, z2, z3;

	x0 = x & (uint64_t)0x1111111111111111;
	x1 = x & (uint64_t)0x2222222222222222;
	x2 = x & (uint64_t)0x4444444444444444;
	x3 = x & (uint64_t)0x8888888888888888;
	y0 = y & (uint64_t)0x1111111111111111;
	y1 = y & (uint64_t)0x2222222222222222;
	y2 = y & (uint64_t)0x4444444444444444;
	y3 = y & (uint64_t)0x8888888888888888;
	z0 = (x0 * y0) ^ (x1 * y3) ^ (x2 * y2) ^ (x3 * y1);
	z1 = (x0 * y1) ^ (x1 * y0) ^ (x2 * y3) ^ (x3 * y2);
	z2 = (x0 * y2) ^ (x1 * y1) ^ (x2 * y0) ^ (x3 * y3);
	z3 = (x0 * y3) ^ (x1 * y2) ^ (x2 * y1) ^ (x3 * y0);
	z0 &= (uint64_t)0x1111111111111111;
	z1 &= (uint64_t)0x2222222222222222;
	z2 &= (uint64_t)0x4444444444444444;
	z3 &= (uint64_t)0x8888888888888888;
	return z0 | z1 | z2 | z3;
}