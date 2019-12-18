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
struct qfq_if {int /*<<< orphan*/ * qif_bitmaps; } ;
struct qfq_group {int /*<<< orphan*/  qfg_F; } ;
typedef  int pktsched_bitmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  EB ; 
 size_t ER ; 
 int /*<<< orphan*/  IB ; 
 size_t IR ; 
 int mask_from (int /*<<< orphan*/ ,int) ; 
 struct qfq_group* qfq_ffs (struct qfq_if*,int) ; 
 int /*<<< orphan*/  qfq_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfq_move_groups (struct qfq_if*,int,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void
qfq_unblock_groups(struct qfq_if *qif, int index, u_int64_t old_finish)
{
	pktsched_bitmap_t mask = mask_from(qif->qif_bitmaps[ER], index + 1);
	struct qfq_group *next;

	if (mask) {
		next = qfq_ffs(qif, mask);
		if (!qfq_gt(next->qfg_F, old_finish))
			return;
	}

	mask = (1UL << index) - 1;
	qfq_move_groups(qif, mask, EB, ER);
	qfq_move_groups(qif, mask, IB, IR);
}