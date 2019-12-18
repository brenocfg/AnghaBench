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
struct qfq_sched {unsigned long* bitmaps; } ;

/* Variables and functions */

__attribute__((used)) static inline void qfq_move_groups(struct qfq_sched *q, unsigned long mask,
				   int src, int dst)
{
	q->bitmaps[dst] |= q->bitmaps[src] & mask;
	q->bitmaps[src] &= ~mask;
}