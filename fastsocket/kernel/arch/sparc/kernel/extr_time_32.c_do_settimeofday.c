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
struct timespec {int dummy; } ;

/* Variables and functions */
 int bus_do_settimeofday (struct timespec*) ; 
 int /*<<< orphan*/  clock_was_set () ; 
 int /*<<< orphan*/  write_seqlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xtime_lock ; 

int do_settimeofday(struct timespec *tv)
{
	int ret;

	write_seqlock_irq(&xtime_lock);
	ret = bus_do_settimeofday(tv);
	write_sequnlock_irq(&xtime_lock);
	clock_was_set();
	return ret;
}