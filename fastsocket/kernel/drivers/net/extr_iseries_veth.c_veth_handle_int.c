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
typedef  scalar_t__ u16 ;
struct TYPE_6__ {size_t xSourceLp; int xSubtype; } ;
struct TYPE_4__ {scalar_t__* token; } ;
struct TYPE_5__ {TYPE_1__ frames_ack_data; } ;
struct veth_lpevent {TYPE_3__ base_event; TYPE_2__ u; } ;
struct veth_lpar_connection {int /*<<< orphan*/  lock; int /*<<< orphan*/  last_contact; int /*<<< orphan*/  outstanding_tx; scalar_t__ msgs; } ;
typedef  size_t HvLpIndex ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  VETH_EVENT_CAP 131 
#define  VETH_EVENT_FRAMES 130 
#define  VETH_EVENT_FRAMES_ACK 129 
#define  VETH_EVENT_MONITOR 128 
 int VETH_MAX_ACKS_PER_MSG ; 
 scalar_t__ VETH_NUMBUFFERS ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct veth_lpar_connection** veth_cnx ; 
 int /*<<< orphan*/  veth_error (char*,int,size_t) ; 
 int /*<<< orphan*/  veth_receive (struct veth_lpar_connection*,struct veth_lpevent*) ; 
 int /*<<< orphan*/  veth_recycle_msg (struct veth_lpar_connection*,scalar_t__) ; 
 int /*<<< orphan*/  veth_take_cap (struct veth_lpar_connection*,struct veth_lpevent*) ; 
 int /*<<< orphan*/  veth_wake_queues (struct veth_lpar_connection*) ; 

__attribute__((used)) static void veth_handle_int(struct veth_lpevent *event)
{
	HvLpIndex rlp = event->base_event.xSourceLp;
	struct veth_lpar_connection *cnx = veth_cnx[rlp];
	unsigned long flags;
	int i, acked = 0;

	BUG_ON(! cnx);

	switch (event->base_event.xSubtype) {
	case VETH_EVENT_CAP:
		veth_take_cap(cnx, event);
		break;
	case VETH_EVENT_MONITOR:
		/* do nothing... this'll hang out here til we're dead,
		 * and the hypervisor will return it for us. */
		break;
	case VETH_EVENT_FRAMES_ACK:
		spin_lock_irqsave(&cnx->lock, flags);

		for (i = 0; i < VETH_MAX_ACKS_PER_MSG; ++i) {
			u16 msgnum = event->u.frames_ack_data.token[i];

			if (msgnum < VETH_NUMBUFFERS) {
				veth_recycle_msg(cnx, cnx->msgs + msgnum);
				cnx->outstanding_tx--;
				acked++;
			}
		}

		if (acked > 0) {
			cnx->last_contact = jiffies;
			veth_wake_queues(cnx);
		}

		spin_unlock_irqrestore(&cnx->lock, flags);
		break;
	case VETH_EVENT_FRAMES:
		veth_receive(cnx, event);
		break;
	default:
		veth_error("Unknown interrupt type %d from LPAR %d.\n",
				event->base_event.xSubtype, rlp);
	};
}