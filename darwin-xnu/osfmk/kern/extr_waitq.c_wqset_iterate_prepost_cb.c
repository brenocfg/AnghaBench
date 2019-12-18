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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct wq_prepost {TYPE_1__ wqp_prepostid; } ;
struct wq_it_ctx {int (* it ) (int /*<<< orphan*/ ,struct waitq*,struct waitq_set*) ;int /*<<< orphan*/  ctx; } ;
struct waitq_set {int dummy; } ;
struct waitq {int dummy; } ;

/* Variables and functions */
 int WQ_ITERATE_BREAK ; 
 int WQ_ITERATE_BREAK_KEEP_LOCKED ; 
 int WQ_ITERATE_DROPPED ; 
 int WQ_ITERATE_RESTART ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  delay (int) ; 
 int stub1 (int /*<<< orphan*/ ,struct waitq*,struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_irq_safe (struct waitq*) ; 
 scalar_t__ waitq_lock_try (struct waitq*) ; 
 int /*<<< orphan*/  waitq_set_lock (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_set_unlock (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 struct wq_prepost* wq_prepost_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wq_prepost_put (struct wq_prepost*) ; 
 int /*<<< orphan*/  wqdbg_v (char*,struct waitq_set*,struct wq_prepost*,int /*<<< orphan*/ ,struct waitq*) ; 
 int /*<<< orphan*/  wqp_is_valid (struct wq_prepost*) ; 

__attribute__((used)) static int wqset_iterate_prepost_cb(struct waitq_set *wqset, void *ctx,
				    struct wq_prepost *wqp, struct waitq *waitq)
{
	struct wq_it_ctx *wctx = (struct wq_it_ctx *)(ctx);
	uint64_t wqp_id;
	int ret;

	(void)wqp;

	/*
	 * This is a bit tricky. The 'wqset' is locked, but the 'waitq' is not.
	 * Taking the 'waitq' lock is a lock order violation, so we need to be
	 * careful. We also must realize that we may have taken a reference to
	 * the 'wqp' just as the associated waitq was being torn down (or
	 * clearing all its preposts) - see waitq_clear_prepost_locked(). If
	 * the 'wqp' is valid and we can get the waitq lock, then we are good
	 * to go. If not, we need to back off, check that the 'wqp' hasn't
	 * been invalidated, and try to re-take the locks.
	 */
	assert(!waitq_irq_safe(waitq));

	if (waitq_lock_try(waitq))
		goto call_iterator;

	if (!wqp_is_valid(wqp))
		return WQ_ITERATE_RESTART;

	/* We are passed a prepost object with a reference on it. If neither
	 * the waitq set nor the waitq require interrupts disabled, then we
	 * may block on the delay(1) call below. We can't hold a prepost
	 * object reference while blocking, so we have to give that up as well
	 * and re-acquire it when we come back.
	 */
	wqp_id = wqp->wqp_prepostid.id;
	wq_prepost_put(wqp);
	waitq_set_unlock(wqset);
	wqdbg_v("dropped set:%p lock waiting for wqp:%p (0x%llx -> wq:%p)",
		wqset, wqp, wqp->wqp_prepostid.id, waitq);
	delay(1);
	waitq_set_lock(wqset);
	wqp = wq_prepost_get(wqp_id);
	if (!wqp)
		/* someone cleared preposts while we slept! */
		return WQ_ITERATE_DROPPED;

	/*
	 * TODO:
	 * This differs slightly from the logic in ipc_mqueue.c:
	 * ipc_mqueue_receive_on_thread(). There, if the waitq lock
	 * can't be obtained, the prepost link is placed on the back of
	 * the chain, and the iteration starts from the beginning. Here,
	 * we just restart from the beginning.
	 */
	return WQ_ITERATE_RESTART;

call_iterator:
	if (!wqp_is_valid(wqp)) {
		ret = WQ_ITERATE_RESTART;
		goto out_unlock;
	}

	/* call the external callback */
	ret = wctx->it(wctx->ctx, waitq, wqset);

	if (ret == WQ_ITERATE_BREAK_KEEP_LOCKED) {
		ret = WQ_ITERATE_BREAK;
		goto out;
	}

out_unlock:
	waitq_unlock(waitq);
out:
	return ret;
}