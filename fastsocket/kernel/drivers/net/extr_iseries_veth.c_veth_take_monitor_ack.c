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
struct veth_lpar_connection {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  remote_lp; } ;

/* Variables and functions */
 int VETH_STATE_RESET ; 
 int VETH_STATE_SHUTDOWN ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  veth_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  veth_kick_statemachine (struct veth_lpar_connection*) ; 

__attribute__((used)) static void veth_take_monitor_ack(struct veth_lpar_connection *cnx,
				  struct veth_lpevent *event)
{
	unsigned long flags;

	spin_lock_irqsave(&cnx->lock, flags);
	veth_debug("cnx %d: lost connection.\n", cnx->remote_lp);

	/* Avoid kicking the statemachine once we're shutdown.
	 * It's unnecessary and it could break veth_stop_connection(). */

	if (! (cnx->state & VETH_STATE_SHUTDOWN)) {
		cnx->state |= VETH_STATE_RESET;
		veth_kick_statemachine(cnx);
	}
	spin_unlock_irqrestore(&cnx->lock, flags);
}