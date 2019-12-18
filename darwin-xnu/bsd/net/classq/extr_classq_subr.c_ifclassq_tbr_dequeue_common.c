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
typedef  void* u_int64_t ;
struct tb_regulator {scalar_t__ tbr_token; void* tbr_last; int tbr_filluptime; scalar_t__ tbr_depth; int tbr_rate; } ;
struct ifclassq {struct tb_regulator ifcq_tbr; } ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  mbuf_svc_class_t ;
typedef  int int64_t ;
typedef  int classq_pkt_type_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_DEQUEUE (struct ifclassq*,void*,int*) ; 
 int /*<<< orphan*/  IFCQ_DEQUEUE_SC (struct ifclassq*,int /*<<< orphan*/ ,void*,int*) ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 int IFCQ_TBR_IS_ENABLED (struct ifclassq*) ; 
 scalar_t__ MBUF_VALID_SC (int /*<<< orphan*/ ) ; 
#define  QP_MBUF 128 
 int /*<<< orphan*/  TBR_SCALE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  m_pktlen (int /*<<< orphan*/ ) ; 
 void* read_machclk () ; 

__attribute__((used)) static void *
ifclassq_tbr_dequeue_common(struct ifclassq *ifq, mbuf_svc_class_t sc,
    boolean_t drvmgt, classq_pkt_type_t *ptype)
{
	struct tb_regulator *tbr;
	void *p;
	int64_t interval;
	u_int64_t now;

	IFCQ_LOCK_ASSERT_HELD(ifq);

	VERIFY(!drvmgt || MBUF_VALID_SC(sc));
	VERIFY(IFCQ_TBR_IS_ENABLED(ifq));

	tbr = &ifq->ifcq_tbr;
	/* update token only when it is negative */
	if (tbr->tbr_token <= 0) {
		now = read_machclk();
		interval = now - tbr->tbr_last;
		if (interval >= tbr->tbr_filluptime) {
			tbr->tbr_token = tbr->tbr_depth;
		} else {
			tbr->tbr_token += interval * tbr->tbr_rate;
			if (tbr->tbr_token > tbr->tbr_depth)
				tbr->tbr_token = tbr->tbr_depth;
		}
		tbr->tbr_last = now;
	}
	/* if token is still negative, don't allow dequeue */
	if (tbr->tbr_token <= 0)
		return (NULL);

	/*
	 * ifclassq takes precedence over ALTQ queue;
	 * ifcq_drain count is adjusted by the caller.
	 */
		if (drvmgt)
			IFCQ_DEQUEUE_SC(ifq, sc, p, ptype);
		else
			IFCQ_DEQUEUE(ifq, p, ptype);

	if (p != NULL) {
		switch (*ptype) {
		case QP_MBUF:
			tbr->tbr_token -= TBR_SCALE(m_pktlen((mbuf_t)p));
			break;


		default:
			VERIFY(0);
			/* NOTREACHED */
		}
	}

	return (p);
}