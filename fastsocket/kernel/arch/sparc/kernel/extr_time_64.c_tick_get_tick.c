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

/* Variables and functions */
 unsigned long TICK_PRIV_BIT ; 

__attribute__((used)) static unsigned long long tick_get_tick(void)
{
	unsigned long ret;

	__asm__ __volatile__("rd	%%tick, %0\n\t"
			     "mov	%0, %0"
			     : "=r" (ret));

	return ret & ~TICK_PRIV_BIT;
}