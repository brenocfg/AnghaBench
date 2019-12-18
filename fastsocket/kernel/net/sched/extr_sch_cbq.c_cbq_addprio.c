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
struct cbq_sched_data {int /*<<< orphan*/ * quanta; int /*<<< orphan*/ * nclasses; } ;
struct cbq_class {size_t priority; scalar_t__ weight; } ;

/* Variables and functions */
 int /*<<< orphan*/  cbq_normalize_quanta (struct cbq_sched_data*,size_t) ; 

__attribute__((used)) static void cbq_addprio(struct cbq_sched_data *q, struct cbq_class *cl)
{
	q->nclasses[cl->priority]++;
	q->quanta[cl->priority] += cl->weight;
	cbq_normalize_quanta(q, cl->priority);
}