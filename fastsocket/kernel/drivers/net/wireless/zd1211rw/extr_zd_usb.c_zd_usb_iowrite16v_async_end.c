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
struct zd_usb {int cmd_error; scalar_t__ in_async; int /*<<< orphan*/  submitted_cmds; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int ENOENT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ZD_ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 unsigned int usb_wait_anchor_empty_timeout (int /*<<< orphan*/ *,unsigned int) ; 
 int zd_submit_waiting_urb (struct zd_usb*,int) ; 
 int /*<<< orphan*/  zd_usb_dev (struct zd_usb*) ; 
 TYPE_1__* zd_usb_to_chip (struct zd_usb*) ; 

int zd_usb_iowrite16v_async_end(struct zd_usb *usb, unsigned int timeout)
{
	int r;

	ZD_ASSERT(mutex_is_locked(&zd_usb_to_chip(usb)->mutex));
	ZD_ASSERT(usb->in_async);

	/* Submit last iowrite16v URB */
	r = zd_submit_waiting_urb(usb, true);
	if (r) {
		dev_dbg_f(zd_usb_dev(usb),
			"error in zd_submit_waiting_usb(). "
			"Error number %d\n", r);

		usb_kill_anchored_urbs(&usb->submitted_cmds);
		goto error;
	}

	if (timeout)
		timeout = usb_wait_anchor_empty_timeout(&usb->submitted_cmds,
							timeout);
	if (!timeout) {
		usb_kill_anchored_urbs(&usb->submitted_cmds);
		if (usb->cmd_error == -ENOENT) {
			dev_dbg_f(zd_usb_dev(usb), "timed out");
			r = -ETIMEDOUT;
			goto error;
		}
	}

	r = usb->cmd_error;
error:
	usb->in_async = 0;
	return r;
}