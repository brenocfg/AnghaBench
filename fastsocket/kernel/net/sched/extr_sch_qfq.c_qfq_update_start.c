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
typedef  scalar_t__ u64 ;
struct qfq_sched {scalar_t__ V; int /*<<< orphan*/ * bitmaps; } ;
struct qfq_group {scalar_t__ F; } ;
struct qfq_class {scalar_t__ F; scalar_t__ S; TYPE_1__* grp; } ;
struct TYPE_2__ {int slot_shift; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 size_t ER ; 
 unsigned long mask_from (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qfq_group* qfq_ffs (struct qfq_sched*,unsigned long) ; 
 scalar_t__ qfq_gt (scalar_t__,scalar_t__) ; 
 scalar_t__ qfq_round_down (scalar_t__,int) ; 

__attribute__((used)) static void qfq_update_start(struct qfq_sched *q, struct qfq_class *cl)
{
	unsigned long mask;
	u64 limit, roundedF;
	int slot_shift = cl->grp->slot_shift;

	roundedF = qfq_round_down(cl->F, slot_shift);
	limit = qfq_round_down(q->V, slot_shift) + (1ULL << slot_shift);

	if (!qfq_gt(cl->F, q->V) || qfq_gt(roundedF, limit)) {
		/* timestamp was stale */
		mask = mask_from(q->bitmaps[ER], cl->grp->index);
		if (mask) {
			struct qfq_group *next = qfq_ffs(q, mask);
			if (qfq_gt(roundedF, next->F)) {
				if (qfq_gt(limit, next->F))
					cl->S = next->F;
				else /* preserve timestamp correctness */
					cl->S = limit;
				return;
			}
		}
		cl->S = q->V;
	} else  /* timestamp is not stale */
		cl->S = cl->F;
}