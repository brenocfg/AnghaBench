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
struct timer_s {unsigned long period; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 size_t TID_CLOCKEVENT ; 
 int /*<<< orphan*/  timer32_config (struct timer_s*) ; 
 struct timer_s* timers ; 

__attribute__((used)) static int davinci_set_next_event(unsigned long cycles,
				  struct clock_event_device *evt)
{
	struct timer_s *t = &timers[TID_CLOCKEVENT];

	t->period = cycles;
	timer32_config(t);
	return 0;
}