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
 int HZ ; 
 unsigned long jiffies ; 
 long schedule_timeout_interruptible (long) ; 
 scalar_t__ time_after (long,unsigned long) ; 
 int /*<<< orphan*/  udelay (unsigned long) ; 

void tms380tr_wait(unsigned long time)
{
#if 0
	long tmp;
	
	tmp = jiffies + time/(1000000/HZ);
	do {
		tmp = schedule_timeout_interruptible(tmp);
	} while(time_after(tmp, jiffies));
#else
	udelay(time);
#endif
	return;
}