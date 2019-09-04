#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct ifclassq {TYPE_1__* ifcq_disc_slots; int /*<<< orphan*/  ifcq_disc; } ;
struct TYPE_6__ {void* pktsched_pkt; int /*<<< orphan*/  pktsched_ptype; } ;
typedef  TYPE_2__ pktsched_pkt_t ;
typedef  int /*<<< orphan*/  pkt ;
typedef  int /*<<< orphan*/  mbuf_svc_class_t ;
typedef  int /*<<< orphan*/  classq_pkt_type_t ;
struct TYPE_5__ {int /*<<< orphan*/  cl; } ;

/* Variables and functions */
 scalar_t__ IFCQ_SC_MAX ; 
 scalar_t__ MBUF_SCIDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  tcq_dequeue_cl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void *
tcq_dequeue_tc_ifclassq(struct ifclassq *ifq, mbuf_svc_class_t sc,
    classq_pkt_type_t *ptype)
{
	pktsched_pkt_t pkt;
	u_int32_t i = MBUF_SCIDX(sc);

	VERIFY((u_int32_t)i < IFCQ_SC_MAX);

	bzero(&pkt, sizeof (pkt));
	(tcq_dequeue_cl(ifq->ifcq_disc, ifq->ifcq_disc_slots[i].cl, sc, &pkt));
	*ptype = pkt.pktsched_ptype;
	return (pkt.pktsched_pkt);
}