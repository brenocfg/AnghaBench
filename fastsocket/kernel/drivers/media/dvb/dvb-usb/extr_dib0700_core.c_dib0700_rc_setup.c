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
struct urb {int /*<<< orphan*/ * transfer_buffer; int /*<<< orphan*/  status; } ;
struct dvb_usb_device {int /*<<< orphan*/  udev; struct dib0700_state* priv; } ;
struct dib0700_state {int fw_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RC_MSG_SIZE_V1_20 ; 
 int /*<<< orphan*/  dib0700_rc_urb_completion ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dvb_usb_device*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

int dib0700_rc_setup(struct dvb_usb_device *d)
{
	struct dib0700_state *st = d->priv;
	struct urb *purb;
	int ret;

	/* Poll-based. Don't initialize bulk mode */
	if (st->fw_version < 0x10200)
		return 0;

	/* Starting in firmware 1.20, the RC info is provided on a bulk pipe */
	purb = usb_alloc_urb(0, GFP_KERNEL);
	if (purb == NULL) {
		err("rc usb alloc urb failed\n");
		return -ENOMEM;
	}

	purb->transfer_buffer = kzalloc(RC_MSG_SIZE_V1_20, GFP_KERNEL);
	if (purb->transfer_buffer == NULL) {
		err("rc kzalloc failed\n");
		usb_free_urb(purb);
		return -ENOMEM;
	}

	purb->status = -EINPROGRESS;
	usb_fill_bulk_urb(purb, d->udev, usb_rcvbulkpipe(d->udev, 1),
			  purb->transfer_buffer, RC_MSG_SIZE_V1_20,
			  dib0700_rc_urb_completion, d);

	ret = usb_submit_urb(purb, GFP_ATOMIC);
	if (ret)
		err("rc submit urb failed\n");

	return ret;
}