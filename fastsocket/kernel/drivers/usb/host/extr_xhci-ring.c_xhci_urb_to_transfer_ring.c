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
struct xhci_ring {int dummy; } ;
struct xhci_hcd {int dummy; } ;
struct urb {int /*<<< orphan*/  stream_id; TYPE_2__* ep; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  slot_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  xhci_get_endpoint_index (int /*<<< orphan*/ *) ; 
 struct xhci_ring* xhci_triad_to_transfer_ring (struct xhci_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xhci_ring *xhci_urb_to_transfer_ring(struct xhci_hcd *xhci,
		struct urb *urb)
{
	return xhci_triad_to_transfer_ring(xhci, urb->dev->slot_id,
		xhci_get_endpoint_index(&urb->ep->desc), urb->stream_id);
}