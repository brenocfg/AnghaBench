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
struct fc_exch {int state; int esb_stat; int /*<<< orphan*/  ex_refcnt; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/ * resp; } ;

/* Variables and functions */
 int ESB_ST_COMPLETE ; 
 int ESB_ST_REC_QUAL ; 
 int FC_EX_DONE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ cancel_delayed_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fc_exch_done_locked(struct fc_exch *ep)
{
	int rc = 1;

	/*
	 * We must check for completion in case there are two threads
	 * tyring to complete this. But the rrq code will reuse the
	 * ep, and in that case we only clear the resp and set it as
	 * complete, so it can be reused by the timer to send the rrq.
	 */
	ep->resp = NULL;
	if (ep->state & FC_EX_DONE)
		return rc;
	ep->esb_stat |= ESB_ST_COMPLETE;

	if (!(ep->esb_stat & ESB_ST_REC_QUAL)) {
		ep->state |= FC_EX_DONE;
		if (cancel_delayed_work(&ep->timeout_work))
			atomic_dec(&ep->ex_refcnt); /* drop hold for timer */
		rc = 0;
	}
	return rc;
}