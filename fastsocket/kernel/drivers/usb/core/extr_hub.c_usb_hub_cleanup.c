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
 int /*<<< orphan*/  hub_driver ; 
 int /*<<< orphan*/  khubd_task ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_deregister (int /*<<< orphan*/ *) ; 

void usb_hub_cleanup(void)
{
	kthread_stop(khubd_task);

	/*
	 * Hub resources are freed for us by usb_deregister. It calls
	 * usb_driver_purge on every device which in turn calls that
	 * devices disconnect function if it is using this driver.
	 * The hub_disconnect function takes care of releasing the
	 * individual hub resources. -greg
	 */
	usb_deregister(&hub_driver);
}