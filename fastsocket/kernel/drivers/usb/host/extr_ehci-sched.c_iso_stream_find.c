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
struct usb_host_endpoint {struct ehci_iso_stream* hcpriv; } ;
struct urb {int /*<<< orphan*/  pipe; TYPE_1__* dev; int /*<<< orphan*/  interval; } ;
struct ehci_iso_stream {int /*<<< orphan*/ * hw; struct usb_host_endpoint* ep; } ;
struct ehci_hcd {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  devpath; struct usb_host_endpoint** ep_out; struct usb_host_endpoint** ep_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*,int /*<<< orphan*/ ,unsigned int,char*) ; 
 struct ehci_iso_stream* iso_stream_alloc (int /*<<< orphan*/ ) ; 
 struct ehci_iso_stream* iso_stream_get (struct ehci_iso_stream*) ; 
 int /*<<< orphan*/  iso_stream_init (struct ehci_hcd*,struct ehci_iso_stream*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 unsigned int usb_pipeendpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ehci_iso_stream *
iso_stream_find (struct ehci_hcd *ehci, struct urb *urb)
{
	unsigned		epnum;
	struct ehci_iso_stream	*stream;
	struct usb_host_endpoint *ep;
	unsigned long		flags;

	epnum = usb_pipeendpoint (urb->pipe);
	if (usb_pipein(urb->pipe))
		ep = urb->dev->ep_in[epnum];
	else
		ep = urb->dev->ep_out[epnum];

	spin_lock_irqsave (&ehci->lock, flags);
	stream = ep->hcpriv;

	if (unlikely (stream == NULL)) {
		stream = iso_stream_alloc(GFP_ATOMIC);
		if (likely (stream != NULL)) {
			/* dev->ep owns the initial refcount */
			ep->hcpriv = stream;
			stream->ep = ep;
			iso_stream_init(ehci, stream, urb->dev, urb->pipe,
					urb->interval);
		}

	/* if dev->ep [epnum] is a QH, hw is set */
	} else if (unlikely (stream->hw != NULL)) {
		ehci_dbg (ehci, "dev %s ep%d%s, not iso??\n",
			urb->dev->devpath, epnum,
			usb_pipein(urb->pipe) ? "in" : "out");
		stream = NULL;
	}

	/* caller guarantees an eventual matching iso_stream_put */
	stream = iso_stream_get (stream);

	spin_unlock_irqrestore (&ehci->lock, flags);
	return stream;
}