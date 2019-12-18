#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct ifclassq {scalar_t__ ifcq_disc; } ;
struct TYPE_8__ {int fqs_ptype; int* fqs_bitmaps; TYPE_3__* fqs_classq; } ;
typedef  TYPE_2__ fq_if_t ;
struct TYPE_7__ {int /*<<< orphan*/  fcl_flows_cnt; } ;
struct TYPE_9__ {scalar_t__ fcl_budget; int fcl_quantum; TYPE_1__ fcl_stat; int /*<<< orphan*/  fcl_drr_max; } ;
typedef  TYPE_3__ fq_if_classq_t ;
typedef  int /*<<< orphan*/  (* fq_if_append_pkt_t ) (void*,void*) ;
typedef  int classq_pkt_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FQ_IF_CLASSQ_IDLE (TYPE_3__*) ; 
 size_t FQ_IF_EB ; 
 size_t FQ_IF_ER ; 
 size_t FQ_IF_IB ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_XMIT_ADD (struct ifclassq*,scalar_t__,scalar_t__) ; 
#define  QP_MBUF 128 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  fq_if_append_mbuf (void*,void*) ; 
 int /*<<< orphan*/  fq_if_dequeue (TYPE_2__*,TYPE_3__*,scalar_t__,scalar_t__,void**,void**,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int*) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pktsched_bit_clr (int,int*) ; 
 int /*<<< orphan*/  pktsched_bit_set (int,int*) ; 
 int pktsched_ffs (int) ; 

int
fq_if_dequeue_classq_multi(struct ifclassq *ifq, u_int32_t maxpktcnt,
    u_int32_t maxbytecnt, void **first_packet,
    void **last_packet, u_int32_t *retpktcnt, u_int32_t *retbytecnt,
    classq_pkt_type_t *ptype)
{
	void *top = NULL, *tail = NULL, *first, *last;
	u_int32_t pktcnt = 0, bytecnt = 0, total_pktcnt, total_bytecnt;
	fq_if_t *fqs;
	fq_if_classq_t *fq_cl;
	int pri;
	fq_if_append_pkt_t append_pkt;

	IFCQ_LOCK_ASSERT_HELD(ifq);

	fqs = (fq_if_t *)ifq->ifcq_disc;

	switch (fqs->fqs_ptype) {
	case QP_MBUF:
		append_pkt = fq_if_append_mbuf;
		break;


	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	first = last = NULL;
	total_pktcnt = total_bytecnt = 0;
	*ptype = fqs->fqs_ptype;

	for (;;) {
		classq_pkt_type_t tmp_ptype;
		if (fqs->fqs_bitmaps[FQ_IF_ER] == 0 &&
		    fqs->fqs_bitmaps[FQ_IF_EB] == 0) {
			fqs->fqs_bitmaps[FQ_IF_EB] = fqs->fqs_bitmaps[FQ_IF_IB];
			fqs->fqs_bitmaps[FQ_IF_IB] = 0;
			if (fqs->fqs_bitmaps[FQ_IF_EB] == 0)
				break;
		}
		pri = pktsched_ffs(fqs->fqs_bitmaps[FQ_IF_ER]);
		if (pri == 0) {
			/*
			 * There are no ER flows, move the highest
			 * priority one from EB if there are any in that
			 * category
			 */
			pri = pktsched_ffs(fqs->fqs_bitmaps[FQ_IF_EB]);
			VERIFY(pri > 0);
			pktsched_bit_clr((pri - 1),
			    &fqs->fqs_bitmaps[FQ_IF_EB]);
			pktsched_bit_set((pri - 1),
			    &fqs->fqs_bitmaps[FQ_IF_ER]);
		}
		pri--; /* index starts at 0 */
		fq_cl = &fqs->fqs_classq[pri];

		if (fq_cl->fcl_budget <= 0) {
			/* Update the budget */
			fq_cl->fcl_budget += (min(fq_cl->fcl_drr_max,
			    fq_cl->fcl_stat.fcl_flows_cnt) *
			    fq_cl->fcl_quantum);
			if (fq_cl->fcl_budget <= 0)
				goto state_change;
		}
		fq_if_dequeue(fqs, fq_cl, (maxpktcnt - total_pktcnt),
		    (maxbytecnt - total_bytecnt), &top, &tail, &pktcnt,
		    &bytecnt, FALSE, &tmp_ptype);
		if (top != NULL) {
			ASSERT(tmp_ptype == *ptype);
			ASSERT(pktcnt > 0 && bytecnt > 0);
			if (first == NULL) {
				first = top;
				last = tail;
				total_pktcnt = pktcnt;
				total_bytecnt = bytecnt;
			} else {
				append_pkt(last, top);
				last = tail;
				total_pktcnt += pktcnt;
				total_bytecnt += bytecnt;
			}
			append_pkt(last, NULL);
			fq_cl->fcl_budget -= bytecnt;
			pktcnt = 0;
			bytecnt = 0;
		}

		/*
		 * If the class has exceeded the budget but still has data
		 * to send, move it to IB
		 */
state_change:
		if (!FQ_IF_CLASSQ_IDLE(fq_cl)) {
			if (fq_cl->fcl_budget <= 0) {
				pktsched_bit_set(pri,
				    &fqs->fqs_bitmaps[FQ_IF_IB]);
				pktsched_bit_clr(pri,
				    &fqs->fqs_bitmaps[FQ_IF_ER]);
			}
		} else {
			pktsched_bit_clr(pri, &fqs->fqs_bitmaps[FQ_IF_ER]);
			VERIFY(((fqs->fqs_bitmaps[FQ_IF_ER] |
			    fqs->fqs_bitmaps[FQ_IF_EB] |
			    fqs->fqs_bitmaps[FQ_IF_IB])&(1 << pri)) == 0);
			fq_cl->fcl_budget = 0;
		}
		if (total_pktcnt >= maxpktcnt || total_bytecnt >= maxbytecnt)
			break;
	}
	if (first != NULL) {
		if (first_packet != NULL)
			*first_packet = first;
		if (last_packet != NULL)
			*last_packet = last;
		if (retpktcnt != NULL)
			*retpktcnt = total_pktcnt;
		if (retbytecnt != NULL)
			*retbytecnt = total_bytecnt;
		IFCQ_XMIT_ADD(ifq, total_pktcnt, total_bytecnt);
	} else {
		if (first_packet != NULL)
			*first_packet = NULL;
		if (last_packet != NULL)
			*last_packet = NULL;
		if (retpktcnt != NULL)
			*retpktcnt = 0;
		if (retbytecnt != NULL)
			*retbytecnt = 0;
	}
	return (0);
}