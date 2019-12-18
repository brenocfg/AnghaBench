#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {scalar_t__ wqp_wq_id; scalar_t__ wqp_next_id; } ;
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_5__ {struct waitq* wqp_wq_ptr; } ;
struct wq_prepost {TYPE_3__ wqp_post; TYPE_2__ wqp_prepostid; TYPE_1__ wqp_wq; } ;
struct waitq {scalar_t__ waitq_prepost_id; } ;
struct waitq_set {scalar_t__ wqset_prepost_id; int /*<<< orphan*/  wqset_id; struct waitq wqset_q; } ;
struct TYPE_8__ {int npreposts; } ;

/* Variables and functions */
 scalar_t__ VM_KERNEL_UNSLIDE_OR_PERM (struct waitq*) ; 
 scalar_t__ WQP_POST ; 
 scalar_t__ WQP_WQ ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__ g_prepost_table ; 
 scalar_t__ waitq_held (struct waitq*) ; 
 int waitqs_is_linked (struct waitq_set*) ; 
 struct wq_prepost* wq_get_prepost_obj (scalar_t__*,scalar_t__) ; 
 scalar_t__ wq_is_preposted_on_set (struct waitq*,struct waitq_set*) ; 
 struct wq_prepost* wq_prepost_get (scalar_t__) ; 
 struct wq_prepost* wq_prepost_get_rnext (struct wq_prepost*) ; 
 int /*<<< orphan*/  wq_prepost_put (struct wq_prepost*) ; 
 int /*<<< orphan*/  wq_prepost_reset_rnext (struct wq_prepost*) ; 
 int /*<<< orphan*/  wq_prepost_rlink (struct wq_prepost*,struct wq_prepost*) ; 
 int /*<<< orphan*/  wqdbg_v (char*,void*,scalar_t__,...) ; 
 int /*<<< orphan*/  wqp_set_valid (struct wq_prepost*) ; 
 scalar_t__ wqp_type (struct wq_prepost*) ; 

__attribute__((used)) static void wq_prepost_do_post_locked(struct waitq_set *wqset,
				      struct waitq *waitq,
				      uint64_t *reserved)
{
	struct wq_prepost *wqp_post, *wqp_head, *wqp_tail;

	assert(waitq_held(waitq) && waitq_held(&wqset->wqset_q));

	/*
	 * nothing to do if it's already preposted:
	 * note that this also culls any invalid prepost objects
	 */
	if (wq_is_preposted_on_set(waitq, wqset))
		return;

	assert(waitqs_is_linked(wqset));

	/*
	 * This function is called because an event is being posted to 'waitq'.
	 * We need a prepost object associated with this queue. Allocate one
	 * now if the waitq isn't already associated with one.
	 */
	if (waitq->waitq_prepost_id == 0) {
		struct wq_prepost *wqp;
		wqp = wq_get_prepost_obj(reserved, WQP_WQ);
		wqp->wqp_wq.wqp_wq_ptr = waitq;
		wqp_set_valid(wqp);
		waitq->waitq_prepost_id = wqp->wqp_prepostid.id;
		wq_prepost_put(wqp);
	}

#if CONFIG_LTABLE_STATS
	g_prepost_table.npreposts += 1;
#endif

	wqdbg_v("preposting waitq %p (0x%llx) to set 0x%llx",
		(void *)VM_KERNEL_UNSLIDE_OR_PERM(waitq),
		waitq->waitq_prepost_id, wqset->wqset_id);

	if (wqset->wqset_prepost_id == 0) {
		/* the set has no previous preposts */
		wqset->wqset_prepost_id = waitq->waitq_prepost_id;
		return;
	}

	wqp_head = wq_prepost_get(wqset->wqset_prepost_id);
	if (!wqp_head) {
		/* the previous prepost has become invalid */
		wqset->wqset_prepost_id = waitq->waitq_prepost_id;
		return;
	}

	assert(wqp_head->wqp_prepostid.id == wqset->wqset_prepost_id);

	/*
	 * If we get here, we're going to need at least one new wq_prepost
	 * object. If the previous wqset_prepost_id points to a WQP_WQ, we
	 * actually need to allocate 2 wq_prepost objects because the WQP_WQ
	 * is tied to the waitq and shared across all sets.
	 */
	wqp_post = wq_get_prepost_obj(reserved, WQP_POST);

	wqp_post->wqp_post.wqp_wq_id = waitq->waitq_prepost_id;
	wqdbg_v("POST 0x%llx :: WQ 0x%llx", wqp_post->wqp_prepostid.id,
		waitq->waitq_prepost_id);

	if (wqp_type(wqp_head) == WQP_WQ) {
		/*
		 * We must replace the wqset_prepost_id with a pointer
		 * to two new WQP_POST objects
		 */
		uint64_t wqp_id = wqp_head->wqp_prepostid.id;
		wqdbg_v("set 0x%llx previous had 1 WQ prepost (0x%llx): "
			"replacing with two POST preposts",
			wqset->wqset_id, wqp_id);

		/* drop the old reference */
		wq_prepost_put(wqp_head);

		/* grab another new object (the 2nd of two) */
		wqp_head = wq_get_prepost_obj(reserved, WQP_POST);

		/* point this one to the original WQP_WQ object */
		wqp_head->wqp_post.wqp_wq_id = wqp_id;
		wqdbg_v("POST 0x%llx :: WQ 0x%llx",
			wqp_head->wqp_prepostid.id, wqp_id);
	
		/* link it to the new wqp_post object allocated earlier */
		wqp_head->wqp_post.wqp_next_id = wqp_post->wqp_prepostid.id;
		/* make the list a double-linked and circular */
		wq_prepost_rlink(wqp_head, wqp_post);

		/*
		 * Finish setting up the new prepost: point it back to the
		 * POST object we allocated to replace the original wqset
		 * WQ prepost object
		 */
		wqp_post->wqp_post.wqp_next_id = wqp_head->wqp_prepostid.id;
		wq_prepost_rlink(wqp_post, wqp_head);

		/* mark objects valid, and reset the wqset prepost list head */
		wqp_set_valid(wqp_head);
		wqp_set_valid(wqp_post);
		wqset->wqset_prepost_id = wqp_head->wqp_prepostid.id;

		/* release both references */
		wq_prepost_put(wqp_head);
		wq_prepost_put(wqp_post);

		wqdbg_v("set 0x%llx: 0x%llx/0x%llx -> 0x%llx/0x%llx -> 0x%llx",
			wqset->wqset_id, wqset->wqset_prepost_id,
			wqp_head->wqp_prepostid.id, wqp_head->wqp_post.wqp_next_id,
			wqp_post->wqp_prepostid.id,
			wqp_post->wqp_post.wqp_next_id);
		return;
	}

	assert(wqp_type(wqp_head) == WQP_POST);

	/*
	 * Add the new prepost to the end of the prepost list
	 */
	wqp_tail = wq_prepost_get_rnext(wqp_head);
	assert(wqp_tail != NULL);
	assert(wqp_tail->wqp_post.wqp_next_id == wqset->wqset_prepost_id);

	/*
	 * link the head to the new tail
	 * NOTE: this needs to happen first in case wqp_tail == wqp_head
	 */
	wq_prepost_reset_rnext(wqp_head);
	wq_prepost_rlink(wqp_head, wqp_post);

	/* point the new object to the list head, and list tail */
	wqp_post->wqp_post.wqp_next_id = wqp_head->wqp_prepostid.id;
	wq_prepost_rlink(wqp_post, wqp_tail);

	/* point the last item in the waitq set's list to the new object */
	wqp_tail->wqp_post.wqp_next_id = wqp_post->wqp_prepostid.id;

	wqp_set_valid(wqp_post);

	wq_prepost_put(wqp_head);
	wq_prepost_put(wqp_tail);
	wq_prepost_put(wqp_post);

	wqdbg_v("set 0x%llx (wqp:0x%llx) last_prepost:0x%llx, "
		"new_prepost:0x%llx->0x%llx", wqset->wqset_id,
		wqset->wqset_prepost_id, wqp_head->wqp_prepostid.id,
		wqp_post->wqp_prepostid.id, wqp_post->wqp_post.wqp_next_id);

	return;
}