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
struct fc_seq {int dummy; } ;
struct fc_exch {void (* resp ) (struct fc_seq*,struct fc_frame*,void*) ;int esb_stat; int /*<<< orphan*/  ex_lock; struct fc_seq seq; void* arg; int /*<<< orphan*/  ex_refcnt; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 struct fc_frame* ERR_PTR (int /*<<< orphan*/ ) ; 
 int ESB_ST_REC_QUAL ; 
 int /*<<< orphan*/  FC_EX_CLOSED ; 
 int /*<<< orphan*/  FC_EX_RST_CLEANUP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_exch_abort_locked (struct fc_exch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_exch_delete (struct fc_exch*) ; 
 int fc_exch_done_locked (struct fc_exch*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_exch_reset(struct fc_exch *ep)
{
	struct fc_seq *sp;
	void (*resp)(struct fc_seq *, struct fc_frame *, void *);
	void *arg;
	int rc = 1;

	spin_lock_bh(&ep->ex_lock);
	fc_exch_abort_locked(ep, 0);
	ep->state |= FC_EX_RST_CLEANUP;
	if (cancel_delayed_work(&ep->timeout_work))
		atomic_dec(&ep->ex_refcnt);	/* drop hold for timer */
	resp = ep->resp;
	ep->resp = NULL;
	if (ep->esb_stat & ESB_ST_REC_QUAL)
		atomic_dec(&ep->ex_refcnt);	/* drop hold for rec_qual */
	ep->esb_stat &= ~ESB_ST_REC_QUAL;
	arg = ep->arg;
	sp = &ep->seq;
	rc = fc_exch_done_locked(ep);
	spin_unlock_bh(&ep->ex_lock);
	if (!rc)
		fc_exch_delete(ep);

	if (resp)
		resp(sp, ERR_PTR(-FC_EX_CLOSED), arg);
}