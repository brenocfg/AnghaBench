#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int echo; } ;
struct TYPE_7__ {TYPE_1__ eth_event; } ;
struct TYPE_8__ {TYPE_2__ data; } ;
union event_ring_elem {TYPE_3__ message; } ;
struct TYPE_9__ {int (* complete ) (struct bnx2x*,TYPE_4__*,union event_ring_elem*,unsigned long*) ;} ;
struct TYPE_10__ {int (* complete ) (struct bnx2x*,TYPE_5__*,union event_ring_elem*,unsigned long*) ;} ;
struct bnx2x_vf_queue {TYPE_4__ vlan_obj; TYPE_5__ mac_obj; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
#define  BNX2X_FILTER_MAC_PENDING 129 
#define  BNX2X_FILTER_VLAN_PENDING 128 
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int BNX2X_SWCID_SHIFT ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RAMROD_CONT ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int stub1 (struct bnx2x*,TYPE_5__*,union event_ring_elem*,unsigned long*) ; 
 int stub2 (struct bnx2x*,TYPE_4__*,union event_ring_elem*,unsigned long*) ; 

__attribute__((used)) static
void bnx2x_vf_handle_classification_eqe(struct bnx2x *bp,
					struct bnx2x_vf_queue *vfq,
					union event_ring_elem *elem)
{
	unsigned long ramrod_flags = 0;
	int rc = 0;

	/* Always push next commands out, don't wait here */
	set_bit(RAMROD_CONT, &ramrod_flags);

	switch (elem->message.data.eth_event.echo >> BNX2X_SWCID_SHIFT) {
	case BNX2X_FILTER_MAC_PENDING:
		rc = vfq->mac_obj.complete(bp, &vfq->mac_obj, elem,
					   &ramrod_flags);
		break;
	case BNX2X_FILTER_VLAN_PENDING:
		rc = vfq->vlan_obj.complete(bp, &vfq->vlan_obj, elem,
					    &ramrod_flags);
		break;
	default:
		BNX2X_ERR("Unsupported classification command: %d\n",
			  elem->message.data.eth_event.echo);
		return;
	}
	if (rc < 0)
		BNX2X_ERR("Failed to schedule new commands: %d\n", rc);
	else if (rc > 0)
		DP(BNX2X_MSG_IOV, "Scheduled next pending commands...\n");
}