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
struct xhci_hcd {TYPE_3__** devs; } ;
struct TYPE_6__ {TYPE_2__* eps; } ;
struct TYPE_5__ {TYPE_1__* ring; } ;
struct TYPE_4__ {scalar_t__ dequeue; } ;

/* Variables and functions */
 int LAST_EP_INDEX ; 
 int /*<<< orphan*/  xhci_ring_ep_doorbell (struct xhci_hcd*,int,int,int /*<<< orphan*/ ) ; 

void xhci_ring_device(struct xhci_hcd *xhci, int slot_id)
{
	int i;

	for (i = 0; i < LAST_EP_INDEX + 1; i++)
		if (xhci->devs[slot_id]->eps[i].ring &&
		    xhci->devs[slot_id]->eps[i].ring->dequeue)
			xhci_ring_ep_doorbell(xhci, slot_id, i, 0);

	return;
}