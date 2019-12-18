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
struct bdi_writeback {int /*<<< orphan*/ * task; int /*<<< orphan*/  list; struct backing_dev_info* bdi; } ;
struct backing_dev_info {int /*<<< orphan*/  work_list; int /*<<< orphan*/  wb_lock; int /*<<< orphan*/  state; int /*<<< orphan*/  bdi_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_pending ; 
 int /*<<< orphan*/  bdi_list ; 
 int /*<<< orphan*/  bdi_lock ; 
 int /*<<< orphan*/  bdi_task_init (struct backing_dev_info*,struct bdi_writeback*) ; 
 int bdi_writeback_task (struct bdi_writeback*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_clear_bit () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wb_do_writeback (struct bdi_writeback*,int) ; 

__attribute__((used)) static int bdi_start_fn(void *ptr)
{
	struct bdi_writeback *wb = ptr;
	struct backing_dev_info *bdi = wb->bdi;
	int ret;

	/*
	 * Add us to the active bdi_list
	 */
	spin_lock_bh(&bdi_lock);
	list_add_rcu(&bdi->bdi_list, &bdi_list);
	spin_unlock_bh(&bdi_lock);

	bdi_task_init(bdi, wb);

	/*
	 * Clear pending bit and wakeup anybody waiting to tear us down
	 */
	clear_bit(BDI_pending, &bdi->state);
	smp_mb__after_clear_bit();
	wake_up_bit(&bdi->state, BDI_pending);

	ret = bdi_writeback_task(wb);

	/*
	 * Remove us from the list
	 */
	spin_lock(&bdi->wb_lock);
	list_del_rcu(&wb->list);
	spin_unlock(&bdi->wb_lock);

	/*
	 * Flush any work that raced with us exiting. No new work
	 * will be added, since this bdi isn't discoverable anymore.
	 */
	if (!list_empty(&bdi->work_list))
		wb_do_writeback(wb, 1);

	wb->task = NULL;
	return ret;
}