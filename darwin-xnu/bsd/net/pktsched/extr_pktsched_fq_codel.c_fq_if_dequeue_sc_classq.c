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
typedef  size_t u_int32_t ;
struct ifclassq {scalar_t__ ifcq_disc; } ;
typedef  int /*<<< orphan*/  mbuf_svc_class_t ;
struct TYPE_4__ {int /*<<< orphan*/ * fqs_classq; } ;
typedef  TYPE_1__ fq_if_t ;
typedef  int /*<<< orphan*/  fq_if_classq_t ;
typedef  int /*<<< orphan*/  classq_pkt_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLASSQ_DEQUEUE_MAX_BYTE_LIMIT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fq_if_dequeue (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t fq_if_service_to_priority (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
fq_if_dequeue_sc_classq(struct ifclassq *ifq, mbuf_svc_class_t svc,
    classq_pkt_type_t *ptype)
{
	void *top;
	fq_if_t *fqs = (fq_if_t *)ifq->ifcq_disc;
	fq_if_classq_t *fq_cl;
	u_int32_t pri;

	pri = fq_if_service_to_priority(fqs, svc);
	fq_cl = &fqs->fqs_classq[pri];

	fq_if_dequeue(fqs, fq_cl, 1, CLASSQ_DEQUEUE_MAX_BYTE_LIMIT,
	    &top, NULL, NULL, NULL, TRUE, ptype);
	return (top);
}