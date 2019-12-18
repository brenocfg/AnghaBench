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
struct Qdisc_ops {int /*<<< orphan*/  (* reset ) (struct Qdisc*) ;} ;
struct TYPE_2__ {scalar_t__ qlen; } ;
struct Qdisc {TYPE_1__ q; int /*<<< orphan*/ * gso_skb; struct Qdisc_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct Qdisc*) ; 

void qdisc_reset(struct Qdisc *qdisc)
{
	const struct Qdisc_ops *ops = qdisc->ops;

	if (ops->reset)
		ops->reset(qdisc);

	if (qdisc->gso_skb) {
		kfree_skb(qdisc->gso_skb);
		qdisc->gso_skb = NULL;
		qdisc->q.qlen = 0;
	}
}