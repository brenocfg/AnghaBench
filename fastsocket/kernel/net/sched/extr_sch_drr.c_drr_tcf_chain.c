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
struct drr_sched {struct tcf_proto* filter_list; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 struct drr_sched* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static struct tcf_proto **drr_tcf_chain(struct Qdisc *sch, unsigned long cl)
{
	struct drr_sched *q = qdisc_priv(sch);

	if (cl)
		return NULL;

	return &q->filter_list;
}