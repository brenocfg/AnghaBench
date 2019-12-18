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
struct urb {scalar_t__ interval; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  pipe; TYPE_1__* dev; } ;
struct ehci_iso_stream {scalar_t__ interval; } ;
struct ehci_hcd {int periodic_size; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  devpath; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*,...) ; 
 int /*<<< orphan*/  ehci_to_hcd (struct ehci_hcd*) ; 
 struct ehci_iso_stream* iso_stream_find (struct ehci_hcd*,struct urb*) ; 
 int /*<<< orphan*/  iso_stream_put (struct ehci_hcd*,struct ehci_iso_stream*) ; 
 int iso_stream_schedule (struct ehci_hcd*,struct urb*,struct ehci_iso_stream*) ; 
 int /*<<< orphan*/  sitd_link_urb (struct ehci_hcd*,struct urb*,int,struct ehci_iso_stream*) ; 
 int sitd_urb_transaction (struct ehci_iso_stream*,struct ehci_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int usb_hcd_link_urb_to_ep (int /*<<< orphan*/ ,struct urb*) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (int /*<<< orphan*/ ,struct urb*) ; 
 int /*<<< orphan*/  usb_pipeendpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sitd_submit (struct ehci_hcd *ehci, struct urb *urb,
	gfp_t mem_flags)
{
	int			status = -EINVAL;
	unsigned long		flags;
	struct ehci_iso_stream	*stream;

	/* Get iso_stream head */
	stream = iso_stream_find (ehci, urb);
	if (stream == NULL) {
		ehci_dbg (ehci, "can't get iso stream\n");
		return -ENOMEM;
	}
	if (urb->interval != stream->interval) {
		ehci_dbg (ehci, "can't change iso interval %d --> %d\n",
			stream->interval, urb->interval);
		goto done;
	}

#ifdef EHCI_URB_TRACE
	ehci_dbg (ehci,
		"submit %p dev%s ep%d%s-iso len %d\n",
		urb, urb->dev->devpath,
		usb_pipeendpoint (urb->pipe),
		usb_pipein (urb->pipe) ? "in" : "out",
		urb->transfer_buffer_length);
#endif

	/* allocate SITDs */
	status = sitd_urb_transaction (stream, ehci, urb, mem_flags);
	if (status < 0) {
		ehci_dbg (ehci, "can't init sitds\n");
		goto done;
	}

	/* schedule ... need to lock */
	spin_lock_irqsave (&ehci->lock, flags);
	if (unlikely(!HCD_HW_ACCESSIBLE(ehci_to_hcd(ehci)))) {
		status = -ESHUTDOWN;
		goto done_not_linked;
	}
	status = usb_hcd_link_urb_to_ep(ehci_to_hcd(ehci), urb);
	if (unlikely(status))
		goto done_not_linked;
	status = iso_stream_schedule(ehci, urb, stream);
	if (status == 0)
		sitd_link_urb (ehci, urb, ehci->periodic_size << 3, stream);
	else
		usb_hcd_unlink_urb_from_ep(ehci_to_hcd(ehci), urb);
done_not_linked:
	spin_unlock_irqrestore (&ehci->lock, flags);

done:
	if (status < 0)
		iso_stream_put (ehci, stream);
	return status;
}