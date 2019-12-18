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
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (long) ; 

__attribute__((used)) static void turnaround_delay(unsigned long last_jif, int mtt)
{
	long ticks;

	mtt = mtt < 10000 ? 10000 : mtt;
	ticks = 1 + mtt / (USEC_PER_SEC / HZ);
	schedule_timeout_uninterruptible(ticks);
}