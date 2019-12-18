#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct usb_iso_packet_descriptor {scalar_t__ actual_length; scalar_t__ length; int /*<<< orphan*/  status; } ;
struct usb_device {int /*<<< orphan*/  devpath; } ;
struct urb {int number_of_packets; struct usb_device* dev; int /*<<< orphan*/  actual_length; int /*<<< orphan*/  pipe; int /*<<< orphan*/  error_count; struct usb_iso_packet_descriptor* iso_frame_desc; } ;
struct ehci_sitd {int index; scalar_t__ frame; int /*<<< orphan*/  sitd_list; struct ehci_iso_stream* stream; struct urb* urb; int /*<<< orphan*/  hw_results; } ;
struct ehci_iso_stream {int depth; int interval; int bEndpointAddress; int refcount; TYPE_2__* ep; int /*<<< orphan*/  free_list; scalar_t__ bandwidth; int /*<<< orphan*/  td_list; } ;
struct ehci_hcd {int amd_pll_fix; scalar_t__ clock_frame; int /*<<< orphan*/  cached_sitd_list; } ;
struct TYPE_4__ {scalar_t__ bandwidth_isoc_reqs; int /*<<< orphan*/  bandwidth_allocated; } ;
struct TYPE_6__ {TYPE_1__ self; } ;
struct TYPE_5__ {int /*<<< orphan*/ * hcpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECOMM ; 
 int /*<<< orphan*/  ENOSR ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  EPROTO ; 
 int SITD_ERRS ; 
 scalar_t__ SITD_LENGTH (int) ; 
 int SITD_STS_BABBLE ; 
 int SITD_STS_DBE ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  disable_periodic (struct ehci_hcd*) ; 
 TYPE_3__* ehci_to_hcd (struct ehci_hcd*) ; 
 int /*<<< orphan*/  ehci_urb_done (struct ehci_hcd*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_vdbg (struct ehci_hcd*,char*,int /*<<< orphan*/ ,int,char*) ; 
 int hc32_to_cpup (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iso_stream_put (struct ehci_hcd*,struct ehci_iso_stream*) ; 
 scalar_t__ list_is_singular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_amd_quirk_pll_enable () ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
sitd_complete (
	struct ehci_hcd		*ehci,
	struct ehci_sitd	*sitd
) {
	struct urb				*urb = sitd->urb;
	struct usb_iso_packet_descriptor	*desc;
	u32					t;
	int					urb_index = -1;
	struct ehci_iso_stream			*stream = sitd->stream;
	struct usb_device			*dev;
	unsigned				retval = false;

	urb_index = sitd->index;
	desc = &urb->iso_frame_desc [urb_index];
	t = hc32_to_cpup(ehci, &sitd->hw_results);

	/* report transfer status */
	if (t & SITD_ERRS) {
		urb->error_count++;
		if (t & SITD_STS_DBE)
			desc->status = usb_pipein (urb->pipe)
				? -ENOSR  /* hc couldn't read */
				: -ECOMM; /* hc couldn't write */
		else if (t & SITD_STS_BABBLE)
			desc->status = -EOVERFLOW;
		else /* XACT, MMF, etc */
			desc->status = -EPROTO;
	} else {
		desc->status = 0;
		desc->actual_length = desc->length - SITD_LENGTH(t);
		urb->actual_length += desc->actual_length;
	}
	stream->depth -= stream->interval << 3;

	/* handle completion now? */
	if ((urb_index + 1) != urb->number_of_packets)
		goto done;

	/* ASSERT: it's really the last sitd for this urb
	list_for_each_entry (sitd, &stream->td_list, sitd_list)
		BUG_ON (sitd->urb == urb);
	 */

	/* give urb back to the driver; completion often (re)submits */
	dev = urb->dev;
	ehci_urb_done(ehci, urb, 0);
	retval = true;
	urb = NULL;
	(void) disable_periodic(ehci);
	ehci_to_hcd(ehci)->self.bandwidth_isoc_reqs--;

	if (ehci_to_hcd(ehci)->self.bandwidth_isoc_reqs == 0) {
		if (ehci->amd_pll_fix == 1)
			usb_amd_quirk_pll_enable();
	}

	if (list_is_singular(&stream->td_list)) {
		ehci_to_hcd(ehci)->self.bandwidth_allocated
				-= stream->bandwidth;
		ehci_vdbg (ehci,
			"deschedule devp %s ep%d%s-iso\n",
			dev->devpath, stream->bEndpointAddress & 0x0f,
			(stream->bEndpointAddress & USB_DIR_IN) ? "in" : "out");
	}
	iso_stream_put (ehci, stream);

done:
	sitd->urb = NULL;
	if (ehci->clock_frame != sitd->frame) {
		/* OK to recycle this SITD now. */
		sitd->stream = NULL;
		list_move(&sitd->sitd_list, &stream->free_list);
		iso_stream_put(ehci, stream);
	} else {
		/* HW might remember this SITD, so we can't recycle it yet.
		 * Move it to a safe place until a new frame starts.
		 */
		list_move(&sitd->sitd_list, &ehci->cached_sitd_list);
		if (stream->refcount == 2) {
			/* If iso_stream_put() were called here, stream
			 * would be freed.  Instead, just prevent reuse.
			 */
			stream->ep->hcpriv = NULL;
			stream->ep = NULL;
		}
	}
	return retval;
}