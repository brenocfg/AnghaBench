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
 int /*<<< orphan*/  jiffies_to_msecs (int) ; 
 long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (long) ; 

__attribute__((used)) static void sleep_delay(long n)
{
	/* Sleep nicely for 'n' uS */
	int d = n / msecs_to_jiffies(1000);
	if (!d)
		udelay(n);
	else
		msleep(jiffies_to_msecs(d));
}