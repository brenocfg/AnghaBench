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
struct xhci_ring {TYPE_1__* enqueue; } ;
struct xhci_link_trb {int /*<<< orphan*/  control; } ;
struct TYPE_2__ {struct xhci_link_trb link; } ;

/* Variables and functions */
 int TRB_TYPE_LINK_LE32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enqueue_is_link_trb(struct xhci_ring *ring)
{
	struct xhci_link_trb *link = &ring->enqueue->link;
	return TRB_TYPE_LINK_LE32(link->control);
}