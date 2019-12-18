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
typedef  int /*<<< orphan*/  uint32_t ;
struct tcq_if {struct ifclassq* tif_ifq; } ;
struct tcq_class {int /*<<< orphan*/  cl_xmitcnt; int /*<<< orphan*/  cl_period; int /*<<< orphan*/  cl_q; } ;
struct ifclassq {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pktsched_pkt; } ;
typedef  TYPE_1__ pktsched_pkt_t ;
typedef  int /*<<< orphan*/  mbuf_svc_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_DEC_BYTES (struct ifclassq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFCQ_DEC_LEN (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_IS_EMPTY (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_XMIT_ADD (struct ifclassq*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBUF_SCIDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKTCNTR_ADD (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  pktsched_get_pkt_len (TYPE_1__*) ; 
 scalar_t__ qempty (int /*<<< orphan*/ *) ; 
 struct tcq_class* tcq_clh_to_clp (struct tcq_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcq_getq (struct tcq_class*,TYPE_1__*) ; 

__attribute__((used)) static void
tcq_dequeue_cl(struct tcq_if *tif, struct tcq_class *cl, mbuf_svc_class_t sc,
    pktsched_pkt_t *pkt)
{
	struct ifclassq *ifq = tif->tif_ifq;
	uint32_t len;

	IFCQ_LOCK_ASSERT_HELD(ifq);

	if (cl == NULL) {
		cl = tcq_clh_to_clp(tif, MBUF_SCIDX(sc));
		if (cl == NULL) {
			pkt->pktsched_pkt = NULL;
			return;
		}
	}

	if (qempty(&cl->cl_q)) {
		pkt->pktsched_pkt = NULL;
		return;
	}

	VERIFY(!IFCQ_IS_EMPTY(ifq));

	tcq_getq(cl, pkt);
	if (pkt->pktsched_pkt != NULL) {
		len = pktsched_get_pkt_len(pkt);
		IFCQ_DEC_LEN(ifq);
		IFCQ_DEC_BYTES(ifq, len);
		if (qempty(&cl->cl_q))
			cl->cl_period++;
		PKTCNTR_ADD(&cl->cl_xmitcnt, 1, len);
		IFCQ_XMIT_ADD(ifq, 1, len);
	}
}