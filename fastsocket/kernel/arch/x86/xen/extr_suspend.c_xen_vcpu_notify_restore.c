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
 int /*<<< orphan*/  clockevents_notify (unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ smp_processor_id () ; 

__attribute__((used)) static void xen_vcpu_notify_restore(void *data)
{
	unsigned long reason = (unsigned long)data;

	/* Boot processor notified via generic timekeeping_resume() */
	if ( smp_processor_id() == 0)
		return;

	clockevents_notify(reason, NULL);
}