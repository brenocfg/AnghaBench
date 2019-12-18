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
struct io_context {int /*<<< orphan*/  lock; int /*<<< orphan*/  ioc_data; } ;
struct cfq_io_context {unsigned long dead_key; int /*<<< orphan*/ ** cfqq; int /*<<< orphan*/ * key; int /*<<< orphan*/  queue_list; struct io_context* ioc; } ;
struct cfq_data {int dummy; } ;

/* Variables and functions */
 size_t BLK_RW_ASYNC ; 
 size_t BLK_RW_SYNC ; 
 int /*<<< orphan*/  cfq_exit_cfqq (struct cfq_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cfq_io_context* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __cfq_exit_single_io_context(struct cfq_data *cfqd,
					 struct cfq_io_context *cic)
{
	struct io_context *ioc = cic->ioc;

	list_del_init(&cic->queue_list);

	/*
	 * Make sure key == NULL is seen for dead queues
	 */
	smp_wmb();
	cic->dead_key = (unsigned long) cic->key;
	cic->key = NULL;

	if (rcu_dereference(ioc->ioc_data) == cic) {
		spin_lock(&ioc->lock);
		rcu_assign_pointer(ioc->ioc_data, NULL);
		spin_unlock(&ioc->lock);
	}

	if (cic->cfqq[BLK_RW_ASYNC]) {
		cfq_exit_cfqq(cfqd, cic->cfqq[BLK_RW_ASYNC]);
		cic->cfqq[BLK_RW_ASYNC] = NULL;
	}

	if (cic->cfqq[BLK_RW_SYNC]) {
		cfq_exit_cfqq(cfqd, cic->cfqq[BLK_RW_SYNC]);
		cic->cfqq[BLK_RW_SYNC] = NULL;
	}
}