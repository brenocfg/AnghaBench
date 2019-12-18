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
struct xhci_ring {unsigned int num_segs; int type; TYPE_3__* last_seg; int /*<<< orphan*/  first_seg; int /*<<< orphan*/  td_list; } ;
struct xhci_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum xhci_ring_type { ____Placeholder_xhci_ring_type } xhci_ring_type ;
struct TYPE_6__ {TYPE_2__* trbs; } ;
struct TYPE_4__ {int /*<<< orphan*/  control; } ;
struct TYPE_5__ {TYPE_1__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LINK_TOGGLE ; 
 int TRBS_PER_SEGMENT ; 
 int TYPE_EVENT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct xhci_ring*) ; 
 struct xhci_ring* kzalloc (int,int /*<<< orphan*/ ) ; 
 int xhci_alloc_segments_for_ring (struct xhci_hcd*,int /*<<< orphan*/ *,TYPE_3__**,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_initialize_ring_info (struct xhci_ring*,unsigned int) ; 

__attribute__((used)) static struct xhci_ring *xhci_ring_alloc(struct xhci_hcd *xhci,
		unsigned int num_segs, unsigned int cycle_state,
		enum xhci_ring_type type, gfp_t flags)
{
	struct xhci_ring	*ring;
	int ret;

	ring = kzalloc(sizeof *(ring), flags);
	if (!ring)
		return NULL;

	ring->num_segs = num_segs;
	INIT_LIST_HEAD(&ring->td_list);
	ring->type = type;
	if (num_segs == 0)
		return ring;

	ret = xhci_alloc_segments_for_ring(xhci, &ring->first_seg,
			&ring->last_seg, num_segs, cycle_state, type, flags);
	if (ret)
		goto fail;

	/* Only event ring does not use link TRB */
	if (type != TYPE_EVENT) {
		/* See section 4.9.2.1 and 6.4.4.1 */
		ring->last_seg->trbs[TRBS_PER_SEGMENT - 1].link.control |=
			cpu_to_le32(LINK_TOGGLE);
	}
	xhci_initialize_ring_info(ring, cycle_state);
	return ring;

fail:
	kfree(ring);
	return NULL;
}