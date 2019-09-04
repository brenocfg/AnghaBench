#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
struct ifclassq {scalar_t__ ifcq_disc; } ;
typedef  int /*<<< orphan*/  pktsched_pkt_t ;
typedef  TYPE_2__* mbuf_t ;
typedef  scalar_t__ mbuf_svc_class_t ;
struct TYPE_12__ {int fqs_throttle; int fqs_flags; int* fqs_bitmaps; TYPE_4__* fqs_classq; } ;
typedef  TYPE_3__ fq_if_t ;
struct TYPE_10__ {int /*<<< orphan*/  fcl_throttle_drops; } ;
struct TYPE_13__ {TYPE_1__ fcl_stat; } ;
typedef  TYPE_4__ fq_if_classq_t ;
typedef  int /*<<< orphan*/  classq_pkt_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_11__ {int m_flags; } ;

/* Variables and functions */
#define  CLASSQEQ_DROP 130 
#define  CLASSQEQ_DROP_FC 129 
#define  CLASSQEQ_DROP_SP 128 
 int CLASSQEQ_SUCCESS_FC ; 
 int ENOBUFS ; 
 int EQFULL ; 
 int EQSUSPENDED ; 
 int /*<<< orphan*/  FALSE ; 
 int FQS_DRIVER_MANAGED ; 
 int /*<<< orphan*/  FQ_IF_CLASSQ_IDLE (TYPE_4__*) ; 
 size_t FQ_IF_EB ; 
 size_t FQ_IF_ER ; 
 size_t FQ_IF_IB ; 
 size_t FQ_IF_MAX_CLASSES ; 
 int /*<<< orphan*/  IFCQ_CONVERT_LOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_INC_BYTES (struct ifclassq*,int) ; 
 int /*<<< orphan*/  IFCQ_INC_LEN (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 scalar_t__ MBUF_SC_BK_SYS ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  QP_MBUF ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int fq_addq (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 size_t fq_if_service_to_priority (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  m_freem (TYPE_2__*) ; 
 int /*<<< orphan*/  pktsched_bit_set (size_t,int*) ; 
 int /*<<< orphan*/  pktsched_free_pkt (int /*<<< orphan*/ *) ; 
 int pktsched_get_pkt_len (int /*<<< orphan*/ *) ; 
 scalar_t__ pktsched_get_pkt_svc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pktsched_pkt_encap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

int
fq_if_enqueue_classq(struct ifclassq *ifq, void *p, classq_pkt_type_t ptype,
    boolean_t *pdrop)
{
	u_int32_t pri;
	fq_if_t *fqs;
	fq_if_classq_t *fq_cl;
	int ret, len;
	mbuf_svc_class_t svc;
	pktsched_pkt_t pkt;

	IFCQ_LOCK_ASSERT_HELD(ifq);
	if ((ptype == QP_MBUF) && !(((mbuf_t)p)->m_flags & M_PKTHDR)) {
		IFCQ_CONVERT_LOCK(ifq);
		m_freem((mbuf_t)p);
		*pdrop = TRUE;
		return (ENOBUFS);
	}
	pktsched_pkt_encap(&pkt, ptype, p);

	fqs = (fq_if_t *)ifq->ifcq_disc;
	svc = pktsched_get_pkt_svc(&pkt);
	pri = fq_if_service_to_priority(fqs, svc);
	VERIFY(pri >= 0 && pri < FQ_IF_MAX_CLASSES);
	fq_cl = &fqs->fqs_classq[pri];

	if (svc == MBUF_SC_BK_SYS && fqs->fqs_throttle == 1) {
		/* BK_SYS is currently throttled */
		fq_cl->fcl_stat.fcl_throttle_drops++;
		IFCQ_CONVERT_LOCK(ifq);
		pktsched_free_pkt(&pkt);
		*pdrop = TRUE;
		return (EQSUSPENDED);
	}

	len = pktsched_get_pkt_len(&pkt);
	ret = fq_addq(fqs, &pkt, fq_cl);
	if (!(fqs->fqs_flags & FQS_DRIVER_MANAGED) &&
	    !FQ_IF_CLASSQ_IDLE(fq_cl)) {
		if (((fqs->fqs_bitmaps[FQ_IF_ER] | fqs->fqs_bitmaps[FQ_IF_EB]) &
		    (1 << pri)) == 0) {
			/*
			 * this group is not in ER or EB groups,
			 * mark it as IB
			 */
			pktsched_bit_set(pri, &fqs->fqs_bitmaps[FQ_IF_IB]);
		}
	}

	if (ret != 0) {
		if (ret == CLASSQEQ_SUCCESS_FC) {
			/* packet enqueued, return advisory feedback */
			ret = EQFULL;
			*pdrop = FALSE;
		} else {
			*pdrop = TRUE;
			VERIFY(ret == CLASSQEQ_DROP ||
			    ret == CLASSQEQ_DROP_FC ||
			    ret == CLASSQEQ_DROP_SP);
			pktsched_free_pkt(&pkt);
			switch (ret) {
			case CLASSQEQ_DROP:
				return (ENOBUFS);
			case CLASSQEQ_DROP_FC:
				return (EQFULL);
			case CLASSQEQ_DROP_SP:
				return (EQSUSPENDED);
			}
		}
	} else {
		*pdrop = FALSE;
	}
	IFCQ_INC_LEN(ifq);
	IFCQ_INC_BYTES(ifq, len);
	return (ret);
}