#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  scalar_t__ u_int64_t ;
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_35__ {scalar_t__ pktsched_ptype; int /*<<< orphan*/  pktsched_pkt; } ;
typedef  TYPE_2__ pktsched_pkt_t ;
struct TYPE_36__ {scalar_t__ fq_ptype; int fq_flags; int /*<<< orphan*/  fq_deficit; int /*<<< orphan*/  fq_bytes; } ;
typedef  TYPE_3__ fq_t ;
struct TYPE_37__ {int /*<<< orphan*/  fqs_ifq; TYPE_3__* fqs_large_flow; } ;
typedef  TYPE_4__ fq_if_t ;
struct TYPE_34__ {int /*<<< orphan*/  fcl_newflows_cnt; int /*<<< orphan*/  fcl_pkt_cnt; int /*<<< orphan*/  fcl_byte_cnt; int /*<<< orphan*/  fcl_drop_overflow; int /*<<< orphan*/  fcl_flow_control_fail; int /*<<< orphan*/  fcl_drop_early; int /*<<< orphan*/  fcl_drop_memfailure; } ;
struct TYPE_38__ {int /*<<< orphan*/  fcl_quantum; TYPE_1__ fcl_stat; int /*<<< orphan*/  fcl_new_flows; } ;
typedef  TYPE_5__ fq_if_classq_t ;

/* Variables and functions */
 int CLASSQEQ_DROP ; 
 int CLASSQEQ_DROP_FC ; 
 int CLASSQEQ_SUCCESS ; 
 int CLASSQEQ_SUCCESS_FC ; 
 int DTYPE_EARLY ; 
 int DTYPE_FORCED ; 
 int DTYPE_NODROP ; 
 int FQF_FLOWCTL_CAPABLE ; 
 int FQF_FLOWCTL_ON ; 
 int FQF_NEW_FLOW ; 
 int FQF_OLD_FLOW ; 
 scalar_t__ FQ_IS_DELAYHIGH (TYPE_3__*) ; 
 int /*<<< orphan*/  IFCQ_CONVERT_LOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ IPPROTO_TCP ; 
 int NSEC_PER_SEC ; 
 int PKTF_FLOW_ADV ; 
 int PKTF_PRIV_GUARDED ; 
 scalar_t__ QP_MBUF ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * STAILQ_NEXT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  fq_actlink ; 
 int /*<<< orphan*/  fq_detect_dequeue_stall (TYPE_4__*,TYPE_3__*,TYPE_5__*,scalar_t__*) ; 
 scalar_t__ fq_empty (TYPE_3__*) ; 
 int /*<<< orphan*/  fq_enqueue (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fq_head_drop (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ fq_if_add_fcentry (TYPE_4__*,TYPE_2__*,int,scalar_t__,TYPE_5__*) ; 
 scalar_t__ fq_if_at_drop_limit (TYPE_4__*) ; 
 int /*<<< orphan*/  fq_if_destroy_flow (TYPE_4__*,TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  fq_if_drop_packet (TYPE_4__*) ; 
 TYPE_3__* fq_if_hash_pkt (TYPE_4__*,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fq_if_is_flow_heavy (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  nanouptime (struct timespec*) ; 
 int pktsched_get_pkt_len (TYPE_2__*) ; 
 int /*<<< orphan*/  pktsched_get_pkt_svc (TYPE_2__*) ; 
 int /*<<< orphan*/  pktsched_get_pkt_vars (TYPE_2__*,int**,scalar_t__**,int*,scalar_t__*,scalar_t__*,int*) ; 

int
fq_addq(fq_if_t *fqs, pktsched_pkt_t *pkt, fq_if_classq_t *fq_cl)
{
	int droptype = DTYPE_NODROP, fc_adv = 0, ret = CLASSQEQ_SUCCESS;
	u_int64_t now;
	fq_t *fq = NULL;
	uint64_t *pkt_timestamp;
	uint32_t *pkt_flags;
	uint32_t pkt_flowid, pkt_tx_start_seq;
	uint8_t pkt_proto, pkt_flowsrc;

	pktsched_get_pkt_vars(pkt, &pkt_flags, &pkt_timestamp, &pkt_flowid,
	    &pkt_flowsrc, &pkt_proto, &pkt_tx_start_seq);

	if (pkt->pktsched_ptype == QP_MBUF) {
		/* See comments in <rdar://problem/14040693> */
		VERIFY(!(*pkt_flags & PKTF_PRIV_GUARDED));
		*pkt_flags |= PKTF_PRIV_GUARDED;
	}

	if (*pkt_timestamp > 0) {
		now = *pkt_timestamp;
	} else {
		struct timespec now_ts;
		nanouptime(&now_ts);
		now = (now_ts.tv_sec * NSEC_PER_SEC) + now_ts.tv_nsec;
		*pkt_timestamp = now;
	}

	/* find the flowq for this packet */
	fq = fq_if_hash_pkt(fqs, pkt_flowid, pktsched_get_pkt_svc(pkt),
	    now, TRUE, pkt->pktsched_ptype);
	if (fq == NULL) {
		/* drop the packet if we could not allocate a flow queue */
		fq_cl->fcl_stat.fcl_drop_memfailure++;
		IFCQ_CONVERT_LOCK(fqs->fqs_ifq);
		return (CLASSQEQ_DROP);
	}
	VERIFY(fq->fq_ptype == pkt->pktsched_ptype);

	fq_detect_dequeue_stall(fqs, fq, fq_cl, &now);

	if (FQ_IS_DELAYHIGH(fq)) {
		if ((fq->fq_flags & FQF_FLOWCTL_CAPABLE) &&
		    (*pkt_flags & PKTF_FLOW_ADV)) {
			fc_adv = 1;
			/*
			 * If the flow is suspended or it is not
			 * TCP, drop the packet
			 */
			if (pkt_proto != IPPROTO_TCP) {
				droptype = DTYPE_EARLY;
				fq_cl->fcl_stat.fcl_drop_early++;
			}
		} else {
			/*
			 * Need to drop a packet, instead of dropping this
			 * one, try to drop from the head of the queue
			 */
			if (!fq_empty(fq)) {
				fq_head_drop(fqs, fq);
				droptype = DTYPE_NODROP;
			} else {
				droptype = DTYPE_EARLY;
			}
			fq_cl->fcl_stat.fcl_drop_early++;
		}

	}

	/* Set the return code correctly */
	if (fc_adv == 1 && droptype != DTYPE_FORCED) {
		if (fq_if_add_fcentry(fqs, pkt, pkt_flowid, pkt_flowsrc,
		    fq_cl)) {
			fq->fq_flags |= FQF_FLOWCTL_ON;
			/* deliver flow control advisory error */
			if (droptype == DTYPE_NODROP) {
				ret = CLASSQEQ_SUCCESS_FC;
			} else {
				/* dropped due to flow control */
				ret = CLASSQEQ_DROP_FC;
			}
		} else {
			/*
			 * if we could not flow control the flow, it is
			 * better to drop
			 */
			droptype = DTYPE_FORCED;
			ret = CLASSQEQ_DROP_FC;
			fq_cl->fcl_stat.fcl_flow_control_fail++;
		}
	}

	/*
	 * If the queue length hits the queue limit, drop a packet from the
	 * front of the queue for a flow with maximum number of bytes. This
	 * will penalize heavy and unresponsive flows. It will also avoid a
	 * tail drop.
	 */
	if (droptype == DTYPE_NODROP && fq_if_at_drop_limit(fqs)) {
		if (fqs->fqs_large_flow == fq) {
			/*
			 * Drop from the head of the current fq. Since a
			 * new packet will be added to the tail, it is ok
			 * to leave fq in place.
			 */
			fq_head_drop(fqs, fq);
		} else {
			if (fqs->fqs_large_flow == NULL) {
				droptype = DTYPE_FORCED;
				fq_cl->fcl_stat.fcl_drop_overflow++;
				ret = CLASSQEQ_DROP;

				/*
				 * if this fq was freshly created and there
				 * is nothing to enqueue, free it
				 */
				if (fq_empty(fq) && !(fq->fq_flags &
				    (FQF_NEW_FLOW | FQF_OLD_FLOW))) {
					fq_if_destroy_flow(fqs, fq_cl, fq);
					fq = NULL;
				}
			} else {
				fq_if_drop_packet(fqs);
			}
		}
	}

	if (droptype == DTYPE_NODROP) {
		uint32_t pkt_len = pktsched_get_pkt_len(pkt);
		fq_enqueue(fq, pkt->pktsched_pkt);
		fq->fq_bytes += pkt_len;
		fq_cl->fcl_stat.fcl_byte_cnt += pkt_len;
		fq_cl->fcl_stat.fcl_pkt_cnt++;

		/*
		 * check if this queue will qualify to be the next
		 * victim queue
		 */
		fq_if_is_flow_heavy(fqs, fq);
	} else {
		IFCQ_CONVERT_LOCK(fqs->fqs_ifq);
		return ((ret != CLASSQEQ_SUCCESS) ? ret : CLASSQEQ_DROP);
	}

	/*
	 * If the queue is not currently active, add it to the end of new
	 * flows list for that service class.
	 */
	if ((fq->fq_flags & (FQF_NEW_FLOW|FQF_OLD_FLOW)) == 0) {
		VERIFY(STAILQ_NEXT(fq, fq_actlink) == NULL);
		STAILQ_INSERT_TAIL(&fq_cl->fcl_new_flows, fq, fq_actlink);
		fq->fq_flags |= FQF_NEW_FLOW;

		fq_cl->fcl_stat.fcl_newflows_cnt++;

		fq->fq_deficit = fq_cl->fcl_quantum;
	}
	return (ret);
}