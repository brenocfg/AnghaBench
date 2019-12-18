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
struct cbq_sched_data {scalar_t__ toplevel; } ;
struct cbq_class {scalar_t__ level; struct cbq_class* borrow; int /*<<< orphan*/  qdisc; } ;

/* Variables and functions */
 int /*<<< orphan*/  cbq_ovl_classic (struct cbq_class*) ; 
 struct cbq_sched_data* qdisc_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cbq_ovl_rclassic(struct cbq_class *cl)
{
	struct cbq_sched_data *q = qdisc_priv(cl->qdisc);
	struct cbq_class *this = cl;

	do {
		if (cl->level > q->toplevel) {
			cl = NULL;
			break;
		}
	} while ((cl = cl->borrow) != NULL);

	if (cl == NULL)
		cl = this;
	cbq_ovl_classic(cl);
}