#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ib_mad_port_private {int /*<<< orphan*/  wq; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  mr; } ;
struct ib_mad_agent_private {TYPE_1__ agent; struct ib_mad_agent_private* reg_req; int /*<<< orphan*/  comp; int /*<<< orphan*/  agent_list; int /*<<< orphan*/  timed_work; TYPE_2__* qp_info; } ;
struct TYPE_4__ {struct ib_mad_port_private* port_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_mads (struct ib_mad_agent_private*) ; 
 int /*<<< orphan*/  deref_mad_agent (struct ib_mad_agent_private*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_cancel_rmpp_recvs (struct ib_mad_agent_private*) ; 
 int /*<<< orphan*/  ib_dereg_mr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_mad_agent_private*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_mad_reg_req (struct ib_mad_agent_private*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unregister_mad_agent(struct ib_mad_agent_private *mad_agent_priv)
{
	struct ib_mad_port_private *port_priv;
	unsigned long flags;

	/* Note that we could still be handling received MADs */

	/*
	 * Canceling all sends results in dropping received response
	 * MADs, preventing us from queuing additional work
	 */
	cancel_mads(mad_agent_priv);
	port_priv = mad_agent_priv->qp_info->port_priv;
	cancel_delayed_work(&mad_agent_priv->timed_work);

	spin_lock_irqsave(&port_priv->reg_lock, flags);
	remove_mad_reg_req(mad_agent_priv);
	list_del(&mad_agent_priv->agent_list);
	spin_unlock_irqrestore(&port_priv->reg_lock, flags);

	flush_workqueue(port_priv->wq);
	ib_cancel_rmpp_recvs(mad_agent_priv);

	deref_mad_agent(mad_agent_priv);
	wait_for_completion(&mad_agent_priv->comp);

	kfree(mad_agent_priv->reg_req);
	ib_dereg_mr(mad_agent_priv->agent.mr);
	kfree(mad_agent_priv);
}