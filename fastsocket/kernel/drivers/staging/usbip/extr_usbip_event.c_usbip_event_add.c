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
struct usbip_device {unsigned long event; int /*<<< orphan*/  lock; int /*<<< orphan*/  eh_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void usbip_event_add(struct usbip_device *ud, unsigned long event)
{
	spin_lock(&ud->lock);

	ud->event |= event;

	wake_up(&ud->eh_waitq);

	spin_unlock(&ud->lock);
}