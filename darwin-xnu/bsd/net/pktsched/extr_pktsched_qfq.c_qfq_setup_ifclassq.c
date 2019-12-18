#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct qfq_if {int dummy; } ;
struct qfq_class {int dummy; } ;
struct ifnet {int dummy; } ;
struct ifclassq {scalar_t__ ifcq_type; TYPE_1__* ifcq_disc_slots; int /*<<< orphan*/ * ifcq_disc; struct ifnet* ifcq_ifp; } ;
typedef  int /*<<< orphan*/  classq_pkt_type_t ;
struct TYPE_2__ {size_t qid; struct qfq_class* cl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 int IFCQ_MAXLEN (struct ifclassq*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PKTSCHEDF_QALG_DELAYBASED ; 
 int PKTSCHEDF_QALG_ECN ; 
 int PKTSCHEDF_QALG_FLOWCTL ; 
 int PKTSCHEDF_QALG_SFB ; 
 scalar_t__ PKTSCHEDT_NONE ; 
 int /*<<< orphan*/  PKTSCHEDT_QFQ ; 
 int QFCF_DEFAULTCLASS ; 
 int QFCF_DELAYBASED ; 
 int QFCF_ECN ; 
 int QFCF_FLOWCTL ; 
 int QFCF_LAZY ; 
 int QFCF_SFB ; 
 size_t SCIDX_AV ; 
 size_t SCIDX_BE ; 
 size_t SCIDX_BK ; 
 size_t SCIDX_BK_SYS ; 
 size_t SCIDX_CTL ; 
 size_t SCIDX_OAM ; 
 size_t SCIDX_RD ; 
 size_t SCIDX_RV ; 
 size_t SCIDX_VI ; 
 size_t SCIDX_VO ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int if_sndq_maxlen ; 
 int ifclassq_attach (struct ifclassq*,int /*<<< orphan*/ ,struct qfq_if*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qfq_add_queue (struct qfq_if*,int,int,int,int,size_t,struct qfq_class**,int /*<<< orphan*/ ) ; 
 struct qfq_if* qfq_alloc (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfq_dequeue_ifclassq ; 
 int /*<<< orphan*/  qfq_destroy_locked (struct qfq_if*) ; 
 int /*<<< orphan*/  qfq_enqueue_ifclassq ; 
 int /*<<< orphan*/  qfq_request_ifclassq ; 

int
qfq_setup_ifclassq(struct ifclassq *ifq, u_int32_t flags,
    classq_pkt_type_t ptype)
{
	struct ifnet *ifp = ifq->ifcq_ifp;
	struct qfq_class *cl0, *cl1, *cl2, *cl3, *cl4;
	struct qfq_class *cl5, *cl6, *cl7, *cl8, *cl9;
	struct qfq_if *qif;
	u_int32_t maxlen = 0, qflags = 0;
	int err = 0;

	IFCQ_LOCK_ASSERT_HELD(ifq);
	VERIFY(ifq->ifcq_disc == NULL);
	VERIFY(ifq->ifcq_type == PKTSCHEDT_NONE);

	if (flags & PKTSCHEDF_QALG_SFB)
		qflags |= QFCF_SFB;
	if (flags & PKTSCHEDF_QALG_ECN)
		qflags |= QFCF_ECN;
	if (flags & PKTSCHEDF_QALG_FLOWCTL)
		qflags |= QFCF_FLOWCTL;
	if (flags & PKTSCHEDF_QALG_DELAYBASED)
		qflags |= QFCF_DELAYBASED;

	qif = qfq_alloc(ifp, M_WAITOK);
	if (qif == NULL)
		return (ENOMEM);

	if ((maxlen = IFCQ_MAXLEN(ifq)) == 0)
		maxlen = if_sndq_maxlen;

	if ((err = qfq_add_queue(qif, maxlen, 300, 1200,
	    qflags | QFCF_LAZY, SCIDX_BK_SYS, &cl0, ptype)) != 0)
		goto cleanup;

	if ((err = qfq_add_queue(qif, maxlen, 600, 1400,
	    qflags | QFCF_LAZY, SCIDX_BK, &cl1, ptype)) != 0)
		goto cleanup;

	if ((err = qfq_add_queue(qif, maxlen, 2400, 600,
	    qflags | QFCF_DEFAULTCLASS, SCIDX_BE, &cl2, ptype)) != 0)
		goto cleanup;

	if ((err = qfq_add_queue(qif, maxlen, 2700, 600,
	    qflags | QFCF_LAZY, SCIDX_RD, &cl3, ptype)) != 0)
		goto cleanup;

	if ((err = qfq_add_queue(qif, maxlen, 3000, 400,
	    qflags | QFCF_LAZY, SCIDX_OAM, &cl4, ptype)) != 0)
		goto cleanup;

	if ((err = qfq_add_queue(qif, maxlen, 8000, 1000,
	    qflags | QFCF_LAZY, SCIDX_AV, &cl5, ptype)) != 0)
		goto cleanup;

	if ((err = qfq_add_queue(qif, maxlen, 15000, 1200,
	    qflags | QFCF_LAZY, SCIDX_RV, &cl6, ptype)) != 0)
		goto cleanup;

	if ((err = qfq_add_queue(qif, maxlen, 20000, 1400,
	    qflags | QFCF_LAZY, SCIDX_VI, &cl7, ptype)) != 0)
		goto cleanup;

	if ((err = qfq_add_queue(qif, maxlen, 23000, 200,
	    qflags | QFCF_LAZY, SCIDX_VO, &cl8, ptype)) != 0)
		goto cleanup;

	if ((err = qfq_add_queue(qif, maxlen, 25000, 200,
	    qflags, SCIDX_CTL, &cl9, ptype)) != 0)
		goto cleanup;

	err = ifclassq_attach(ifq, PKTSCHEDT_QFQ, qif,
	    qfq_enqueue_ifclassq, qfq_dequeue_ifclassq, NULL,
	    NULL, NULL, qfq_request_ifclassq);

	/* cache these for faster lookup */
	if (err == 0) {
		ifq->ifcq_disc_slots[SCIDX_BK_SYS].qid = SCIDX_BK_SYS;
		ifq->ifcq_disc_slots[SCIDX_BK_SYS].cl = cl0;

		ifq->ifcq_disc_slots[SCIDX_BK].qid = SCIDX_BK;
		ifq->ifcq_disc_slots[SCIDX_BK].cl = cl1;

		ifq->ifcq_disc_slots[SCIDX_BE].qid = SCIDX_BE;
		ifq->ifcq_disc_slots[SCIDX_BE].cl = cl2;

		ifq->ifcq_disc_slots[SCIDX_RD].qid = SCIDX_RD;
		ifq->ifcq_disc_slots[SCIDX_RD].cl = cl3;

		ifq->ifcq_disc_slots[SCIDX_OAM].qid = SCIDX_OAM;
		ifq->ifcq_disc_slots[SCIDX_OAM].cl = cl4;

		ifq->ifcq_disc_slots[SCIDX_AV].qid = SCIDX_AV;
		ifq->ifcq_disc_slots[SCIDX_AV].cl = cl5;

		ifq->ifcq_disc_slots[SCIDX_RV].qid = SCIDX_RV;
		ifq->ifcq_disc_slots[SCIDX_RV].cl = cl6;

		ifq->ifcq_disc_slots[SCIDX_VI].qid = SCIDX_VI;
		ifq->ifcq_disc_slots[SCIDX_VI].cl = cl7;

		ifq->ifcq_disc_slots[SCIDX_VO].qid = SCIDX_VO;
		ifq->ifcq_disc_slots[SCIDX_VO].cl = cl8;

		ifq->ifcq_disc_slots[SCIDX_CTL].qid = SCIDX_CTL;
		ifq->ifcq_disc_slots[SCIDX_CTL].cl = cl9;
	}

cleanup:
	if (err != 0)
		(void) qfq_destroy_locked(qif);

	return (err);
}