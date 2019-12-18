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
struct qfq_class {int /*<<< orphan*/  cl_q; } ;
struct ifclassq {TYPE_1__* ifcq_disc_slots; } ;
struct TYPE_5__ {scalar_t__ sc; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
typedef  TYPE_2__ cqrq_stat_sc_t ;
struct TYPE_4__ {struct qfq_class* cl; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (struct ifclassq*) ; 
 size_t IFCQ_SC_MAX ; 
 size_t MBUF_SCIDX (scalar_t__) ; 
 scalar_t__ MBUF_SC_UNSPEC ; 
 scalar_t__ MBUF_VALID_SC (scalar_t__) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  qlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qsize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qfq_stat_sc(struct qfq_if *qif, cqrq_stat_sc_t *sr)
{
	struct ifclassq *ifq = qif->qif_ifq;
	struct qfq_class *cl;
	u_int32_t i;

	IFCQ_LOCK_ASSERT_HELD(ifq);

	VERIFY(sr->sc == MBUF_SC_UNSPEC || MBUF_VALID_SC(sr->sc));

	i = MBUF_SCIDX(sr->sc);
	VERIFY(i < IFCQ_SC_MAX);

	cl = ifq->ifcq_disc_slots[i].cl;
	sr->packets = qlen(&cl->cl_q);
	sr->bytes = qsize(&cl->cl_q);

	return (0);
}