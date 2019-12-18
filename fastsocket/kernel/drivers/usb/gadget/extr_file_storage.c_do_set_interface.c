#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_endpoint_descriptor {int /*<<< orphan*/  wMaxPacketSize; } ;
struct fsg_dev {int running; int bulk_in_enabled; int bulk_out_enabled; int intr_in_enabled; int nluns; TYPE_1__* luns; TYPE_2__* intreq; int /*<<< orphan*/  intr_in; int /*<<< orphan*/  bulk_out; int /*<<< orphan*/  bulk_in; struct fsg_buffhd* buffhds; int /*<<< orphan*/  gadget; int /*<<< orphan*/  atomic_bitflags; int /*<<< orphan*/  bulk_out_maxpacket; } ;
struct fsg_buffhd {TYPE_2__* outreq; TYPE_2__* inreq; int /*<<< orphan*/  buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  complete; struct fsg_buffhd* context; int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  unit_attention_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct fsg_dev*,char*,...) ; 
 int /*<<< orphan*/  IGNORE_BULK_OUT ; 
 int NUM_BUFFERS ; 
 int /*<<< orphan*/  SS_RESET_OCCURRED ; 
 int alloc_request (struct fsg_dev*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  bulk_in_complete ; 
 int /*<<< orphan*/  bulk_out_complete ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int enable_endpoint (struct fsg_dev*,int /*<<< orphan*/ ,struct usb_endpoint_descriptor const*) ; 
 struct usb_endpoint_descriptor* ep_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_bulk_in_desc ; 
 int /*<<< orphan*/  fs_bulk_out_desc ; 
 int /*<<< orphan*/  fs_intr_in_desc ; 
 int /*<<< orphan*/  hs_bulk_in_desc ; 
 int /*<<< orphan*/  hs_bulk_out_desc ; 
 int /*<<< orphan*/  hs_intr_in_desc ; 
 int /*<<< orphan*/  intr_in_complete ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ transport_is_cbi () ; 
 int /*<<< orphan*/  usb_ep_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_free_request (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int do_set_interface(struct fsg_dev *fsg, int altsetting)
{
	int	rc = 0;
	int	i;
	const struct usb_endpoint_descriptor	*d;

	if (fsg->running)
		DBG(fsg, "reset interface\n");

reset:
	/* Deallocate the requests */
	for (i = 0; i < NUM_BUFFERS; ++i) {
		struct fsg_buffhd *bh = &fsg->buffhds[i];

		if (bh->inreq) {
			usb_ep_free_request(fsg->bulk_in, bh->inreq);
			bh->inreq = NULL;
		}
		if (bh->outreq) {
			usb_ep_free_request(fsg->bulk_out, bh->outreq);
			bh->outreq = NULL;
		}
	}
	if (fsg->intreq) {
		usb_ep_free_request(fsg->intr_in, fsg->intreq);
		fsg->intreq = NULL;
	}

	/* Disable the endpoints */
	if (fsg->bulk_in_enabled) {
		usb_ep_disable(fsg->bulk_in);
		fsg->bulk_in_enabled = 0;
	}
	if (fsg->bulk_out_enabled) {
		usb_ep_disable(fsg->bulk_out);
		fsg->bulk_out_enabled = 0;
	}
	if (fsg->intr_in_enabled) {
		usb_ep_disable(fsg->intr_in);
		fsg->intr_in_enabled = 0;
	}

	fsg->running = 0;
	if (altsetting < 0 || rc != 0)
		return rc;

	DBG(fsg, "set interface %d\n", altsetting);

	/* Enable the endpoints */
	d = ep_desc(fsg->gadget, &fs_bulk_in_desc, &hs_bulk_in_desc);
	if ((rc = enable_endpoint(fsg, fsg->bulk_in, d)) != 0)
		goto reset;
	fsg->bulk_in_enabled = 1;

	d = ep_desc(fsg->gadget, &fs_bulk_out_desc, &hs_bulk_out_desc);
	if ((rc = enable_endpoint(fsg, fsg->bulk_out, d)) != 0)
		goto reset;
	fsg->bulk_out_enabled = 1;
	fsg->bulk_out_maxpacket = le16_to_cpu(d->wMaxPacketSize);
	clear_bit(IGNORE_BULK_OUT, &fsg->atomic_bitflags);

	if (transport_is_cbi()) {
		d = ep_desc(fsg->gadget, &fs_intr_in_desc, &hs_intr_in_desc);
		if ((rc = enable_endpoint(fsg, fsg->intr_in, d)) != 0)
			goto reset;
		fsg->intr_in_enabled = 1;
	}

	/* Allocate the requests */
	for (i = 0; i < NUM_BUFFERS; ++i) {
		struct fsg_buffhd	*bh = &fsg->buffhds[i];

		if ((rc = alloc_request(fsg, fsg->bulk_in, &bh->inreq)) != 0)
			goto reset;
		if ((rc = alloc_request(fsg, fsg->bulk_out, &bh->outreq)) != 0)
			goto reset;
		bh->inreq->buf = bh->outreq->buf = bh->buf;
		bh->inreq->context = bh->outreq->context = bh;
		bh->inreq->complete = bulk_in_complete;
		bh->outreq->complete = bulk_out_complete;
	}
	if (transport_is_cbi()) {
		if ((rc = alloc_request(fsg, fsg->intr_in, &fsg->intreq)) != 0)
			goto reset;
		fsg->intreq->complete = intr_in_complete;
	}

	fsg->running = 1;
	for (i = 0; i < fsg->nluns; ++i)
		fsg->luns[i].unit_attention_data = SS_RESET_OCCURRED;
	return rc;
}