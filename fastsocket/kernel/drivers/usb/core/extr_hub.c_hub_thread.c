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
 int /*<<< orphan*/  hub_event_list ; 
 int /*<<< orphan*/  hub_events () ; 
 int /*<<< orphan*/  khubd_wait ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  usbcore_name ; 
 int /*<<< orphan*/  wait_event_freezable (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hub_thread(void *__unused)
{
	/* khubd needs to be freezable to avoid intefering with USB-PERSIST
	 * port handover.  Otherwise it might see that a full-speed device
	 * was gone before the EHCI controller had handed its port over to
	 * the companion full-speed controller.
	 */
	set_freezable();

	do {
		hub_events();
		wait_event_freezable(khubd_wait,
				!list_empty(&hub_event_list) ||
				kthread_should_stop());
	} while (!kthread_should_stop() || !list_empty(&hub_event_list));

	pr_debug("%s: khubd exiting\n", usbcore_name);
	return 0;
}