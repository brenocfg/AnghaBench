#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ifclassq {int /*<<< orphan*/  ifcq_disc; } ;
struct TYPE_4__ {void* pktsched_pkt; int /*<<< orphan*/  pktsched_ptype; } ;
typedef  TYPE_1__ pktsched_pkt_t ;
typedef  int /*<<< orphan*/  pkt ;
typedef  int /*<<< orphan*/  classq_pkt_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  qfq_dequeue (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void *
qfq_dequeue_ifclassq(struct ifclassq *ifq, classq_pkt_type_t *ptype)
{
	pktsched_pkt_t pkt;
	bzero(&pkt, sizeof (pkt));
	qfq_dequeue(ifq->ifcq_disc, &pkt);
	*ptype = pkt.pktsched_ptype;
	return (pkt.pktsched_pkt);
}