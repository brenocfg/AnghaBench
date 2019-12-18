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
struct nlattr {int dummy; } ;
struct TYPE_2__ {int ref; int /*<<< orphan*/ * next; int /*<<< orphan*/  classid; int /*<<< orphan*/ * sock; int /*<<< orphan*/ * vcc; int /*<<< orphan*/ * filter_list; int /*<<< orphan*/ * q; } ;
struct atm_qdisc_data {int /*<<< orphan*/  task; TYPE_1__ link; TYPE_1__* flows; } ;
struct Qdisc {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/ * qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct atm_qdisc_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_atm_dequeue ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int atm_tc_init(struct Qdisc *sch, struct nlattr *opt)
{
	struct atm_qdisc_data *p = qdisc_priv(sch);

	pr_debug("atm_tc_init(sch %p,[qdisc %p],opt %p)\n", sch, p, opt);
	p->flows = &p->link;
	p->link.q = qdisc_create_dflt(qdisc_dev(sch), sch->dev_queue,
				      &pfifo_qdisc_ops, sch->handle);
	if (!p->link.q)
		p->link.q = &noop_qdisc;
	pr_debug("atm_tc_init: link (%p) qdisc %p\n", &p->link, p->link.q);
	p->link.filter_list = NULL;
	p->link.vcc = NULL;
	p->link.sock = NULL;
	p->link.classid = sch->handle;
	p->link.ref = 1;
	p->link.next = NULL;
	tasklet_init(&p->task, sch_atm_dequeue, (unsigned long)sch);
	return 0;
}