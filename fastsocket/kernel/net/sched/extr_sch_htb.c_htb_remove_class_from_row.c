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
struct htb_sched {scalar_t__** ptr; int* row_mask; TYPE_1__** row; } ;
struct htb_class {size_t level; scalar_t__ node; } ;
struct TYPE_2__ {int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 int ffz (int) ; 
 int /*<<< orphan*/  htb_next_rb_node (scalar_t__*) ; 
 int /*<<< orphan*/  htb_safe_rb_erase (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static inline void htb_remove_class_from_row(struct htb_sched *q,
						 struct htb_class *cl, int mask)
{
	int m = 0;

	while (mask) {
		int prio = ffz(~mask);

		mask &= ~(1 << prio);
		if (q->ptr[cl->level][prio] == cl->node + prio)
			htb_next_rb_node(q->ptr[cl->level] + prio);

		htb_safe_rb_erase(cl->node + prio, q->row[cl->level] + prio);
		if (!q->row[cl->level][prio].rb_node)
			m |= 1 << prio;
	}
	q->row_mask[cl->level] &= ~m;
}