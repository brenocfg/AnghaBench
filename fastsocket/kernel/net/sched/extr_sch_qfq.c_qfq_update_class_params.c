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
typedef  void* u32 ;
struct qfq_sched {int wsum; int /*<<< orphan*/ * groups; } ;
struct qfq_class {int /*<<< orphan*/ * grp; void* lmax; void* inv_w; } ;

/* Variables and functions */
 int qfq_calc_index (void*,void*) ; 

__attribute__((used)) static void qfq_update_class_params(struct qfq_sched *q, struct qfq_class *cl,
				    u32 lmax, u32 inv_w, int delta_w)
{
	int i;

	/* update qfq-specific data */
	cl->lmax = lmax;
	cl->inv_w = inv_w;
	i = qfq_calc_index(cl->inv_w, cl->lmax);

	cl->grp = &q->groups[i];

	q->wsum += delta_w;
}