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
struct io_context {int dummy; } ;
struct cfq_queue {int dummy; } ;
struct cfq_io_context {int dummy; } ;
struct cfq_group {int dummy; } ;
struct cfq_data {struct cfq_queue oom_cfqq; TYPE_1__* queue; } ;
typedef  int gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  node; int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int __GFP_WAIT ; 
 int __GFP_ZERO ; 
 struct cfq_io_context* cfq_cic_lookup (struct cfq_data*,struct io_context*) ; 
 struct cfq_group* cfq_get_cfqg (struct cfq_data*) ; 
 int /*<<< orphan*/  cfq_init_cfqq (struct cfq_data*,struct cfq_queue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cfq_init_prio_data (struct cfq_queue*,struct io_context*) ; 
 int /*<<< orphan*/  cfq_link_cfqq_cfqg (struct cfq_queue*,struct cfq_group*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*) ; 
 int /*<<< orphan*/  cfq_pool ; 
 struct cfq_queue* cic_to_cfqq (struct cfq_io_context*,int) ; 
 TYPE_2__* current ; 
 struct cfq_queue* kmem_cache_alloc_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct cfq_queue*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cfq_queue *
cfq_find_alloc_queue(struct cfq_data *cfqd, bool is_sync,
		     struct io_context *ioc, gfp_t gfp_mask)
{
	struct cfq_queue *cfqq, *new_cfqq = NULL;
	struct cfq_io_context *cic;
	struct cfq_group *cfqg;

retry:
	cfqg = cfq_get_cfqg(cfqd);
	cic = cfq_cic_lookup(cfqd, ioc);
	/* cic always exists here */
	cfqq = cic_to_cfqq(cic, is_sync);

	/*
	 * Always try a new alloc if we fell back to the OOM cfqq
	 * originally, since it should just be a temporary situation.
	 */
	if (!cfqq || cfqq == &cfqd->oom_cfqq) {
		cfqq = NULL;
		if (new_cfqq) {
			cfqq = new_cfqq;
			new_cfqq = NULL;
		} else if (gfp_mask & __GFP_WAIT) {
			spin_unlock_irq(cfqd->queue->queue_lock);
			new_cfqq = kmem_cache_alloc_node(cfq_pool,
					gfp_mask | __GFP_ZERO,
					cfqd->queue->node);
			spin_lock_irq(cfqd->queue->queue_lock);
			if (new_cfqq)
				goto retry;
		} else {
			cfqq = kmem_cache_alloc_node(cfq_pool,
					gfp_mask | __GFP_ZERO,
					cfqd->queue->node);
		}

		if (cfqq) {
			cfq_init_cfqq(cfqd, cfqq, current->pid, is_sync);
			cfq_init_prio_data(cfqq, ioc);
			cfq_link_cfqq_cfqg(cfqq, cfqg);
			cfq_log_cfqq(cfqd, cfqq, "alloced");
		} else
			cfqq = &cfqd->oom_cfqq;
	}

	if (new_cfqq)
		kmem_cache_free(cfq_pool, new_cfqq);

	return cfqq;
}