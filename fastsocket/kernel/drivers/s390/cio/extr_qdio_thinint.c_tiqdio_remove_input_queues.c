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
struct TYPE_2__ {int /*<<< orphan*/  next; int /*<<< orphan*/  prev; } ;
struct qdio_q {TYPE_1__ entry; } ;
struct qdio_irq {int nr_input_qs; struct qdio_q** input_qs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  list_del_rcu (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  tiq_list_lock ; 

void tiqdio_remove_input_queues(struct qdio_irq *irq_ptr)
{
	struct qdio_q *q;

	BUG_ON(irq_ptr->nr_input_qs < 1);
	q = irq_ptr->input_qs[0];
	/* if establish triggered an error */
	if (!q || !q->entry.prev || !q->entry.next)
		return;

	mutex_lock(&tiq_list_lock);
	list_del_rcu(&q->entry);
	mutex_unlock(&tiq_list_lock);
	synchronize_rcu();
}