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
struct io_context {int /*<<< orphan*/  lock; int /*<<< orphan*/  radix_root; } ;
struct cfq_io_context {int /*<<< orphan*/  cic_list; int /*<<< orphan*/  dead_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cfq_cic_free (struct cfq_io_context*) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cic_free_func(struct io_context *ioc, struct cfq_io_context *cic)
{
	unsigned long flags;

	BUG_ON(!cic->dead_key);

	spin_lock_irqsave(&ioc->lock, flags);
	radix_tree_delete(&ioc->radix_root, cic->dead_key);
	hlist_del_rcu(&cic->cic_list);
	spin_unlock_irqrestore(&ioc->lock, flags);

	cfq_cic_free(cic);
}