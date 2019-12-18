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

void
br_aes_ct64_interleave_out(uint32_t *w, uint64_t q0, uint64_t q1)
{
	uint64_t x0, x1, x2, x3;

	x0 = q0 & (uint64_t)0x00FF00FF00FF00FF;
	x1 = q1 & (uint64_t)0x00FF00FF00FF00FF;
	x2 = (q0 >> 8) & (uint64_t)0x00FF00FF00FF00FF;
	x3 = (q1 >> 8) & (uint64_t)0x00FF00FF00FF00FF;
	x0 |= (x0 >> 8);
	x1 |= (x1 >> 8);
	x2 |= (x2 >> 8);
	x3 |= (x3 >> 8);
	x0 &= (uint64_t)0x0000FFFF0000FFFF;
	x1 &= (uint64_t)0x0000FFFF0000FFFF;
	x2 &= (uint64_t)0x0000FFFF0000FFFF;
	x3 &= (uint64_t)0x0000FFFF0000FFFF;
	w[0] = (uint32_t)x0 | (uint32_t)(x0 >> 16);
	w[1] = (uint32_t)x1 | (uint32_t)(x1 >> 16);
	w[2] = (uint32_t)x2 | (uint32_t)(x2 >> 16);
	w[3] = (uint32_t)x3 | (uint32_t)(x3 >> 16);
}