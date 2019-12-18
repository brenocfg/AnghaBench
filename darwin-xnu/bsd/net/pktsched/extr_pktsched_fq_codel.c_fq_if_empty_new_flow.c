#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  fq_flags; } ;
typedef  TYPE_2__ fq_t ;
struct TYPE_8__ {int /*<<< orphan*/  fcl_oldflows_cnt; int /*<<< orphan*/  fcl_newflows_cnt; } ;
struct TYPE_10__ {TYPE_1__ fcl_stat; int /*<<< orphan*/  fcl_old_flows; int /*<<< orphan*/  fcl_new_flows; } ;
typedef  TYPE_3__ fq_if_classq_t ;

/* Variables and functions */
 int /*<<< orphan*/  FQF_NEW_FLOW ; 
 int /*<<< orphan*/  FQF_OLD_FLOW ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flowq ; 
 int /*<<< orphan*/  fq_actlink ; 

__attribute__((used)) static void
fq_if_empty_new_flow(fq_t *fq, fq_if_classq_t *fq_cl, bool add_to_old)
{
	/* Move to the end of old queue list */
	STAILQ_REMOVE(&fq_cl->fcl_new_flows, fq,
	    flowq, fq_actlink);
	fq->fq_flags &= ~FQF_NEW_FLOW;
	fq_cl->fcl_stat.fcl_newflows_cnt--;

	if (add_to_old) {
		STAILQ_INSERT_TAIL(&fq_cl->fcl_old_flows, fq,
		    fq_actlink);
		fq->fq_flags |= FQF_OLD_FLOW;
		fq_cl->fcl_stat.fcl_oldflows_cnt++;
	}
}