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
struct cbq_sched_data {scalar_t__ now; scalar_t__ toplevel; } ;
struct TYPE_2__ {int /*<<< orphan*/  overlimits; } ;
struct cbq_class {scalar_t__ undertime; scalar_t__ level; scalar_t__ delayed; int /*<<< orphan*/  (* overlimit ) (struct cbq_class*) ;TYPE_1__ qstats; struct cbq_class* borrow; int /*<<< orphan*/ * tparent; int /*<<< orphan*/  qdisc; } ;

/* Variables and functions */
 scalar_t__ PSCHED_PASTPERFECT ; 
 struct cbq_sched_data* qdisc_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cbq_class*) ; 

__attribute__((used)) static __inline__ struct cbq_class *
cbq_under_limit(struct cbq_class *cl)
{
	struct cbq_sched_data *q = qdisc_priv(cl->qdisc);
	struct cbq_class *this_cl = cl;

	if (cl->tparent == NULL)
		return cl;

	if (cl->undertime == PSCHED_PASTPERFECT || q->now >= cl->undertime) {
		cl->delayed = 0;
		return cl;
	}

	do {
		/* It is very suspicious place. Now overlimit
		   action is generated for not bounded classes
		   only if link is completely congested.
		   Though it is in agree with ancestor-only paradigm,
		   it looks very stupid. Particularly,
		   it means that this chunk of code will either
		   never be called or result in strong amplification
		   of burstiness. Dangerous, silly, and, however,
		   no another solution exists.
		 */
		if ((cl = cl->borrow) == NULL) {
			this_cl->qstats.overlimits++;
			this_cl->overlimit(this_cl);
			return NULL;
		}
		if (cl->level > q->toplevel)
			return NULL;
	} while (cl->undertime != PSCHED_PASTPERFECT && q->now < cl->undertime);

	cl->delayed = 0;
	return cl;
}