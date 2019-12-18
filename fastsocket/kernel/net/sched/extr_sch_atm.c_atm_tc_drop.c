#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct atm_qdisc_data {struct atm_flow_data* flows; } ;
struct atm_flow_data {TYPE_2__* q; struct atm_flow_data* next; } ;
struct Qdisc {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {unsigned int (* drop ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,struct Qdisc*,struct atm_qdisc_data*) ; 
 struct atm_qdisc_data* qdisc_priv (struct Qdisc*) ; 
 unsigned int stub1 (TYPE_2__*) ; 

__attribute__((used)) static unsigned int atm_tc_drop(struct Qdisc *sch)
{
	struct atm_qdisc_data *p = qdisc_priv(sch);
	struct atm_flow_data *flow;
	unsigned int len;

	pr_debug("atm_tc_drop(sch %p,[qdisc %p])\n", sch, p);
	for (flow = p->flows; flow; flow = flow->next)
		if (flow->q->ops->drop && (len = flow->q->ops->drop(flow->q)))
			return len;
	return 0;
}