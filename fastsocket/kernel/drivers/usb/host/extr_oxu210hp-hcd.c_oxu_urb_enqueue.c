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
struct usb_hcd {int dummy; } ;
struct urb {int transfer_buffer_length; int /*<<< orphan*/ * complete; void* transfer_buffer; int /*<<< orphan*/  pipe; } ;
struct oxu_murb {int last; struct urb* main; } ;
struct oxu_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int __oxu_urb_enqueue (struct usb_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 struct oxu_hcd* hcd_to_oxu (struct usb_hcd*) ; 
 int /*<<< orphan*/  memcpy (struct urb*,struct urb*,int) ; 
 scalar_t__ oxu_murb_alloc (struct oxu_hcd*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  usb_pipebulk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int oxu_urb_enqueue(struct usb_hcd *hcd, struct urb *urb,
				gfp_t mem_flags)
{
	struct oxu_hcd *oxu = hcd_to_oxu(hcd);
	int num, rem;
	int transfer_buffer_length;
	void *transfer_buffer;
	struct urb *murb;
	int i, ret;

	/* If not bulk pipe just enqueue the URB */
	if (!usb_pipebulk(urb->pipe))
		return __oxu_urb_enqueue(hcd, urb, mem_flags);

	/* Otherwise we should verify the USB transfer buffer size! */
	transfer_buffer = urb->transfer_buffer;
	transfer_buffer_length = urb->transfer_buffer_length;

	num = urb->transfer_buffer_length / 4096;
	rem = urb->transfer_buffer_length % 4096;
	if (rem != 0)
		num++;

	/* If URB is smaller than 4096 bytes just enqueue it! */
	if (num == 1)
		return __oxu_urb_enqueue(hcd, urb, mem_flags);

	/* Ok, we have more job to do! :) */

	for (i = 0; i < num - 1; i++) {
		/* Get free micro URB poll till a free urb is recieved */

		do {
			murb = (struct urb *) oxu_murb_alloc(oxu);
			if (!murb)
				schedule();
		} while (!murb);

		/* Coping the urb */
		memcpy(murb, urb, sizeof(struct urb));

		murb->transfer_buffer_length = 4096;
		murb->transfer_buffer = transfer_buffer + i * 4096;

		/* Null pointer for the encodes that this is a micro urb */
		murb->complete = NULL;

		((struct oxu_murb *) murb)->main = urb;
		((struct oxu_murb *) murb)->last = 0;

		/* This loop is to guarantee urb to be processed when there's
		 * not enough resources at a particular time by retrying.
		 */
		do {
			ret  = __oxu_urb_enqueue(hcd, murb, mem_flags);
			if (ret)
				schedule();
		} while (ret);
	}

	/* Last urb requires special handling  */

	/* Get free micro URB poll till a free urb is recieved */
	do {
		murb = (struct urb *) oxu_murb_alloc(oxu);
		if (!murb)
			schedule();
	} while (!murb);

	/* Coping the urb */
	memcpy(murb, urb, sizeof(struct urb));

	murb->transfer_buffer_length = rem > 0 ? rem : 4096;
	murb->transfer_buffer = transfer_buffer + (num - 1) * 4096;

	/* Null pointer for the encodes that this is a micro urb */
	murb->complete = NULL;

	((struct oxu_murb *) murb)->main = urb;
	((struct oxu_murb *) murb)->last = 1;

	do {
		ret = __oxu_urb_enqueue(hcd, murb, mem_flags);
		if (ret)
			schedule();
	} while (ret);

	return ret;
}