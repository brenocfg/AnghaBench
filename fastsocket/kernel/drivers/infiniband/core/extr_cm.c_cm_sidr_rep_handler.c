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
struct cm_work {TYPE_1__* mad_recv_wc; } ;
struct cm_sidr_rep_msg {int /*<<< orphan*/  request_id; } ;
struct TYPE_9__ {TYPE_3__* port; } ;
struct TYPE_7__ {scalar_t__ state; } ;
struct cm_id_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  msg; TYPE_4__ av; TYPE_2__ id; } ;
struct TYPE_10__ {scalar_t__ mad; } ;
struct TYPE_8__ {int /*<<< orphan*/  mad_agent; } ;
struct TYPE_6__ {TYPE_5__ recv_buf; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_CM_IDLE ; 
 scalar_t__ IB_CM_SIDR_REQ_SENT ; 
 struct cm_id_private* cm_acquire_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_deref_id (struct cm_id_private*) ; 
 int /*<<< orphan*/  cm_format_sidr_rep_event (struct cm_work*) ; 
 int /*<<< orphan*/  cm_process_work (struct cm_id_private*,struct cm_work*) ; 
 int /*<<< orphan*/  ib_cancel_mad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm_sidr_rep_handler(struct cm_work *work)
{
	struct cm_sidr_rep_msg *sidr_rep_msg;
	struct cm_id_private *cm_id_priv;

	sidr_rep_msg = (struct cm_sidr_rep_msg *)
				work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_id(sidr_rep_msg->request_id, 0);
	if (!cm_id_priv)
		return -EINVAL; /* Unmatched reply. */

	spin_lock_irq(&cm_id_priv->lock);
	if (cm_id_priv->id.state != IB_CM_SIDR_REQ_SENT) {
		spin_unlock_irq(&cm_id_priv->lock);
		goto out;
	}
	cm_id_priv->id.state = IB_CM_IDLE;
	ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
	spin_unlock_irq(&cm_id_priv->lock);

	cm_format_sidr_rep_event(work);
	cm_process_work(cm_id_priv, work);
	return 0;
out:
	cm_deref_id(cm_id_priv);
	return -EINVAL;
}