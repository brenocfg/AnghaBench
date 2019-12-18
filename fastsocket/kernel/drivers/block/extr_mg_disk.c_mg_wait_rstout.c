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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 unsigned int MG_ERR_NONE ; 
 unsigned int MG_ERR_RSTOUT ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned int mg_wait_rstout(u32 rstout, u32 msec)
{
	unsigned long expire;

	expire = jiffies + msecs_to_jiffies(msec);
	while (time_before(jiffies, expire)) {
		if (gpio_get_value(rstout) == 1)
			return MG_ERR_NONE;
		msleep(10);
	}

	return MG_ERR_RSTOUT;
}