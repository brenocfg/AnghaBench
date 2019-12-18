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
struct tcf_proto {int dummy; } ;
struct hfsc_class {struct tcf_proto* filter_list; } ;
struct hfsc_sched {struct hfsc_class root; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static struct tcf_proto **
hfsc_tcf_chain(struct Qdisc *sch, unsigned long arg)
{
	struct hfsc_sched *q = qdisc_priv(sch);
	struct hfsc_class *cl = (struct hfsc_class *)arg;

	if (cl == NULL)
		cl = &q->root;

	return &cl->filter_list;
}