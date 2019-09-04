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
struct waitq_set {int /*<<< orphan*/  wqset_q; } ;

/* Variables and functions */
 int WQ_ITERATE_INVALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitq_held (int /*<<< orphan*/ *) ; 
 int wq_prepost_foreach_locked (struct waitq_set*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wqset_iterate_prepost_cb ; 

int waitq_set_iterate_preposts(struct waitq_set *wqset,
			       void *ctx, waitq_iterator_t it)
{
	struct wq_it_ctx wctx = {
		.input = (void *)wqset,
		.ctx = ctx,
		.it = it,
	};
	if (!it || !wqset)
		return WQ_ITERATE_INVALID;

	assert(waitq_held(&wqset->wqset_q));

	return wq_prepost_foreach_locked(wqset, (void *)&wctx,
					 wqset_iterate_prepost_cb);
}