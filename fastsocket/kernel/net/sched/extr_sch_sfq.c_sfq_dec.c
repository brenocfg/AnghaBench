#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sfq_sched_data {scalar_t__ max_depth; TYPE_1__* qs; TYPE_2__* dep; } ;
typedef  size_t sfq_index ;
struct TYPE_4__ {size_t next; size_t prev; } ;
struct TYPE_3__ {scalar_t__ qlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  sfq_link (struct sfq_sched_data*,size_t) ; 

__attribute__((used)) static inline void sfq_dec(struct sfq_sched_data *q, sfq_index x)
{
	sfq_index p, n;

	n = q->dep[x].next;
	p = q->dep[x].prev;
	q->dep[p].next = n;
	q->dep[n].prev = p;

	if (n == p && q->max_depth == q->qs[x].qlen + 1)
		q->max_depth--;

	sfq_link(q, x);
}