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
struct throtl_grp {int dummy; } ;
struct throtl_data {struct throtl_grp* root_tg; struct request_queue* queue; } ;
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct blkio_cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_queue_dead (struct request_queue*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kfree (struct throtl_grp*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 struct blkio_cgroup* task_blkio_cgroup (int /*<<< orphan*/ ) ; 
 struct throtl_grp* throtl_alloc_tg (struct throtl_data*) ; 
 struct throtl_grp* throtl_find_tg (struct throtl_data*,struct blkio_cgroup*) ; 
 int /*<<< orphan*/  throtl_init_add_tg_lists (struct throtl_data*,struct throtl_grp*,struct blkio_cgroup*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct throtl_grp * throtl_get_tg(struct throtl_data *td)
{
	struct throtl_grp *tg = NULL, *__tg = NULL;
	struct blkio_cgroup *blkcg;
	struct request_queue *q = td->queue;

	/* no throttling for dead queue */
	if (unlikely(blk_queue_dead(q)))
		return NULL;

	rcu_read_lock();
	blkcg = task_blkio_cgroup(current);
	tg = throtl_find_tg(td, blkcg);
	if (tg) {
		rcu_read_unlock();
		return tg;
	}

	/*
	 * Need to allocate a group. Allocation of group also needs allocation
	 * of per cpu stats which in-turn takes a mutex() and can block. Hence
	 * we need to drop rcu lock and queue_lock before we call alloc.
	 */
	rcu_read_unlock();
	spin_unlock_irq(q->queue_lock);

	tg = throtl_alloc_tg(td);

	/* Group allocated and queue is still alive. take the lock */
	spin_lock_irq(q->queue_lock);

	/* Make sure @q is still alive */
	if (unlikely(blk_queue_dead(q))) {
		kfree(tg);
		return NULL;
	}

	/*
	 * Initialize the new group. After sleeping, read the blkcg again.
	 */
	rcu_read_lock();
	blkcg = task_blkio_cgroup(current);

	/*
	 * If some other thread already allocated the group while we were
	 * not holding queue lock, free up the group
	 */
	__tg = throtl_find_tg(td, blkcg);

	if (__tg) {
		kfree(tg);
		rcu_read_unlock();
		return __tg;
	}

	/* Group allocation failed. Account the IO to root group */
	if (!tg) {
		tg = td->root_tg;
		return tg;
	}

	throtl_init_add_tg_lists(td, tg, blkcg);
	rcu_read_unlock();
	return tg;
}