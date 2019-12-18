#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usblp {size_t current_protocol; TYPE_1__* protocol; int /*<<< orphan*/  dev; } ;
struct urb {int /*<<< orphan*/  transfer_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_3__ {TYPE_2__* epwrite; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  URB_FREE_BUFFER ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct usblp*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usblp_bulk_write ; 

__attribute__((used)) static struct urb *usblp_new_writeurb(struct usblp *usblp, int transfer_length)
{
	struct urb *urb;
	char *writebuf;

	if ((writebuf = kmalloc(transfer_length, GFP_KERNEL)) == NULL)
		return NULL;
	if ((urb = usb_alloc_urb(0, GFP_KERNEL)) == NULL) {
		kfree(writebuf);
		return NULL;
	}

	usb_fill_bulk_urb(urb, usblp->dev,
		usb_sndbulkpipe(usblp->dev,
		 usblp->protocol[usblp->current_protocol].epwrite->bEndpointAddress),
		writebuf, transfer_length, usblp_bulk_write, usblp);
	urb->transfer_flags |= URB_FREE_BUFFER;

	return urb;
}