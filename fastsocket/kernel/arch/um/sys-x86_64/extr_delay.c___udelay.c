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
 unsigned long HZ ; 
 unsigned long MILLION ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long loops_per_jiffy ; 

void __udelay(unsigned long usecs)
{
	unsigned long i, n;

	n = (loops_per_jiffy * HZ * usecs) / MILLION;
        for(i=0;i<n;i++)
                cpu_relax();
}