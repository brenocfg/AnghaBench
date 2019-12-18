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
typedef  int uint32_t ;

/* Variables and functions */
 int MUL (int,int) ; 

__attribute__((used)) static inline void
bmul(uint32_t *hi, uint32_t *lo, uint32_t x, uint32_t y)
{
	uint32_t x0, x1, x2, x3;
	uint32_t y0, y1, y2, y3;
	uint64_t z0, z1, z2, z3;
	uint64_t z;

	x0 = x & (uint32_t)0x11111111;
	x1 = x & (uint32_t)0x22222222;
	x2 = x & (uint32_t)0x44444444;
	x3 = x & (uint32_t)0x88888888;
	y0 = y & (uint32_t)0x11111111;
	y1 = y & (uint32_t)0x22222222;
	y2 = y & (uint32_t)0x44444444;
	y3 = y & (uint32_t)0x88888888;
	z0 = MUL(x0, y0) ^ MUL(x1, y3) ^ MUL(x2, y2) ^ MUL(x3, y1);
	z1 = MUL(x0, y1) ^ MUL(x1, y0) ^ MUL(x2, y3) ^ MUL(x3, y2);
	z2 = MUL(x0, y2) ^ MUL(x1, y1) ^ MUL(x2, y0) ^ MUL(x3, y3);
	z3 = MUL(x0, y3) ^ MUL(x1, y2) ^ MUL(x2, y1) ^ MUL(x3, y0);
	z0 &= (uint64_t)0x1111111111111111;
	z1 &= (uint64_t)0x2222222222222222;
	z2 &= (uint64_t)0x4444444444444444;
	z3 &= (uint64_t)0x8888888888888888;
	z = z0 | z1 | z2 | z3;
	*lo = (uint32_t)z;
	*hi = (uint32_t)(z >> 32);
}