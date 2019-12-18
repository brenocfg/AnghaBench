#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ sync; } ;
struct qdio_irq {int nr_input_qs; int /*<<< orphan*/  dsci; TYPE_2__** input_qs; TYPE_1__ siga_flag; } ;
struct TYPE_4__ {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int css_qdio_omit_svs ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tiq_list ; 
 int /*<<< orphan*/  tiq_list_lock ; 
 int /*<<< orphan*/  xchg (int /*<<< orphan*/ ,int) ; 

void tiqdio_add_input_queues(struct qdio_irq *irq_ptr)
{
	/* No TDD facility? If we must use SIGA-s we can also omit SVS. */
	if (!css_qdio_omit_svs && irq_ptr->siga_flag.sync)
		css_qdio_omit_svs = 1;

	mutex_lock(&tiq_list_lock);
	BUG_ON(irq_ptr->nr_input_qs < 1);
	list_add_rcu(&irq_ptr->input_qs[0]->entry, &tiq_list);
	mutex_unlock(&tiq_list_lock);
	xchg(irq_ptr->dsci, 1);
}