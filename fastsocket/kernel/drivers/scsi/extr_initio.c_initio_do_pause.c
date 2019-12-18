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
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned int jiffies ; 
 scalar_t__ time_before_eq (unsigned int,unsigned long) ; 

__attribute__((used)) static void initio_do_pause(unsigned amount)
{
	/* Pause for amount jiffies */
	unsigned long the_time = jiffies + amount;

	while (time_before_eq(jiffies, the_time))
		cpu_relax();
}