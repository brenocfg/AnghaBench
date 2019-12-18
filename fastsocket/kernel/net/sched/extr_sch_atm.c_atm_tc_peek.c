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
struct sk_buff {int dummy; } ;
struct TYPE_5__ {TYPE_3__* q; } ;
struct atm_qdisc_data {TYPE_2__ link; } ;
struct Qdisc {int dummy; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_4__ {struct sk_buff* (* peek ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,struct Qdisc*,struct atm_qdisc_data*) ; 
 struct atm_qdisc_data* qdisc_priv (struct Qdisc*) ; 
 struct sk_buff* stub1 (TYPE_3__*) ; 

__attribute__((used)) static struct sk_buff *atm_tc_peek(struct Qdisc *sch)
{
	struct atm_qdisc_data *p = qdisc_priv(sch);

	pr_debug("atm_tc_peek(sch %p,[qdisc %p])\n", sch, p);

	return p->link.q->ops->peek(p->link.q);
}