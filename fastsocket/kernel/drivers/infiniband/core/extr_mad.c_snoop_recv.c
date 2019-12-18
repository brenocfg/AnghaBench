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
struct TYPE_2__ {int /*<<< orphan*/  (* recv_handler ) (TYPE_1__*,struct ib_mad_recv_wc*) ;} ;
struct ib_mad_snoop_private {int mad_snoop_flags; TYPE_1__ agent; int /*<<< orphan*/  refcount; } ;
struct ib_mad_recv_wc {int dummy; } ;
struct ib_mad_qp_info {int snoop_table_size; int /*<<< orphan*/  snoop_lock; struct ib_mad_snoop_private** snoop_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deref_snoop_agent (struct ib_mad_snoop_private*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct ib_mad_recv_wc*) ; 

__attribute__((used)) static void snoop_recv(struct ib_mad_qp_info *qp_info,
		       struct ib_mad_recv_wc *mad_recv_wc,
		       int mad_snoop_flags)
{
	struct ib_mad_snoop_private *mad_snoop_priv;
	unsigned long flags;
	int i;

	spin_lock_irqsave(&qp_info->snoop_lock, flags);
	for (i = 0; i < qp_info->snoop_table_size; i++) {
		mad_snoop_priv = qp_info->snoop_table[i];
		if (!mad_snoop_priv ||
		    !(mad_snoop_priv->mad_snoop_flags & mad_snoop_flags))
			continue;

		atomic_inc(&mad_snoop_priv->refcount);
		spin_unlock_irqrestore(&qp_info->snoop_lock, flags);
		mad_snoop_priv->agent.recv_handler(&mad_snoop_priv->agent,
						   mad_recv_wc);
		deref_snoop_agent(mad_snoop_priv);
		spin_lock_irqsave(&qp_info->snoop_lock, flags);
	}
	spin_unlock_irqrestore(&qp_info->snoop_lock, flags);
}