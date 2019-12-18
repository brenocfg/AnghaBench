#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clock_event_device {scalar_t__ mode; } ;
typedef  scalar_t__ cycle_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_alarm ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;scalar_t__ (* get_cycle_counter ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CLOCK_EVT_MODE_ONESHOT ; 
 int /*<<< orphan*/  VMI_ONESHOT ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmi_counter (int /*<<< orphan*/ ) ; 
 TYPE_1__ vmi_timer_ops ; 

__attribute__((used)) static int vmi_timer_next_event(unsigned long delta,
				struct clock_event_device *evt)
{
	/* Unfortunately, set_next_event interface only passes relative
	 * expiry, but we want absolute expiry.  It'd be better if were
	 * were passed an aboslute expiry, since a bunch of time may
	 * have been stolen between the time the delta is computed and
	 * when we set the alarm below. */
	cycle_t now = vmi_timer_ops.get_cycle_counter(vmi_counter(VMI_ONESHOT));

	BUG_ON(evt->mode != CLOCK_EVT_MODE_ONESHOT);
	vmi_timer_ops.set_alarm(VMI_ONESHOT, now + delta, 0);
	return 0;
}