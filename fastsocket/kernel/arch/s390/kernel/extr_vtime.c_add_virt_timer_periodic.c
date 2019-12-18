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
struct vtimer_list {int /*<<< orphan*/  expires; int /*<<< orphan*/  interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  internal_add_vtimer (struct vtimer_list*) ; 
 int /*<<< orphan*/  prepare_vtimer (struct vtimer_list*) ; 

void add_virt_timer_periodic(void *new)
{
	struct vtimer_list *timer;

	timer = (struct vtimer_list *)new;
	prepare_vtimer(timer);
	timer->interval = timer->expires;
	internal_add_vtimer(timer);
}