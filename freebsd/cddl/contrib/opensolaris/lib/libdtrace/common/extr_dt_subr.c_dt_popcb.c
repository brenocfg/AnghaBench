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
typedef  size_t ulong_t ;

/* Variables and functions */
 size_t BT_ULMASK ; 
 size_t BT_ULSHIFT ; 
 size_t dt_popc (size_t const) ; 

ulong_t
dt_popcb(const ulong_t *bp, ulong_t n)
{
	ulong_t maxb = n & BT_ULMASK;
	ulong_t maxw = n >> BT_ULSHIFT;
	ulong_t w, popc = 0;

	if (n == 0)
		return (0);

	for (w = 0; w < maxw; w++)
		popc += dt_popc(bp[w]);

	return (popc + dt_popc(bp[maxw] & ((1UL << maxb) - 1)));
}