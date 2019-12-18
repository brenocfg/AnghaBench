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
struct clock_event_device {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ CLOCK_EVT_MODE_ONESHOT ; 
 scalar_t__ HYPERVISOR_set_timer_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  get_abs_timeout (unsigned long) ; 

__attribute__((used)) static int xen_timerop_set_next_event(unsigned long delta,
				      struct clock_event_device *evt)
{
	WARN_ON(evt->mode != CLOCK_EVT_MODE_ONESHOT);

	if (HYPERVISOR_set_timer_op(get_abs_timeout(delta)) < 0)
		BUG();

	/* We may have missed the deadline, but there's no real way of
	   knowing for sure.  If the event was in the past, then we'll
	   get an immediate interrupt. */

	return 0;
}