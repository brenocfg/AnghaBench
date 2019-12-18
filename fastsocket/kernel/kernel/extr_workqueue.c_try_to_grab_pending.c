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
struct work_struct {int /*<<< orphan*/  entry; } ;
struct cpu_workqueue_struct {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WORK_STRUCT_PENDING ; 
 struct cpu_workqueue_struct* get_wq_data (struct work_struct*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_data_bits (struct work_struct*) ; 

__attribute__((used)) static int try_to_grab_pending(struct work_struct *work)
{
	struct cpu_workqueue_struct *cwq;
	int ret = -1;

	if (!test_and_set_bit(WORK_STRUCT_PENDING, work_data_bits(work)))
		return 0;

	/*
	 * The queueing is in progress, or it is already queued. Try to
	 * steal it from ->worklist without clearing WORK_STRUCT_PENDING.
	 */

	cwq = get_wq_data(work);
	if (!cwq)
		return ret;

	spin_lock_irq(&cwq->lock);
	if (!list_empty(&work->entry)) {
		/*
		 * This work is queued, but perhaps we locked the wrong cwq.
		 * In that case we must see the new value after rmb(), see
		 * insert_work()->wmb().
		 */
		smp_rmb();
		if (cwq == get_wq_data(work)) {
			list_del_init(&work->entry);
			ret = 1;
		}
	}
	spin_unlock_irq(&cwq->lock);

	return ret;
}