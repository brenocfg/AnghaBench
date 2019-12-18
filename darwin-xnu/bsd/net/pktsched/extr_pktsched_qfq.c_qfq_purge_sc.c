#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int32_t ;
struct qfq_if {struct ifclassq* qif_ifq; } ;
struct ifclassq {TYPE_1__* ifcq_disc_slots; } ;
struct TYPE_5__ {scalar_t__ sc; size_t packets; size_t bytes; int /*<<< orphan*/  flow; } ;
typedef  TYPE_2__ cqrq_purge_sc_t ;
struct TYPE_4__ {int /*<<< orphan*/  cl; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 size_t IFCQ_SC_MAX ; 
 size_t MBUF_SCIDX (scalar_t__) ; 
 scalar_t__ MBUF_SC_UNSPEC ; 
 scalar_t__ MBUF_VALID_SC (scalar_t__) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  qfq_purgeq (struct qfq_if*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,size_t*) ; 

__attribute__((used)) static void
qfq_purge_sc(struct qfq_if *qif, cqrq_purge_sc_t *pr)
{
	struct ifclassq *ifq = qif->qif_ifq;
	u_int32_t i;

	IFCQ_LOCK_ASSERT_HELD(ifq);

	VERIFY(pr->sc == MBUF_SC_UNSPEC || MBUF_VALID_SC(pr->sc));
	VERIFY(pr->flow != 0);

	if (pr->sc != MBUF_SC_UNSPEC) {
		i = MBUF_SCIDX(pr->sc);
		VERIFY(i < IFCQ_SC_MAX);

		qfq_purgeq(qif, ifq->ifcq_disc_slots[i].cl,
		    pr->flow, &pr->packets, &pr->bytes);
	} else {
		u_int32_t cnt, len;

		pr->packets = 0;
		pr->bytes = 0;

		for (i = 0; i < IFCQ_SC_MAX; i++) {
			qfq_purgeq(qif, ifq->ifcq_disc_slots[i].cl,
			    pr->flow, &cnt, &len);
			pr->packets += cnt;
			pr->bytes += len;
		}
	}
}