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
struct ib_mad_send_wr_private {scalar_t__ status; int refcount; scalar_t__ timeout; int /*<<< orphan*/  agent_list; struct ib_mad_agent_private* mad_agent_priv; } ;
struct ib_mad_send_wc {scalar_t__ status; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_handler ) (TYPE_1__*,struct ib_mad_send_wc*) ;scalar_t__ rmpp_version; } ;
struct ib_mad_agent_private {int /*<<< orphan*/  lock; TYPE_1__ agent; } ;

/* Variables and functions */
 int IB_RMPP_RESULT_CONSUMED ; 
 int IB_RMPP_RESULT_INTERNAL ; 
 int IB_RMPP_RESULT_UNHANDLED ; 
 scalar_t__ IB_WC_SUCCESS ; 
 int /*<<< orphan*/  adjust_timeout (struct ib_mad_agent_private*) ; 
 int /*<<< orphan*/  deref_mad_agent (struct ib_mad_agent_private*) ; 
 int ib_process_rmpp_send_wc (struct ib_mad_send_wr_private*,struct ib_mad_send_wc*) ; 
 int /*<<< orphan*/  ib_rmpp_send_handler (struct ib_mad_send_wc*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct ib_mad_send_wc*) ; 
 int /*<<< orphan*/  wait_for_response (struct ib_mad_send_wr_private*) ; 

void ib_mad_complete_send_wr(struct ib_mad_send_wr_private *mad_send_wr,
			     struct ib_mad_send_wc *mad_send_wc)
{
	struct ib_mad_agent_private	*mad_agent_priv;
	unsigned long			flags;
	int				ret;

	mad_agent_priv = mad_send_wr->mad_agent_priv;
	spin_lock_irqsave(&mad_agent_priv->lock, flags);
	if (mad_agent_priv->agent.rmpp_version) {
		ret = ib_process_rmpp_send_wc(mad_send_wr, mad_send_wc);
		if (ret == IB_RMPP_RESULT_CONSUMED)
			goto done;
	} else
		ret = IB_RMPP_RESULT_UNHANDLED;

	if (mad_send_wc->status != IB_WC_SUCCESS &&
	    mad_send_wr->status == IB_WC_SUCCESS) {
		mad_send_wr->status = mad_send_wc->status;
		mad_send_wr->refcount -= (mad_send_wr->timeout > 0);
	}

	if (--mad_send_wr->refcount > 0) {
		if (mad_send_wr->refcount == 1 && mad_send_wr->timeout &&
		    mad_send_wr->status == IB_WC_SUCCESS) {
			wait_for_response(mad_send_wr);
		}
		goto done;
	}

	/* Remove send from MAD agent and notify client of completion */
	list_del(&mad_send_wr->agent_list);
	adjust_timeout(mad_agent_priv);
	spin_unlock_irqrestore(&mad_agent_priv->lock, flags);

	if (mad_send_wr->status != IB_WC_SUCCESS )
		mad_send_wc->status = mad_send_wr->status;
	if (ret == IB_RMPP_RESULT_INTERNAL)
		ib_rmpp_send_handler(mad_send_wc);
	else
		mad_agent_priv->agent.send_handler(&mad_agent_priv->agent,
						   mad_send_wc);

	/* Release reference on agent taken when sending */
	deref_mad_agent(mad_agent_priv);
	return;
done:
	spin_unlock_irqrestore(&mad_agent_priv->lock, flags);
}