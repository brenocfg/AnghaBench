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
typedef  scalar_t__ u64 ;
struct qfq_group {scalar_t__ S; int /*<<< orphan*/  slot_shift; } ;
struct qfq_class {scalar_t__ inv_w; scalar_t__ S; scalar_t__ F; int /*<<< orphan*/  qdisc; } ;

/* Variables and functions */
 unsigned int qdisc_peek_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfq_front_slot_remove (struct qfq_group*) ; 
 scalar_t__ qfq_round_down (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfq_slot_insert (struct qfq_group*,struct qfq_class*,scalar_t__) ; 

__attribute__((used)) static bool qfq_update_class(struct qfq_group *grp, struct qfq_class *cl)
{
	unsigned int len = qdisc_peek_len(cl->qdisc);

	cl->S = cl->F;
	if (!len)
		qfq_front_slot_remove(grp);	/* queue is empty */
	else {
		u64 roundedS;

		cl->F = cl->S + (u64)len * cl->inv_w;
		roundedS = qfq_round_down(cl->S, grp->slot_shift);
		if (roundedS == grp->S)
			return false;

		qfq_front_slot_remove(grp);
		qfq_slot_insert(grp, cl, roundedS);
	}

	return true;
}