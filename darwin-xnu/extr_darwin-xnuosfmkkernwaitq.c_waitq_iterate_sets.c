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
typedef  int /*<<< orphan*/  waitq_iterator_t ;
struct wq_it_ctx {void* input; void* ctx; int /*<<< orphan*/  it; } ;
struct waitq {int /*<<< orphan*/  waitq_set_id; } ;

/* Variables and functions */
 int KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  LINK_WALK_ONE_LEVEL ; 
 int /*<<< orphan*/  WQL_WQS ; 
 int WQ_ITERATE_CONTINUE ; 
 int WQ_ITERATE_SUCCESS ; 
 int /*<<< orphan*/  waitq_iterate_sets_cb ; 
 int walk_waitq_links (int /*<<< orphan*/ ,struct waitq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

int waitq_iterate_sets(struct waitq *waitq, void *ctx, waitq_iterator_t it)
{
	int ret;
	struct wq_it_ctx wctx = {
		.input = (void *)waitq,
		.ctx = ctx,
		.it = it,
	};
	if (!it || !waitq)
		return KERN_INVALID_ARGUMENT;

	ret = walk_waitq_links(LINK_WALK_ONE_LEVEL, waitq, waitq->waitq_set_id,
			       WQL_WQS, (void *)&wctx, waitq_iterate_sets_cb);
	if (ret == WQ_ITERATE_CONTINUE)
		ret = WQ_ITERATE_SUCCESS;
	return ret;
}