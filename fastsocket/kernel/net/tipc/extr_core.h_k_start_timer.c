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
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,struct timer_list*,unsigned long) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (struct timer_list*,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (unsigned long) ; 

__attribute__((used)) static inline void k_start_timer(struct timer_list *timer, unsigned long msec)
{
	dbg("starting timer %p for %u\n", timer, msec);
	mod_timer(timer, jiffies + msecs_to_jiffies(msec) + 1);
}