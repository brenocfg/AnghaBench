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
struct cfq_queue {scalar_t__ ref; int* allocated; struct cfq_group* orig_cfqg; struct cfq_group* cfqg; int /*<<< orphan*/  sort_list; struct cfq_data* cfqd; } ;
struct cfq_group {int dummy; } ;
struct cfq_data {struct cfq_queue* active_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t READ ; 
 size_t WRITE ; 
 int /*<<< orphan*/  __cfq_slice_expired (struct cfq_data*,struct cfq_queue*,int /*<<< orphan*/ ) ; 
 int cfq_cfqq_on_rr (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_log_cfqq (struct cfq_data*,struct cfq_queue*,char*) ; 
 int /*<<< orphan*/  cfq_pool ; 
 int /*<<< orphan*/  cfq_put_cfqg (struct cfq_group*) ; 
 int /*<<< orphan*/  cfq_schedule_dispatch (struct cfq_data*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct cfq_queue*) ; 
 int rb_first (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void cfq_put_queue(struct cfq_queue *cfqq)
{
	struct cfq_data *cfqd = cfqq->cfqd;
	struct cfq_group *cfqg, *orig_cfqg;

	BUG_ON(cfqq->ref <= 0);

	cfqq->ref--;
	if (cfqq->ref)
		return;

	cfq_log_cfqq(cfqd, cfqq, "put_queue");
	BUG_ON(rb_first(&cfqq->sort_list));
	BUG_ON(cfqq->allocated[READ] + cfqq->allocated[WRITE]);
	cfqg = cfqq->cfqg;
	orig_cfqg = cfqq->orig_cfqg;

	if (unlikely(cfqd->active_queue == cfqq)) {
		__cfq_slice_expired(cfqd, cfqq, 0);
		cfq_schedule_dispatch(cfqd);
	}

	BUG_ON(cfq_cfqq_on_rr(cfqq));
	kmem_cache_free(cfq_pool, cfqq);
	cfq_put_cfqg(cfqg);
	if (orig_cfqg)
		cfq_put_cfqg(orig_cfqg);
}