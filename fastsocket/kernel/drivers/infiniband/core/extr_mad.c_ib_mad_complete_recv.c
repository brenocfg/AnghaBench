#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ib_mad_send_wr_private {int /*<<< orphan*/  send_buf; } ;
struct ib_mad_send_wc {int /*<<< orphan*/ * send_buf; scalar_t__ vendor_err; int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int /*<<< orphan*/  mad; int /*<<< orphan*/  list; } ;
struct ib_mad_recv_wc {TYPE_2__* wc; TYPE_1__ recv_buf; int /*<<< orphan*/  rmpp_list; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* recv_handler ) (TYPE_3__*,struct ib_mad_recv_wc*) ;scalar_t__ rmpp_version; } ;
struct ib_mad_agent_private {TYPE_3__ agent; int /*<<< orphan*/  refcount; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {unsigned long wr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deref_mad_agent (struct ib_mad_agent_private*) ; 
 struct ib_mad_send_wr_private* ib_find_send_mad (struct ib_mad_agent_private*,struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  ib_free_recv_mad (struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  ib_mad_complete_send_wr (struct ib_mad_send_wr_private*,struct ib_mad_send_wc*) ; 
 int /*<<< orphan*/  ib_mark_mad_done (struct ib_mad_send_wr_private*) ; 
 struct ib_mad_recv_wc* ib_process_rmpp_recv_wc (struct ib_mad_agent_private*,struct ib_mad_recv_wc*) ; 
 scalar_t__ ib_response_mad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,struct ib_mad_recv_wc*) ; 

__attribute__((used)) static void ib_mad_complete_recv(struct ib_mad_agent_private *mad_agent_priv,
				 struct ib_mad_recv_wc *mad_recv_wc)
{
	struct ib_mad_send_wr_private *mad_send_wr;
	struct ib_mad_send_wc mad_send_wc;
	unsigned long flags;

	INIT_LIST_HEAD(&mad_recv_wc->rmpp_list);
	list_add(&mad_recv_wc->recv_buf.list, &mad_recv_wc->rmpp_list);
	if (mad_agent_priv->agent.rmpp_version) {
		mad_recv_wc = ib_process_rmpp_recv_wc(mad_agent_priv,
						      mad_recv_wc);
		if (!mad_recv_wc) {
			deref_mad_agent(mad_agent_priv);
			return;
		}
	}

	/* Complete corresponding request */
	if (ib_response_mad(mad_recv_wc->recv_buf.mad)) {
		spin_lock_irqsave(&mad_agent_priv->lock, flags);
		mad_send_wr = ib_find_send_mad(mad_agent_priv, mad_recv_wc);
		if (!mad_send_wr) {
			spin_unlock_irqrestore(&mad_agent_priv->lock, flags);
			ib_free_recv_mad(mad_recv_wc);
			deref_mad_agent(mad_agent_priv);
			return;
		}
		ib_mark_mad_done(mad_send_wr);
		spin_unlock_irqrestore(&mad_agent_priv->lock, flags);

		/* Defined behavior is to complete response before request */
		mad_recv_wc->wc->wr_id = (unsigned long) &mad_send_wr->send_buf;
		mad_agent_priv->agent.recv_handler(&mad_agent_priv->agent,
						   mad_recv_wc);
		atomic_dec(&mad_agent_priv->refcount);

		mad_send_wc.status = IB_WC_SUCCESS;
		mad_send_wc.vendor_err = 0;
		mad_send_wc.send_buf = &mad_send_wr->send_buf;
		ib_mad_complete_send_wr(mad_send_wr, &mad_send_wc);
	} else {
		mad_agent_priv->agent.recv_handler(&mad_agent_priv->agent,
						   mad_recv_wc);
		deref_mad_agent(mad_agent_priv);
	}
}