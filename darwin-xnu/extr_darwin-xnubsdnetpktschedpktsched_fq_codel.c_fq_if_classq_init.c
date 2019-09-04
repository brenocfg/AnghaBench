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
struct TYPE_4__ {TYPE_2__* fqs_classq; } ;
typedef  TYPE_1__ fq_if_t ;
struct TYPE_5__ {scalar_t__ fcl_quantum; size_t fcl_pri; size_t fcl_drr_max; size_t fcl_service_class; int /*<<< orphan*/  fcl_old_flows; int /*<<< orphan*/  fcl_new_flows; } ;
typedef  TYPE_2__ fq_if_classq_t ;

/* Variables and functions */
 size_t FQ_IF_MAX_CLASSES ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 

void
fq_if_classq_init(fq_if_t *fqs, u_int32_t pri, u_int32_t quantum,
    u_int32_t drr_max, u_int32_t svc_class)
{
	fq_if_classq_t *fq_cl;

	fq_cl = &fqs->fqs_classq[pri];

	VERIFY(pri >= 0 && pri < FQ_IF_MAX_CLASSES &&
	    fq_cl->fcl_quantum == 0);
	fq_cl->fcl_quantum = quantum;
	fq_cl->fcl_pri = pri;
	fq_cl->fcl_drr_max = drr_max;
	fq_cl->fcl_service_class = svc_class;
	STAILQ_INIT(&fq_cl->fcl_new_flows);
	STAILQ_INIT(&fq_cl->fcl_old_flows);
}