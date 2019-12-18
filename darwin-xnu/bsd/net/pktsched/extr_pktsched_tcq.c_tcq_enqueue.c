#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tcq_if {struct tcq_class* tif_default; struct ifclassq* tif_ifq; } ;
struct tcq_class {int /*<<< orphan*/  cl_dropcnt; int /*<<< orphan*/  cl_q; struct tcq_if* cl_tif; } ;
struct pf_mtag {int dummy; } ;
struct ifclassq {int dummy; } ;
struct TYPE_5__ {scalar_t__ pktsched_ptype; } ;
typedef  TYPE_1__ pktsched_pkt_t ;

/* Variables and functions */
 int CLASSQEQ_DROP ; 
 int CLASSQEQ_DROP_FC ; 
 int CLASSQEQ_DROP_SP ; 
 int CLASSQEQ_SUCCESS_FC ; 
 int /*<<< orphan*/  IFCQ_CONVERT_LOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_DROP_ADD (struct ifclassq*,int,int) ; 
 int /*<<< orphan*/  IFCQ_INC_BYTES (struct ifclassq*,int) ; 
 int /*<<< orphan*/  IFCQ_INC_LEN (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 int /*<<< orphan*/  PKTCNTR_ADD (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int pktsched_get_pkt_len (TYPE_1__*) ; 
 scalar_t__ qptype (int /*<<< orphan*/ *) ; 
 int tcq_addq (struct tcq_class*,TYPE_1__*,struct pf_mtag*) ; 
 struct tcq_class* tcq_clh_to_clp (struct tcq_if*,int /*<<< orphan*/ ) ; 

int
tcq_enqueue(struct tcq_if *tif, struct tcq_class *cl, pktsched_pkt_t *pkt,
    struct pf_mtag *t)
{
	struct ifclassq *ifq = tif->tif_ifq;
	int len, ret;

	IFCQ_LOCK_ASSERT_HELD(ifq);
	VERIFY(cl == NULL || cl->cl_tif == tif);

	if (cl == NULL) {
		cl = tcq_clh_to_clp(tif, 0);
		if (cl == NULL) {
			cl = tif->tif_default;
			if (cl == NULL) {
				IFCQ_CONVERT_LOCK(ifq);
				return (CLASSQEQ_DROP);
			}
		}
	}

	VERIFY(pkt->pktsched_ptype == qptype(&cl->cl_q));
	len = pktsched_get_pkt_len(pkt);

	ret = tcq_addq(cl, pkt, t);
	if ((ret != 0) && (ret != CLASSQEQ_SUCCESS_FC)) {
		VERIFY(ret == CLASSQEQ_DROP ||
		    ret == CLASSQEQ_DROP_FC ||
		    ret == CLASSQEQ_DROP_SP);
		PKTCNTR_ADD(&cl->cl_dropcnt, 1, len);
		IFCQ_DROP_ADD(ifq, 1, len);
		return (ret);
	}
	IFCQ_INC_LEN(ifq);
	IFCQ_INC_BYTES(ifq, len);

	/* successfully queued. */
	return (ret);
}