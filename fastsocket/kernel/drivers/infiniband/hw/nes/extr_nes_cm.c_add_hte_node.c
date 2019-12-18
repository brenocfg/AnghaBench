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
struct nes_cm_node {int /*<<< orphan*/  list; } ;
struct list_head {int dummy; } ;
struct nes_cm_core {int /*<<< orphan*/  ht_lock; int /*<<< orphan*/  ht_node_cnt; struct list_head connected_nodes; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NES_DBG_CM ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,struct nes_cm_node*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int add_hte_node(struct nes_cm_core *cm_core, struct nes_cm_node *cm_node)
{
	unsigned long flags;
	struct list_head *hte;

	if (!cm_node || !cm_core)
		return -EINVAL;

	nes_debug(NES_DBG_CM, "Adding Node %p to Active Connection HT\n",
		  cm_node);

	spin_lock_irqsave(&cm_core->ht_lock, flags);

	/* get a handle on the hash table element (list head for this slot) */
	hte = &cm_core->connected_nodes;
	list_add_tail(&cm_node->list, hte);
	atomic_inc(&cm_core->ht_node_cnt);

	spin_unlock_irqrestore(&cm_core->ht_lock, flags);

	return 0;
}