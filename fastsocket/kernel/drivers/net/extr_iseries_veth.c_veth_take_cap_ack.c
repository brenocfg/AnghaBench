#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct veth_lpevent {int dummy; } ;
struct veth_lpar_connection {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  cap_ack_event; int /*<<< orphan*/  remote_lp; } ;

/* Variables and functions */
 int VETH_STATE_GOTCAPACK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct veth_lpevent*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  veth_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  veth_kick_statemachine (struct veth_lpar_connection*) ; 

__attribute__((used)) static void veth_take_cap_ack(struct veth_lpar_connection *cnx,
			      struct veth_lpevent *event)
{
	unsigned long flags;

	spin_lock_irqsave(&cnx->lock, flags);
	if (cnx->state & VETH_STATE_GOTCAPACK) {
		veth_error("Received a second capabilities ack from LPAR %d.\n",
			   cnx->remote_lp);
	} else {
		memcpy(&cnx->cap_ack_event, event,
		       sizeof(cnx->cap_ack_event));
		cnx->state |= VETH_STATE_GOTCAPACK;
		veth_kick_statemachine(cnx);
	}
	spin_unlock_irqrestore(&cnx->lock, flags);
}