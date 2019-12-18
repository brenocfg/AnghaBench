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
struct veth_lpar_connection {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  statemachine_wq; } ;

/* Variables and functions */
 int VETH_STATE_RESET ; 
 int VETH_STATE_SHUTDOWN ; 
 scalar_t__ cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  veth_kick_statemachine (struct veth_lpar_connection*) ; 

__attribute__((used)) static void veth_stop_connection(struct veth_lpar_connection *cnx)
{
	if (!cnx)
		return;

	spin_lock_irq(&cnx->lock);
	cnx->state |= VETH_STATE_RESET | VETH_STATE_SHUTDOWN;
	veth_kick_statemachine(cnx);
	spin_unlock_irq(&cnx->lock);

	/* There's a slim chance the reset code has just queued the
	 * statemachine to run in five seconds. If so we need to cancel
	 * that and requeue the work to run now. */
	if (cancel_delayed_work(&cnx->statemachine_wq)) {
		spin_lock_irq(&cnx->lock);
		veth_kick_statemachine(cnx);
		spin_unlock_irq(&cnx->lock);
	}

	/* Wait for the state machine to run. */
	flush_scheduled_work();
}