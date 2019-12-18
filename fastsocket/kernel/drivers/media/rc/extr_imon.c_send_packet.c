#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_ctrlrequest {int bRequestType; int bRequest; void* wLength; void* wIndex; void* wValue; } ;
struct TYPE_7__ {int busy; int status; int /*<<< orphan*/  finished; } ;
struct imon_context {TYPE_2__ tx; int /*<<< orphan*/  lock; TYPE_3__* tx_urb; int /*<<< orphan*/  usb_tx_buf; int /*<<< orphan*/  usbdev_intf0; TYPE_1__* tx_endpoint; int /*<<< orphan*/  tx_control; } ;
struct TYPE_8__ {scalar_t__ actual_length; } ;
struct TYPE_6__ {int bInterval; int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct usb_ctrlrequest*) ; 
 struct usb_ctrlrequest* kmalloc (int,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  schedule_timeout (unsigned long) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  usb_fill_control_urb (TYPE_3__*,int /*<<< orphan*/ ,unsigned int,unsigned char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct imon_context*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_3__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct imon_context*,int) ; 
 unsigned int usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_tx_callback ; 
 int wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int send_packet(struct imon_context *ictx)
{
	unsigned int pipe;
	unsigned long timeout;
	int interval = 0;
	int retval = 0;
	struct usb_ctrlrequest *control_req = NULL;

	/* Check if we need to use control or interrupt urb */
	if (!ictx->tx_control) {
		pipe = usb_sndintpipe(ictx->usbdev_intf0,
				      ictx->tx_endpoint->bEndpointAddress);
		interval = ictx->tx_endpoint->bInterval;

		usb_fill_int_urb(ictx->tx_urb, ictx->usbdev_intf0, pipe,
				 ictx->usb_tx_buf,
				 sizeof(ictx->usb_tx_buf),
				 usb_tx_callback, ictx, interval);

		ictx->tx_urb->actual_length = 0;
	} else {
		/* fill request into kmalloc'ed space: */
		control_req = kmalloc(sizeof(struct usb_ctrlrequest),
				      GFP_KERNEL);
		if (control_req == NULL)
			return -ENOMEM;

		/* setup packet is '21 09 0200 0001 0008' */
		control_req->bRequestType = 0x21;
		control_req->bRequest = 0x09;
		control_req->wValue = cpu_to_le16(0x0200);
		control_req->wIndex = cpu_to_le16(0x0001);
		control_req->wLength = cpu_to_le16(0x0008);

		/* control pipe is endpoint 0x00 */
		pipe = usb_sndctrlpipe(ictx->usbdev_intf0, 0);

		/* build the control urb */
		usb_fill_control_urb(ictx->tx_urb, ictx->usbdev_intf0,
				     pipe, (unsigned char *)control_req,
				     ictx->usb_tx_buf,
				     sizeof(ictx->usb_tx_buf),
				     usb_tx_callback, ictx);
		ictx->tx_urb->actual_length = 0;
	}

	init_completion(&ictx->tx.finished);
	ictx->tx.busy = true;
	smp_rmb(); /* ensure later readers know we're busy */

	retval = usb_submit_urb(ictx->tx_urb, GFP_KERNEL);
	if (retval) {
		ictx->tx.busy = false;
		smp_rmb(); /* ensure later readers know we're not busy */
		pr_err("error submitting urb(%d)\n", retval);
	} else {
		/* Wait for transmission to complete (or abort) */
		mutex_unlock(&ictx->lock);
		retval = wait_for_completion_interruptible(
				&ictx->tx.finished);
		if (retval)
			pr_err("task interrupted\n");
		mutex_lock(&ictx->lock);

		retval = ictx->tx.status;
		if (retval)
			pr_err("packet tx failed (%d)\n", retval);
	}

	kfree(control_req);

	/*
	 * Induce a mandatory 5ms delay before returning, as otherwise,
	 * send_packet can get called so rapidly as to overwhelm the device,
	 * particularly on faster systems and/or those with quirky usb.
	 */
	timeout = msecs_to_jiffies(5);
	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule_timeout(timeout);

	return retval;
}