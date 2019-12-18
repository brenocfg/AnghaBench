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
typedef  int /*<<< orphan*/  u_int32_t ;
struct qfq_if {int /*<<< orphan*/  qif_ifq; } ;
struct qfq_class {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (int /*<<< orphan*/ ) ; 
 int qfq_class_destroy (struct qfq_if*,struct qfq_class*) ; 
 struct qfq_class* qfq_clh_to_clp (struct qfq_if*,int /*<<< orphan*/ ) ; 

int
qfq_remove_queue(struct qfq_if *qif, u_int32_t qid)
{
	struct qfq_class *cl;

	IFCQ_LOCK_ASSERT_HELD(qif->qif_ifq);

	if ((cl = qfq_clh_to_clp(qif, qid)) == NULL)
		return (EINVAL);

	return (qfq_class_destroy(qif, cl));
}