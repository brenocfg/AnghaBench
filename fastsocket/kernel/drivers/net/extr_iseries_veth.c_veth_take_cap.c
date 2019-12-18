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
struct TYPE_2__ {int /*<<< orphan*/  xRc; } ;
struct veth_lpevent {TYPE_1__ base_event; } ;
struct veth_lpar_connection {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  cap_event; int /*<<< orphan*/  remote_lp; int /*<<< orphan*/  dst_inst; } ;
struct HvLpEvent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HvCallEvent_ackLpEvent (struct HvLpEvent*) ; 
 int /*<<< orphan*/  HvCallEvent_getTargetLpInstanceId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HvLpEvent_Rc_BufferNotAvailable ; 
 int /*<<< orphan*/  HvLpEvent_Type_VirtualLan ; 
 int VETH_STATE_GOTCAPS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct veth_lpevent*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  veth_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  veth_kick_statemachine (struct veth_lpar_connection*) ; 

__attribute__((used)) static void veth_take_cap(struct veth_lpar_connection *cnx,
			  struct veth_lpevent *event)
{
	unsigned long flags;

	spin_lock_irqsave(&cnx->lock, flags);
	/* Receiving caps may mean the other end has just come up, so
	 * we need to reload the instance ID of the far end */
	cnx->dst_inst =
		HvCallEvent_getTargetLpInstanceId(cnx->remote_lp,
						  HvLpEvent_Type_VirtualLan);

	if (cnx->state & VETH_STATE_GOTCAPS) {
		veth_error("Received a second capabilities from LPAR %d.\n",
			   cnx->remote_lp);
		event->base_event.xRc = HvLpEvent_Rc_BufferNotAvailable;
		HvCallEvent_ackLpEvent((struct HvLpEvent *) event);
	} else {
		memcpy(&cnx->cap_event, event, sizeof(cnx->cap_event));
		cnx->state |= VETH_STATE_GOTCAPS;
		veth_kick_statemachine(cnx);
	}
	spin_unlock_irqrestore(&cnx->lock, flags);
}