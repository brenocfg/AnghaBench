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
struct uinput_request {int /*<<< orphan*/  id; int /*<<< orphan*/  code; } ;
struct uinput_device {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  EV_UINPUT ; 
 scalar_t__ UIST_CREATED ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uinput_dev_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uinput_request_reserve_slot (struct uinput_device*,struct uinput_request*) ; 

__attribute__((used)) static int uinput_request_submit(struct uinput_device *udev, struct uinput_request *request)
{
	int retval;

	retval = uinput_request_reserve_slot(udev, request);
	if (retval)
		return retval;

	retval = mutex_lock_interruptible(&udev->mutex);
	if (retval)
		return retval;

	if (udev->state != UIST_CREATED) {
		retval = -ENODEV;
		goto out;
	}

	/* Tell our userspace app about this new request by queueing an input event */
	uinput_dev_event(udev->dev, EV_UINPUT, request->code, request->id);

 out:
	mutex_unlock(&udev->mutex);
	return retval;
}