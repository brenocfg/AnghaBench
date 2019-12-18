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
struct Qdisc_ops {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* destroy ) (struct Qdisc*) ;int /*<<< orphan*/  (* reset ) (struct Qdisc*) ;} ;
struct Qdisc {int flags; int padded; int /*<<< orphan*/  gso_skb; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; int /*<<< orphan*/  stab; int /*<<< orphan*/  refcnt; struct Qdisc_ops* ops; } ;

/* Variables and functions */
 int TCQ_F_BUILTIN ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_kill_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_list_del (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_put_stab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct Qdisc*) ; 
 int /*<<< orphan*/  stub2 (struct Qdisc*) ; 

void qdisc_destroy(struct Qdisc *qdisc)
{
	const struct Qdisc_ops  *ops = qdisc->ops;

	if (qdisc->flags & TCQ_F_BUILTIN ||
	    !atomic_dec_and_test(&qdisc->refcnt))
		return;

#ifdef CONFIG_NET_SCHED
	qdisc_list_del(qdisc);

	qdisc_put_stab(qdisc->stab);
#endif
	gen_kill_estimator(&qdisc->bstats, &qdisc->rate_est);
	if (ops->reset)
		ops->reset(qdisc);
	if (ops->destroy)
		ops->destroy(qdisc);

	module_put(ops->owner);
	dev_put(qdisc_dev(qdisc));

	kfree_skb(qdisc->gso_skb);
	kfree((char *) qdisc - qdisc->padded);
}