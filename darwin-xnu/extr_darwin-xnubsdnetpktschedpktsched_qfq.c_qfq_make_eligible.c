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
typedef  int u_int64_t ;
struct qfq_if {int qif_V; } ;
typedef  int pktsched_bitmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  EB ; 
 int /*<<< orphan*/  ER ; 
 int /*<<< orphan*/  IB ; 
 int /*<<< orphan*/  IR ; 
 int QFQ_MIN_SLOT_SHIFT ; 
 unsigned long __fls (int) ; 
 int /*<<< orphan*/  qfq_move_groups (struct qfq_if*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
qfq_make_eligible(struct qfq_if *qif, u_int64_t old_V)
{
	pktsched_bitmap_t mask, vslot, old_vslot;

	vslot = qif->qif_V >> QFQ_MIN_SLOT_SHIFT;
	old_vslot = old_V >> QFQ_MIN_SLOT_SHIFT;

	if (vslot != old_vslot) {
		mask = (2UL << (__fls(vslot ^ old_vslot))) - 1;
		qfq_move_groups(qif, mask, IR, ER);
		qfq_move_groups(qif, mask, IB, EB);
	}
}