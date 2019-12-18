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
bmul32(uint32_t x, uint32_t y)
{
	uint32_t x0, x1, x2, x3;
	uint32_t y0, y1, y2, y3;
	uint32_t z0, z1, z2, z3;

	x0 = x & (uint32_t)0x11111111;
	x1 = x & (uint32_t)0x22222222;
	x2 = x & (uint32_t)0x44444444;
	x3 = x & (uint32_t)0x88888888;
	y0 = y & (uint32_t)0x11111111;
	y1 = y & (uint32_t)0x22222222;
	y2 = y & (uint32_t)0x44444444;
	y3 = y & (uint32_t)0x88888888;
	z0 = (x0 * y0) ^ (x1 * y3) ^ (x2 * y2) ^ (x3 * y1);
	z1 = (x0 * y1) ^ (x1 * y0) ^ (x2 * y3) ^ (x3 * y2);
	z2 = (x0 * y2) ^ (x1 * y1) ^ (x2 * y0) ^ (x3 * y3);
	z3 = (x0 * y3) ^ (x1 * y2) ^ (x2 * y1) ^ (x3 * y0);
	z0 &= (uint32_t)0x11111111;
	z1 &= (uint32_t)0x22222222;
	z2 &= (uint32_t)0x44444444;
	z3 &= (uint32_t)0x88888888;
	return z0 | z1 | z2 | z3;
}