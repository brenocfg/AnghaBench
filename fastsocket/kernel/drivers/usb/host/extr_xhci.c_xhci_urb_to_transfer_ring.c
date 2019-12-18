#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xhci_virt_ep {int ep_state; TYPE_4__* stream_info; struct xhci_ring* ring; } ;
struct xhci_ring {int dummy; } ;
struct xhci_hcd {TYPE_3__** devs; } ;
struct urb {unsigned int stream_id; TYPE_2__* ep; TYPE_1__* dev; } ;
struct TYPE_8__ {unsigned int num_streams; struct xhci_ring** stream_rings; } ;
struct TYPE_7__ {struct xhci_virt_ep* eps; } ;
struct TYPE_6__ {int /*<<< orphan*/  desc; } ;
struct TYPE_5__ {unsigned int slot_id; } ;

/* Variables and functions */
 int EP_HAS_STREAMS ; 
 unsigned int xhci_get_endpoint_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*,unsigned int,unsigned int,...) ; 

__attribute__((used)) static struct xhci_ring *xhci_urb_to_transfer_ring(struct xhci_hcd *xhci,
		struct urb *urb)
{
	unsigned int slot_id;
	unsigned int ep_index;
	unsigned int stream_id;
	struct xhci_virt_ep *ep;

	slot_id = urb->dev->slot_id;
	ep_index = xhci_get_endpoint_index(&urb->ep->desc);
	stream_id = urb->stream_id;
	ep = &xhci->devs[slot_id]->eps[ep_index];
	/* Common case: no streams */
	if (!(ep->ep_state & EP_HAS_STREAMS))
		return ep->ring;

	if (stream_id == 0) {
		xhci_warn(xhci,
				"WARN: Slot ID %u, ep index %u has streams, "
				"but URB has no stream ID.\n",
				slot_id, ep_index);
		return NULL;
	}

	if (stream_id < ep->stream_info->num_streams)
		return ep->stream_info->stream_rings[stream_id];

	xhci_warn(xhci,
			"WARN: Slot ID %u, ep index %u has "
			"stream IDs 1 to %u allocated, "
			"but stream ID %u is requested.\n",
			slot_id, ep_index,
			ep->stream_info->num_streams - 1,
			stream_id);
	return NULL;
}