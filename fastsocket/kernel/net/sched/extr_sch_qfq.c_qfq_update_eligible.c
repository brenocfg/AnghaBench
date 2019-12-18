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
typedef  int /*<<< orphan*/  u64 ;
struct qfq_sched {unsigned long* bitmaps; int /*<<< orphan*/  V; } ;
struct qfq_group {int /*<<< orphan*/  S; } ;

/* Variables and functions */
 size_t ER ; 
 size_t IB ; 
 size_t IR ; 
 struct qfq_group* qfq_ffs (struct qfq_sched*,unsigned long) ; 
 scalar_t__ qfq_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfq_make_eligible (struct qfq_sched*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qfq_update_eligible(struct qfq_sched *q, u64 old_V)
{
	struct qfq_group *grp;
	unsigned long ineligible;

	ineligible = q->bitmaps[IR] | q->bitmaps[IB];
	if (ineligible) {
		if (!q->bitmaps[ER]) {
			grp = qfq_ffs(q, ineligible);
			if (qfq_gt(grp->S, q->V))
				q->V = grp->S;
		}
		qfq_make_eligible(q, old_V);
	}
}