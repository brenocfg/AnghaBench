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
struct cbq_class {struct tcf_proto* filter_list; } ;
struct cbq_sched_data {struct cbq_class link; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct cbq_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static struct tcf_proto **cbq_find_tcf(struct Qdisc *sch, unsigned long arg)
{
	struct cbq_sched_data *q = qdisc_priv(sch);
	struct cbq_class *cl = (struct cbq_class *)arg;

	if (cl == NULL)
		cl = &q->link;

	return &cl->filter_list;
}