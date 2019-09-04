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
typedef  size_t u_int32_t ;
struct ifclassq {scalar_t__ ifcq_disc; } ;
typedef  int /*<<< orphan*/  mbuf_svc_class_t ;
struct TYPE_8__ {int fqs_ptype; TYPE_3__* fqs_classq; } ;
typedef  TYPE_2__ fq_if_t ;
struct TYPE_7__ {scalar_t__ fcl_pkt_cnt; } ;
struct TYPE_9__ {TYPE_1__ fcl_stat; } ;
typedef  TYPE_3__ fq_if_classq_t ;
typedef  int /*<<< orphan*/  (* fq_if_append_pkt_t ) (void*,void*) ;
typedef  int /*<<< orphan*/  classq_pkt_type_t ;

/* Variables and functions */
#define  QP_MBUF 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fq_if_append_mbuf (void*,void*) ; 
 int /*<<< orphan*/  fq_if_dequeue (TYPE_2__*,TYPE_3__*,size_t,size_t,void**,void**,size_t*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t fq_if_service_to_priority (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
fq_if_dequeue_sc_classq_multi(struct ifclassq *ifq, mbuf_svc_class_t svc,
    u_int32_t maxpktcnt, u_int32_t maxbytecnt, void **first_packet,
    void **last_packet, u_int32_t *retpktcnt, u_int32_t *retbytecnt,
    classq_pkt_type_t *ptype)
{
#pragma unused(maxpktcnt, maxbytecnt, first_packet, last_packet, retpktcnt, retbytecnt)
	fq_if_t *fqs = (fq_if_t *)ifq->ifcq_disc;
	u_int32_t pri;
	u_int32_t total_pktcnt = 0, total_bytecnt = 0;
	fq_if_classq_t *fq_cl;
	void *first = NULL, *last = NULL;
	fq_if_append_pkt_t append_pkt;

	switch (fqs->fqs_ptype) {
	case QP_MBUF:
		append_pkt = fq_if_append_mbuf;
		break;


	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	pri = fq_if_service_to_priority(fqs, svc);
	fq_cl = &fqs->fqs_classq[pri];

	/*
	 * Now we have the queue for a particular service class. We need
	 * to dequeue as many packets as needed, first from the new flows
	 * and then from the old flows.
	 */
	while (total_pktcnt < maxpktcnt && total_bytecnt < maxbytecnt &&
	    fq_cl->fcl_stat.fcl_pkt_cnt > 0) {
		void *top, *tail;
		u_int32_t pktcnt = 0, bytecnt = 0;
		fq_if_dequeue(fqs, fq_cl, (maxpktcnt - total_pktcnt),
		    (maxbytecnt - total_bytecnt), &top, &tail, &pktcnt,
		    &bytecnt, TRUE, ptype);
		if (first == NULL) {
			first = top;
			total_pktcnt = pktcnt;
			total_bytecnt = bytecnt;
		} else {
			append_pkt(last, top);
			total_pktcnt += pktcnt;
			total_bytecnt += bytecnt;
		}
		last = tail;
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