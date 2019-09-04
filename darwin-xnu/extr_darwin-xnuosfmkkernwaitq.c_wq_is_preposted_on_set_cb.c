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
struct wq_prepost {int dummy; } ;
struct waitq_set {int dummy; } ;
struct waitq {int dummy; } ;
struct _is_posted_ctx {int did_prepost; struct waitq* posting_wq; } ;

/* Variables and functions */
 int WQ_ITERATE_CONTINUE ; 

__attribute__((used)) static int wq_is_preposted_on_set_cb(struct waitq_set *wqset, void *ctx,
				     struct wq_prepost *wqp, struct waitq *waitq)
{
	struct _is_posted_ctx *pctx = (struct _is_posted_ctx *)ctx;

	(void)wqset;
	(void)wqp;

	/*
	 * Don't early-out, run through the _entire_ list:
	 * This ensures that we retain a minimum number of invalid elements.
	 */
	if (pctx->posting_wq == waitq)
		pctx->did_prepost = 1;

	return WQ_ITERATE_CONTINUE;
}