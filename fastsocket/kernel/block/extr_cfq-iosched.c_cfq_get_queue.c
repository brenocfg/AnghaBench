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
struct io_context {int dummy; } ;
struct cfq_queue {int /*<<< orphan*/  ref; } ;
struct cfq_data {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct cfq_queue** cfq_async_queue_prio (struct cfq_data*,int const,int const) ; 
 struct cfq_queue* cfq_find_alloc_queue (struct cfq_data*,int,struct io_context*,int /*<<< orphan*/ ) ; 
 int task_ioprio (struct io_context*) ; 
 int task_ioprio_class (struct io_context*) ; 

__attribute__((used)) static struct cfq_queue *
cfq_get_queue(struct cfq_data *cfqd, bool is_sync, struct io_context *ioc,
	      gfp_t gfp_mask)
{
	const int ioprio = task_ioprio(ioc);
	const int ioprio_class = task_ioprio_class(ioc);
	struct cfq_queue **async_cfqq = NULL;
	struct cfq_queue *cfqq = NULL;

	if (!is_sync) {
		async_cfqq = cfq_async_queue_prio(cfqd, ioprio_class, ioprio);
		cfqq = *async_cfqq;
	}

	if (!cfqq)
		cfqq = cfq_find_alloc_queue(cfqd, is_sync, ioc, gfp_mask);

	/*
	 * pin the queue now that it's allocated, scheduler exit will prune it
	 */
	if (!is_sync && !(*async_cfqq)) {
		cfqq->ref++;
		*async_cfqq = cfqq;
	}

	cfqq->ref++;
	return cfqq;
}