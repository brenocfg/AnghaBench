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
struct cbq_sched_data {int activemask; struct cbq_class** active; } ;
struct cbq_class {int cpriority; struct cbq_class* next_alive; int /*<<< orphan*/  qdisc; } ;

/* Variables and functions */
 struct cbq_sched_data* qdisc_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline__ void cbq_activate_class(struct cbq_class *cl)
{
	struct cbq_sched_data *q = qdisc_priv(cl->qdisc);
	int prio = cl->cpriority;
	struct cbq_class *cl_tail;

	cl_tail = q->active[prio];
	q->active[prio] = cl;

	if (cl_tail != NULL) {
		cl->next_alive = cl_tail->next_alive;
		cl_tail->next_alive = cl;
	} else {
		cl->next_alive = cl;
		q->activemask |= (1<<prio);
	}
}