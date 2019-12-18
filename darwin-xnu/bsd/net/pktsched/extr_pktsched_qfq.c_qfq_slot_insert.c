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
typedef  size_t u_int64_t ;
typedef  size_t u_int32_t ;
struct qfq_if {size_t qif_maxslots; } ;
struct qfq_group {size_t qfg_S; size_t qfg_slot_shift; size_t qfg_front; int /*<<< orphan*/  qfg_full_slots; struct qfq_class** qfg_slots; } ;
struct qfq_class {struct qfq_class* cl_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  pktsched_bit_set (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
qfq_slot_insert(struct qfq_if *qif, struct qfq_group *grp,
    struct qfq_class *cl, u_int64_t roundedS)
{
	u_int64_t slot = (roundedS - grp->qfg_S) >> grp->qfg_slot_shift;
	u_int32_t i = (grp->qfg_front + slot) % qif->qif_maxslots;

	cl->cl_next = grp->qfg_slots[i];
	grp->qfg_slots[i] = cl;
	pktsched_bit_set(slot, &grp->qfg_full_slots);
}