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
 int /*<<< orphan*/  DTCN0 ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 unsigned long long cycles2ns (unsigned long) ; 

unsigned long long sched_clock(void)
{
	unsigned long cycl = __raw_readl(DTCN0);

	return cycles2ns(cycl);
}