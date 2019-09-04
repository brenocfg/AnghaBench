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
struct waitq_set {scalar_t__ wqset_prepost_id; } ;
struct waitq {scalar_t__ waitq_prepost_id; } ;
struct _is_posted_ctx {int did_prepost; struct waitq* posting_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  wq_is_preposted_on_set_cb ; 
 int wq_prepost_foreach_locked (struct waitq_set*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wq_is_preposted_on_set(struct waitq *waitq, struct waitq_set *wqset)
{
	int ret;
	struct _is_posted_ctx pctx;

	/*
	 * If the set's only prepost matches the waitq's prepost ID,
	 * then it obviously already preposted to the set.
	 */
	if (waitq->waitq_prepost_id != 0 &&
	    wqset->wqset_prepost_id == waitq->waitq_prepost_id)
		return 1;

	/* use full prepost iteration: always trim the list */
	pctx.posting_wq = waitq;
	pctx.did_prepost = 0;
	ret = wq_prepost_foreach_locked(wqset, (void *)&pctx,
					wq_is_preposted_on_set_cb);
	return pctx.did_prepost;
}