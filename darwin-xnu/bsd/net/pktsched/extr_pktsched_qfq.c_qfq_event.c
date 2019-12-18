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
struct qfq_if {int qif_maxclasses; struct qfq_class** qif_class_tbl; int /*<<< orphan*/  qif_ifq; } ;
struct qfq_class {int dummy; } ;
typedef  int /*<<< orphan*/  cqev_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfq_updateq (struct qfq_if*,struct qfq_class*,int /*<<< orphan*/ ) ; 

void
qfq_event(struct qfq_if *qif, cqev_t ev)
{
	struct qfq_class *cl;
	int i;

	IFCQ_LOCK_ASSERT_HELD(qif->qif_ifq);

	for (i = 0; i < qif->qif_maxclasses; i++)
		if ((cl = qif->qif_class_tbl[i]) != NULL)
			qfq_updateq(qif, cl, ev);
}