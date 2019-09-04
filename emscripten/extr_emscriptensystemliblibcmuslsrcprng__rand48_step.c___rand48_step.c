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
typedef  unsigned short uint64_t ;

/* Variables and functions */

uint64_t __rand48_step(unsigned short *xi, unsigned short *lc)
{
	uint64_t a, x;
	x = xi[0] | xi[1]+0U<<16 | xi[2]+0ULL<<32;
	a = lc[0] | lc[1]+0U<<16 | lc[2]+0ULL<<32;
	x = a*x + lc[3];
	xi[0] = x;
	xi[1] = x>>16;
	xi[2] = x>>32;
	return x & 0xffffffffffffull;
}