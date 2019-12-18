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
typedef  int /*<<< orphan*/  u_int64_t ;
struct qfq_if {int* qif_bitmaps; int /*<<< orphan*/  qif_V; } ;
struct qfq_group {int /*<<< orphan*/  qfg_S; } ;
typedef  int pktsched_bitmap_t ;

/* Variables and functions */
 size_t ER ; 
 size_t IB ; 
 size_t IR ; 
 struct qfq_group* qfq_ffs (struct qfq_if*,int) ; 
 scalar_t__ qfq_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfq_make_eligible (struct qfq_if*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
qfq_update_eligible(struct qfq_if *qif, u_int64_t old_V)
{
	pktsched_bitmap_t ineligible;

	ineligible = qif->qif_bitmaps[IR] | qif->qif_bitmaps[IB];
	if (ineligible) {
		if (!qif->qif_bitmaps[ER]) {
			struct qfq_group *grp;
			grp = qfq_ffs(qif, ineligible);
			if (qfq_gt(grp->qfg_S, qif->qif_V))
				qif->qif_V = grp->qfg_S;
		}
		qfq_make_eligible(qif, old_V);
	}
}