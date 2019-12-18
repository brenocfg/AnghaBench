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
 unsigned long jiffies ; 
 int /*<<< orphan*/  timer_pending (struct timer_list*) ; 

unsigned long ax25_display_timer(struct timer_list *timer)
{
	if (!timer_pending(timer))
		return 0;

	return timer->expires - jiffies;
}