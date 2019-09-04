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
struct qfq_group {size_t qfg_front; int /*<<< orphan*/  qfg_full_slots; struct qfq_class** qfg_slots; } ;
struct qfq_class {struct qfq_class* cl_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  pktsched_bit_clr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
qfq_front_slot_remove(struct qfq_group *grp)
{
	struct qfq_class **h = &grp->qfg_slots[grp->qfg_front];

	*h = (*h)->cl_next;
	if (!*h)
		pktsched_bit_clr(0, &grp->qfg_full_slots);
}