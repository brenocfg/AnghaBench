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
struct wq_it_ctx {int (* it ) (int /*<<< orphan*/ ,struct waitq*,struct waitq_set*) ;scalar_t__ input; int /*<<< orphan*/  ctx; } ;
struct waitq {int dummy; } ;
struct waitq_set {struct waitq wqset_q; } ;
struct TYPE_2__ {struct waitq_set* wql_set; } ;
struct waitq_link {TYPE_1__ wql_wqs; } ;

/* Variables and functions */
 scalar_t__ WQL_WQS ; 
 int /*<<< orphan*/  assert (int) ; 
 int stub1 (int /*<<< orphan*/ ,struct waitq*,struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_set_lock (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_set_unlock (struct waitq_set*) ; 
 scalar_t__ wql_type (struct waitq_link*) ; 

__attribute__((used)) static int waitq_iterate_sets_cb(struct waitq *waitq, void *ctx,
				 struct waitq_link *link)
{
	struct wq_it_ctx *wctx = (struct wq_it_ctx *)(ctx);
	struct waitq_set *wqset;
	int ret;

	(void)waitq;
	assert(!waitq_irq_safe(waitq));
	assert(wql_type(link) == WQL_WQS);

	/*
	 * the waitq is locked, so we can just take the set lock
	 * and call the iterator function
	 */
	wqset = link->wql_wqs.wql_set;
	assert(wqset != NULL);
	assert(!waitq_irq_safe(&wqset->wqset_q));
	waitq_set_lock(wqset);

	ret = wctx->it(wctx->ctx, (struct waitq *)wctx->input, wqset);

	waitq_set_unlock(wqset);
	return ret;
}