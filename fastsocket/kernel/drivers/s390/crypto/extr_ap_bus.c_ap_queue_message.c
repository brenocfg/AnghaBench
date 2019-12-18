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
struct ap_message {int /*<<< orphan*/  (* receive ) (struct ap_device*,struct ap_message*,int /*<<< orphan*/ ) ;} ;
struct ap_device {int unregistered; int /*<<< orphan*/  device; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  ERR_PTR (int) ; 
 int __ap_queue_message (struct ap_device*,struct ap_message*) ; 
 int ap_poll_queue (struct ap_device*,unsigned long*) ; 
 int /*<<< orphan*/  ap_poll_wait ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ap_device*,struct ap_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void ap_queue_message(struct ap_device *ap_dev, struct ap_message *ap_msg)
{
	unsigned long flags;
	int rc;

	/* For asynchronous message handling a valid receive-callback
	 * is required. */
	BUG_ON(!ap_msg->receive);

	spin_lock_bh(&ap_dev->lock);
	if (!ap_dev->unregistered) {
		/* Make room on the queue by polling for finished requests. */
		rc = ap_poll_queue(ap_dev, &flags);
		if (!rc)
			rc = __ap_queue_message(ap_dev, ap_msg);
		if (!rc)
			wake_up(&ap_poll_wait);
		if (rc == -ENODEV)
			ap_dev->unregistered = 1;
	} else {
		ap_msg->receive(ap_dev, ap_msg, ERR_PTR(-ENODEV));
		rc = -ENODEV;
	}
	spin_unlock_bh(&ap_dev->lock);
	if (rc == -ENODEV)
		device_unregister(&ap_dev->device);
}