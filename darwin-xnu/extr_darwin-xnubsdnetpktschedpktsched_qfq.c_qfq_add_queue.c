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
typedef  int u_int32_t ;
struct qfq_if {scalar_t__ qif_wsum; int /*<<< orphan*/  qif_ifq; } ;
struct qfq_class {int dummy; } ;
typedef  int /*<<< orphan*/  classq_pkt_type_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (int /*<<< orphan*/ ) ; 
 int QFQ_MAX_WEIGHT ; 
 scalar_t__ QFQ_MAX_WSUM ; 
 int QFQ_MTU_SHIFT ; 
 int QFQ_ONE_FP ; 
 struct qfq_class* qfq_class_create (struct qfq_if*,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * qfq_clh_to_clp (struct qfq_if*,int) ; 

int
qfq_add_queue(struct qfq_if *qif, u_int32_t qlimit, u_int32_t weight,
    u_int32_t maxsz, u_int32_t flags, u_int32_t qid, struct qfq_class **clp,
    classq_pkt_type_t ptype)
{
	struct qfq_class *cl;
	u_int32_t w;

	IFCQ_LOCK_ASSERT_HELD(qif->qif_ifq);

	if (qfq_clh_to_clp(qif, qid) != NULL)
		return (EBUSY);

	/* check parameters */
	if (weight == 0 || weight > QFQ_MAX_WEIGHT)
		return (EINVAL);

	w = (QFQ_ONE_FP / (QFQ_ONE_FP / weight));
	if (qif->qif_wsum + w > QFQ_MAX_WSUM)
		return (EINVAL);

	if (maxsz == 0 || maxsz > (1 << QFQ_MTU_SHIFT))
		return (EINVAL);

	cl = qfq_class_create(qif, weight, qlimit, flags, maxsz, qid, ptype);
	if (cl == NULL)
		return (ENOMEM);

	if (clp != NULL)
		*clp = cl;

	return (0);
}