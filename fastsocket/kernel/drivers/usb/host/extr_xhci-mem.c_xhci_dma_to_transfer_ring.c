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
typedef  int u64 ;
struct xhci_virt_ep {int ep_state; struct xhci_ring* ring; TYPE_1__* stream_info; } ;
struct xhci_ring {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  trb_address_map; } ;

/* Variables and functions */
 int EP_HAS_STREAMS ; 
 int TRB_SEGMENT_SHIFT ; 
 struct xhci_ring* radix_tree_lookup (int /*<<< orphan*/ *,int) ; 

struct xhci_ring *xhci_dma_to_transfer_ring(
		struct xhci_virt_ep *ep,
		u64 address)
{
	if (ep->ep_state & EP_HAS_STREAMS)
		return radix_tree_lookup(&ep->stream_info->trb_address_map,
				address >> TRB_SEGMENT_SHIFT);
	return ep->ring;
}