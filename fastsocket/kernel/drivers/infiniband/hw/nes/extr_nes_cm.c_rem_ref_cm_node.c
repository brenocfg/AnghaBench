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
struct nes_qp {int /*<<< orphan*/  ibqp; int /*<<< orphan*/ * cm_node; } ;
struct nes_cm_node {struct nes_qp* nesqp; TYPE_4__* nesvnic; int /*<<< orphan*/  loc_port; scalar_t__ apbvt_set; TYPE_5__* listener; scalar_t__ recv_entry; int /*<<< orphan*/  send_entry; scalar_t__ accept_pend; int /*<<< orphan*/  accelerated; TYPE_1__* cm_core; int /*<<< orphan*/  list; int /*<<< orphan*/  ref_count; } ;
struct nes_cm_core {int /*<<< orphan*/  node_cnt; int /*<<< orphan*/  ht_node_cnt; } ;
struct TYPE_10__ {int /*<<< orphan*/  pend_accepts_cnt; } ;
struct TYPE_9__ {TYPE_3__* nesdev; } ;
struct TYPE_8__ {TYPE_2__* pcidev; } ;
struct TYPE_7__ {int /*<<< orphan*/  devfn; } ;
struct TYPE_6__ {int /*<<< orphan*/  ht_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NES_MANAGE_APBVT_DEL ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cm_nodes_destroyed ; 
 int /*<<< orphan*/  handle_recv_entry (struct nes_cm_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nes_cm_node*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mini_cm_dec_refcnt_listen (struct nes_cm_core*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_manage_apbvt (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_rem_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rem_ref_cm_node(struct nes_cm_core *cm_core,
			   struct nes_cm_node *cm_node)
{
	unsigned long flags;
	struct nes_qp *nesqp;

	if (!cm_node)
		return -EINVAL;

	spin_lock_irqsave(&cm_node->cm_core->ht_lock, flags);
	if (atomic_dec_return(&cm_node->ref_count)) {
		spin_unlock_irqrestore(&cm_node->cm_core->ht_lock, flags);
		return 0;
	}
	list_del(&cm_node->list);
	atomic_dec(&cm_core->ht_node_cnt);
	spin_unlock_irqrestore(&cm_node->cm_core->ht_lock, flags);

	/* if the node is destroyed before connection was accelerated */
	if (!cm_node->accelerated && cm_node->accept_pend) {
		BUG_ON(!cm_node->listener);
		atomic_dec(&cm_node->listener->pend_accepts_cnt);
		BUG_ON(atomic_read(&cm_node->listener->pend_accepts_cnt) < 0);
	}
	WARN_ON(cm_node->send_entry);
	if (cm_node->recv_entry)
		handle_recv_entry(cm_node, 0);
	if (cm_node->listener) {
		mini_cm_dec_refcnt_listen(cm_core, cm_node->listener, 0);
	} else {
		if (cm_node->apbvt_set && cm_node->nesvnic) {
			nes_manage_apbvt(cm_node->nesvnic, cm_node->loc_port,
					 PCI_FUNC(
						 cm_node->nesvnic->nesdev->pcidev->devfn),
					 NES_MANAGE_APBVT_DEL);
		}
	}

	atomic_dec(&cm_core->node_cnt);
	atomic_inc(&cm_nodes_destroyed);
	nesqp = cm_node->nesqp;
	if (nesqp) {
		nesqp->cm_node = NULL;
		nes_rem_ref(&nesqp->ibqp);
		cm_node->nesqp = NULL;
	}

	kfree(cm_node);
	return 0;
}