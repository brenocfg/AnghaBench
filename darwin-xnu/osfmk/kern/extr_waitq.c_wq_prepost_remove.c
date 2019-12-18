#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {scalar_t__ wqp_next_id; scalar_t__ wqp_wq_id; } ;
struct TYPE_5__ {scalar_t__ id; } ;
struct wq_prepost {TYPE_3__ wqp_post; TYPE_2__ wqp_prepostid; } ;
struct TYPE_4__ {int waitq_prepost; } ;
struct waitq_set {scalar_t__ wqset_prepost_id; TYPE_1__ wqset_q; } ;

/* Variables and functions */
 scalar_t__ WQP_POST ; 
 int /*<<< orphan*/  assert (int) ; 
 struct wq_prepost* wq_prepost_get (scalar_t__) ; 
 struct wq_prepost* wq_prepost_get_rnext (struct wq_prepost*) ; 
 int /*<<< orphan*/  wq_prepost_invalidate (struct wq_prepost*) ; 
 int /*<<< orphan*/  wq_prepost_put (struct wq_prepost*) ; 
 int /*<<< orphan*/  wq_prepost_reset_rnext (struct wq_prepost*) ; 
 int /*<<< orphan*/  wq_prepost_rlink (struct wq_prepost*,struct wq_prepost*) ; 
 scalar_t__ wqp_type (struct wq_prepost*) ; 

__attribute__((used)) static int wq_prepost_remove(struct waitq_set *wqset,
			     struct wq_prepost *wqp)
{
	int more_posts = 1;
	uint64_t next_id = wqp->wqp_post.wqp_next_id;
	uint64_t wqp_id = wqp->wqp_prepostid.id;
	struct wq_prepost *prev_wqp, *next_wqp;

	assert(wqp_type(wqp) == WQP_POST);
	assert(wqset->wqset_q.waitq_prepost == 1);

	if (next_id == wqp_id) {
		/* the list is singular and becoming empty */
		wqset->wqset_prepost_id = 0;
		more_posts = 0;
		goto out;
	}

	prev_wqp = wq_prepost_get_rnext(wqp);
	assert(prev_wqp != NULL);
	assert(prev_wqp->wqp_post.wqp_next_id == wqp_id);
	assert(prev_wqp->wqp_prepostid.id != wqp_id);
	assert(wqp_type(prev_wqp) == WQP_POST);

	if (prev_wqp->wqp_prepostid.id == next_id) {
		/*
		 * There are two items in the list, and we're removing one. We
		 * only need to keep the WQP_WQ pointer from 'prev_wqp'
		 */
		wqset->wqset_prepost_id = prev_wqp->wqp_post.wqp_wq_id;
		wq_prepost_invalidate(prev_wqp);
		wq_prepost_put(prev_wqp);
		more_posts = 0;
		goto out;
	}

	/* prev->next = next */
	prev_wqp->wqp_post.wqp_next_id = next_id;

	/* next->prev = prev */
	next_wqp = wq_prepost_get(next_id);
	assert(next_wqp != NULL);
	assert(next_wqp != wqp);
	assert(next_wqp != prev_wqp);
	assert(wqp_type(next_wqp) == WQP_POST);

	wq_prepost_reset_rnext(next_wqp);
	wq_prepost_rlink(next_wqp, prev_wqp);

	/* If we remove the head of the list, update the wqset */
	if (wqp_id == wqset->wqset_prepost_id)
		wqset->wqset_prepost_id = next_id;

	wq_prepost_put(prev_wqp);
	wq_prepost_put(next_wqp);

out:
	wq_prepost_reset_rnext(wqp);
	wq_prepost_invalidate(wqp);
	return more_posts;
}