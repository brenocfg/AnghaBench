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
struct veth_lpar_connection {scalar_t__ outstanding_tx; unsigned long last_contact; unsigned long reset_timeout; int /*<<< orphan*/  lock; int /*<<< orphan*/  reset_timer; int /*<<< orphan*/  remote_lp; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  VETH_STATE_RESET ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  veth_error (char*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  veth_kick_statemachine (struct veth_lpar_connection*) ; 

__attribute__((used)) static void veth_timed_reset(unsigned long ptr)
{
	struct veth_lpar_connection *cnx = (struct veth_lpar_connection *)ptr;
	unsigned long trigger_time, flags;

	/* FIXME is it possible this fires after veth_stop_connection()?
	 * That would reschedule the statemachine for 5 seconds and probably
	 * execute it after the module's been unloaded. Hmm. */

	spin_lock_irqsave(&cnx->lock, flags);

	if (cnx->outstanding_tx > 0) {
		trigger_time = cnx->last_contact + cnx->reset_timeout;

		if (trigger_time < jiffies) {
			cnx->state |= VETH_STATE_RESET;
			veth_kick_statemachine(cnx);
			veth_error("%d packets not acked by LPAR %d within %d "
					"seconds, resetting.\n",
					cnx->outstanding_tx, cnx->remote_lp,
					cnx->reset_timeout / HZ);
		} else {
			/* Reschedule the timer */
			trigger_time = jiffies + cnx->reset_timeout;
			mod_timer(&cnx->reset_timer, trigger_time);
		}
	}

	spin_unlock_irqrestore(&cnx->lock, flags);
}