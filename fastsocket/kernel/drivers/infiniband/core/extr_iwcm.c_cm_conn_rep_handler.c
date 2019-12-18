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
struct TYPE_6__ {int (* cm_handler ) (TYPE_3__*,struct iw_cm_event*) ;TYPE_2__* device; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;
struct iwcm_id_private {scalar_t__ state; int /*<<< orphan*/  connect_wait; TYPE_3__ id; int /*<<< orphan*/  lock; int /*<<< orphan*/ * qp; int /*<<< orphan*/  flags; } ;
struct iw_cm_event {scalar_t__ status; int /*<<< orphan*/  private_data; scalar_t__ private_data_len; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;
struct TYPE_5__ {TYPE_1__* iwcm; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* rem_ref ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IWCM_F_CONNECT_WAIT ; 
 scalar_t__ IW_CM_STATE_CONN_SENT ; 
 scalar_t__ IW_CM_STATE_ESTABLISHED ; 
 scalar_t__ IW_CM_STATE_IDLE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_3__*,struct iw_cm_event*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm_conn_rep_handler(struct iwcm_id_private *cm_id_priv,
			       struct iw_cm_event *iw_event)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	/*
	 * Clear the connect wait bit so a callback function calling
	 * iw_cm_disconnect will not wait and deadlock this thread
	 */
	clear_bit(IWCM_F_CONNECT_WAIT, &cm_id_priv->flags);
	BUG_ON(cm_id_priv->state != IW_CM_STATE_CONN_SENT);
	if (iw_event->status == 0) {
		cm_id_priv->id.local_addr = iw_event->local_addr;
		cm_id_priv->id.remote_addr = iw_event->remote_addr;
		cm_id_priv->state = IW_CM_STATE_ESTABLISHED;
	} else {
		/* REJECTED or RESET */
		cm_id_priv->id.device->iwcm->rem_ref(cm_id_priv->qp);
		cm_id_priv->qp = NULL;
		cm_id_priv->state = IW_CM_STATE_IDLE;
	}
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	ret = cm_id_priv->id.cm_handler(&cm_id_priv->id, iw_event);

	if (iw_event->private_data_len)
		kfree(iw_event->private_data);

	/* Wake up waiters on connect complete */
	wake_up_all(&cm_id_priv->connect_wait);

	return ret;
}