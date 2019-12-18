#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * call; } ;
struct TYPE_5__ {TYPE_1__ threshold; int /*<<< orphan*/  dequeues; } ;
typedef  TYPE_2__ timer_longterm_t ;
typedef  int /*<<< orphan*/ * timer_call_t ;

/* Variables and functions */
 TYPE_2__ timer_longterm ; 

void
timer_longterm_dequeued_locked(timer_call_t call)
{
	timer_longterm_t	*tlp = &timer_longterm;

	tlp->dequeues++;
	if (call == tlp->threshold.call)
		tlp->threshold.call = NULL;
}