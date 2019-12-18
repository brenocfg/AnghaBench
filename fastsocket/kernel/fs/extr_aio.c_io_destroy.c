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
struct mm_struct {int /*<<< orphan*/  ioctx_lock; } ;
struct kioctx {int dead; int /*<<< orphan*/  wait; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  aio_cancel_all (struct kioctx*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dprintk (char*,struct kioctx*) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  put_ioctx (struct kioctx*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_all_aios (struct kioctx*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void io_destroy(struct kioctx *ioctx)
{
	struct mm_struct *mm = current->mm;
	int was_dead;

	/* delete the entry from the list is someone else hasn't already */
	spin_lock(&mm->ioctx_lock);
	was_dead = ioctx->dead;
	ioctx->dead = 1;
	hlist_del_rcu(&ioctx->list);
	spin_unlock(&mm->ioctx_lock);

	dprintk("aio_release(%p)\n", ioctx);
	if (likely(!was_dead))
		put_ioctx(ioctx);	/* twice for the list */

	aio_cancel_all(ioctx);
	wait_for_all_aios(ioctx);

	/*
	 * Wake up any waiters.  The setting of ctx->dead must be seen
	 * by other CPUs at this point.  Right now, we rely on the
	 * locking done by the above calls to ensure this consistency.
	 */
	wake_up(&ioctx->wait);
	put_ioctx(ioctx);	/* once for the lookup */
}