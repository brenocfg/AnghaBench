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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ u_int64_t ;
typedef  size_t u_int32_t ;
struct qfq_if {scalar_t__* qif_bitmaps; scalar_t__ qif_V; scalar_t__ qif_queued; int /*<<< orphan*/  qif_emptygrp; struct ifclassq* qif_ifq; } ;
struct qfq_group {scalar_t__ qfg_full_slots; size_t qfg_front; scalar_t__ qfg_F; unsigned long long qfg_slot_shift; scalar_t__ qfg_S; int /*<<< orphan*/  qfg_index; struct qfq_class** qfg_slots; } ;
struct qfq_class {int /*<<< orphan*/  cl_S; int /*<<< orphan*/  cl_F; int /*<<< orphan*/  cl_handle; int /*<<< orphan*/  cl_xmitcnt; int /*<<< orphan*/  cl_period; int /*<<< orphan*/  cl_q; } ;
struct ifclassq {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pktsched_pkt; } ;
typedef  TYPE_1__ pktsched_pkt_t ;
typedef  scalar_t__ pktsched_bitmap_t ;

/* Variables and functions */
 size_t ER ; 
 int /*<<< orphan*/  IFCQ_DEC_BYTES (struct ifclassq*,size_t) ; 
 int /*<<< orphan*/  IFCQ_DEC_LEN (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_IS_EMPTY (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_XMIT_ADD (struct ifclassq*,int,size_t) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  PKTCNTR_ADD (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  QFQIF_IFP (struct qfq_if*) ; 
 scalar_t__ QFQ_IWSUM ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pktsched_bit_clr (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pktsched_bit_set (int /*<<< orphan*/ ,scalar_t__*) ; 
 size_t pktsched_get_pkt_len (TYPE_1__*) ; 
 int pktsched_verbose ; 
 scalar_t__ qempty (int /*<<< orphan*/ *) ; 
 size_t qfq_calc_state (struct qfq_if*,struct qfq_group*) ; 
 int /*<<< orphan*/  qfq_dump_sched (struct qfq_if*,char*) ; 
 struct qfq_group* qfq_ffs (struct qfq_if*,scalar_t__) ; 
 int /*<<< orphan*/  qfq_getq (struct qfq_class*,TYPE_1__*) ; 
 scalar_t__ qfq_round_down (int /*<<< orphan*/ ,unsigned long long) ; 
 struct qfq_class* qfq_slot_scan (struct qfq_if*,struct qfq_group*) ; 
 int /*<<< orphan*/  qfq_style (struct qfq_if*) ; 
 int /*<<< orphan*/  qfq_unblock_groups (struct qfq_if*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ qfq_update_class (struct qfq_if*,struct qfq_group*,struct qfq_class*) ; 
 int /*<<< orphan*/  qfq_update_eligible (struct qfq_if*,scalar_t__) ; 

void
qfq_dequeue(struct qfq_if *qif, pktsched_pkt_t *pkt)
{
	pktsched_bitmap_t er_bits = qif->qif_bitmaps[ER];
	struct ifclassq *ifq = qif->qif_ifq;
	struct qfq_group *grp;
	struct qfq_class *cl;
	u_int64_t old_V;
	u_int32_t len;

	IFCQ_LOCK_ASSERT_HELD(ifq);

	pkt->pktsched_pkt = NULL;

	for (;;) {
		if (er_bits == 0) {
#if QFQ_DEBUG
			if (qif->qif_queued && pktsched_verbose > 1)
				qfq_dump_sched(qif, "start dequeue");
#endif /* QFQ_DEBUG */
			/* no eligible and ready packet */
			return;
		}
		grp = qfq_ffs(qif, er_bits);
		/* if group is non-empty, use it */
		if (grp->qfg_full_slots != 0)
			break;
		pktsched_bit_clr(grp->qfg_index, &er_bits);
#if QFQ_DEBUG
		qif->qif_emptygrp++;
#endif /* QFQ_DEBUG */
	}
	VERIFY(!IFCQ_IS_EMPTY(ifq));

	cl = grp->qfg_slots[grp->qfg_front];
	VERIFY(cl != NULL && !qempty(&cl->cl_q));

	qfq_getq(cl, pkt);
	VERIFY(pkt->pktsched_pkt != NULL); /* qalg must be work conserving */
	len = pktsched_get_pkt_len(pkt);

#if QFQ_DEBUG
	qif->qif_queued--;
#endif /* QFQ_DEBUG */

	IFCQ_DEC_LEN(ifq);
	IFCQ_DEC_BYTES(ifq, len);
	if (qempty(&cl->cl_q))
		cl->cl_period++;
	PKTCNTR_ADD(&cl->cl_xmitcnt, 1, len);
	IFCQ_XMIT_ADD(ifq, 1, len);

	old_V = qif->qif_V;
	qif->qif_V += (u_int64_t)len * QFQ_IWSUM;

	if (pktsched_verbose > 2) {
		log(LOG_DEBUG, "%s: %s qid=%d dequeue pkt=0x%llx F=0x%llx "
		    "V=0x%llx", if_name(QFQIF_IFP(qif)), qfq_style(qif),
		    cl->cl_handle,
		    (uint64_t)VM_KERNEL_ADDRPERM(pkt->pktsched_pkt), cl->cl_F,
		    qif->qif_V);
	}

	if (qfq_update_class(qif, grp, cl)) {
		u_int64_t old_F = grp->qfg_F;

		cl = qfq_slot_scan(qif, grp);
		if (!cl) { /* group gone, remove from ER */
			pktsched_bit_clr(grp->qfg_index, &qif->qif_bitmaps[ER]);
		} else {
			u_int32_t s;
			u_int64_t roundedS =
			    qfq_round_down(cl->cl_S, grp->qfg_slot_shift);

			if (grp->qfg_S == roundedS)
				goto skip_unblock;

			grp->qfg_S = roundedS;
			grp->qfg_F = roundedS + (2ULL << grp->qfg_slot_shift);

			/* remove from ER and put in the new set */
			pktsched_bit_clr(grp->qfg_index, &qif->qif_bitmaps[ER]);
			s = qfq_calc_state(qif, grp);
			pktsched_bit_set(grp->qfg_index, &qif->qif_bitmaps[s]);
		}
		/* we need to unblock even if the group has gone away */
		qfq_unblock_groups(qif, grp->qfg_index, old_F);
	}

skip_unblock:
	qfq_update_eligible(qif, old_V);

#if QFQ_DEBUG
	if (!qif->qif_bitmaps[ER] && qif->qif_queued && pktsched_verbose > 1)
		qfq_dump_sched(qif, "end dequeue");
#endif /* QFQ_DEBUG */
}