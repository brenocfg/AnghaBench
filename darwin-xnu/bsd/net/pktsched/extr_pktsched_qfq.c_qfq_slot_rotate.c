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
typedef  int u_int32_t ;
struct qfq_if {int qif_maxslots; } ;
struct qfq_group {int qfg_S; int qfg_slot_shift; int qfg_full_slots; int qfg_front; } ;

/* Variables and functions */

__attribute__((used)) static inline void
qfq_slot_rotate(struct qfq_if *qif, struct qfq_group *grp, u_int64_t roundedS)
{
#pragma unused(qif)
	u_int32_t i = (grp->qfg_S - roundedS) >> grp->qfg_slot_shift;

	grp->qfg_full_slots <<= i;
	grp->qfg_front = (grp->qfg_front - i) % qif->qif_maxslots;
}