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
struct timer_list {unsigned long expires; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_PINNED ; 
 int __mod_timer (struct timer_list*,unsigned long,int,int /*<<< orphan*/ ) ; 
 scalar_t__ timer_pending (struct timer_list*) ; 

int mod_timer_pinned(struct timer_list *timer, unsigned long expires)
{
	if (timer->expires == expires && timer_pending(timer))
		return 1;

	return __mod_timer(timer, expires, false, TIMER_PINNED);
}