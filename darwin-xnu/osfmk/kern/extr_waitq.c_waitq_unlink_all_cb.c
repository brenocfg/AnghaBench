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
struct wq_unlink_ctx {struct waitq_set* unlink_wqset; struct waitq* unlink_wq; } ;
struct waitq_set {int /*<<< orphan*/  wqset_prepost_id; int /*<<< orphan*/  wqset_q; } ;
struct TYPE_2__ {struct waitq_set* wql_set; } ;
struct waitq_link {TYPE_1__ wql_wqs; } ;
struct waitq {scalar_t__ waitq_prepost_id; } ;

/* Variables and functions */
 scalar_t__ WQL_LINK ; 
 scalar_t__ WQL_WQS ; 
 int WQ_ITERATE_CONTINUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  waitq_irq_safe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitq_set_is_valid (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_set_lock (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_set_maybe_preposted (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_set_unlock (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_unlink_prepost_cb ; 
 int /*<<< orphan*/  wq_prepost_iterate (int /*<<< orphan*/ ,struct wq_unlink_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wql_invalidate (struct waitq_link*) ; 
 scalar_t__ wql_is_valid (struct waitq_link*) ; 
 scalar_t__ wql_type (struct waitq_link*) ; 

__attribute__((used)) static int waitq_unlink_all_cb(struct waitq *waitq, void *ctx,
			       struct waitq_link *link)
{
	(void)waitq;
	(void)ctx;
	if (wql_type(link) == WQL_LINK && wql_is_valid(link))
		wql_invalidate(link);

	if (wql_type(link) == WQL_WQS) {
		struct waitq_set *wqset;
		struct wq_unlink_ctx ulctx;

		/*
		 * When destroying the waitq, take the time to clear out any
		 * preposts it may have made. This could potentially save time
		 * on the IPC send path which would otherwise have to iterate
		 * over lots of dead port preposts.
		 */
		if (waitq->waitq_prepost_id == 0)
			goto out;

		wqset = link->wql_wqs.wql_set;
		assert(wqset != NULL);
		assert(!waitq_irq_safe(&wqset->wqset_q));

		waitq_set_lock(wqset);

		if (!waitq_set_is_valid(wqset)) {
			/* someone raced us to teardown */
			goto out_unlock;
		}
		if (!waitq_set_maybe_preposted(wqset))
			goto out_unlock;

		ulctx.unlink_wq = waitq;
		ulctx.unlink_wqset = wqset;
		(void)wq_prepost_iterate(wqset->wqset_prepost_id, &ulctx,
					 waitq_unlink_prepost_cb);
out_unlock:
		waitq_set_unlock(wqset);
	}

out:
	return WQ_ITERATE_CONTINUE;
}