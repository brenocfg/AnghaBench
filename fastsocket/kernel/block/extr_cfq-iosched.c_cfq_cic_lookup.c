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
struct io_context {int /*<<< orphan*/  lock; int /*<<< orphan*/  ioc_data; int /*<<< orphan*/  radix_root; } ;
struct cfq_io_context {struct cfq_data* key; } ;
struct cfq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfq_drop_dead_cic (struct cfq_data*,struct io_context*,struct cfq_io_context*) ; 
 struct cfq_io_context* radix_tree_lookup (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct cfq_io_context*) ; 
 struct cfq_io_context* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct cfq_io_context *
cfq_cic_lookup(struct cfq_data *cfqd, struct io_context *ioc)
{
	struct cfq_io_context *cic;
	unsigned long flags;
	void *k;

	if (unlikely(!ioc))
		return NULL;

	rcu_read_lock();

	/*
	 * we maintain a last-hit cache, to avoid browsing over the tree
	 */
	cic = rcu_dereference(ioc->ioc_data);
	if (cic && cic->key == cfqd) {
		rcu_read_unlock();
		return cic;
	}

	do {
		cic = radix_tree_lookup(&ioc->radix_root, (unsigned long) cfqd);
		rcu_read_unlock();
		if (!cic)
			break;
		/* ->key must be copied to avoid race with cfq_exit_queue() */
		k = cic->key;
		if (unlikely(!k)) {
			cfq_drop_dead_cic(cfqd, ioc, cic);
			rcu_read_lock();
			continue;
		}

		spin_lock_irqsave(&ioc->lock, flags);
		rcu_assign_pointer(ioc->ioc_data, cic);
		spin_unlock_irqrestore(&ioc->lock, flags);
		break;
	} while (1);

	return cic;
}