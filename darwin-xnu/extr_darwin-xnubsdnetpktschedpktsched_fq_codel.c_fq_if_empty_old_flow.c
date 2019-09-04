#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ fq_bytes; int /*<<< orphan*/  fq_flags; } ;
typedef  TYPE_2__ fq_t ;
typedef  int /*<<< orphan*/  fq_if_t ;
struct TYPE_9__ {int /*<<< orphan*/  fcl_oldflows_cnt; } ;
struct TYPE_11__ {TYPE_1__ fcl_stat; int /*<<< orphan*/  fcl_old_flows; } ;
typedef  TYPE_3__ fq_if_classq_t ;

/* Variables and functions */
 int /*<<< orphan*/  FQF_OLD_FLOW ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  flowq ; 
 int /*<<< orphan*/  fq_actlink ; 
 int /*<<< orphan*/  fq_if_destroy_flow (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static void
fq_if_empty_old_flow(fq_if_t *fqs, fq_if_classq_t *fq_cl, fq_t *fq,
    bool remove_hash)
{
	/*
	 * Remove the flow queue if it is empty
	 * and delete it
	 */
	STAILQ_REMOVE(&fq_cl->fcl_old_flows, fq, flowq,
	    fq_actlink);
	fq->fq_flags &= ~FQF_OLD_FLOW;
	fq_cl->fcl_stat.fcl_oldflows_cnt--;
	VERIFY(fq->fq_bytes == 0);

	if (remove_hash) {
		/* Remove from the hash list */
		fq_if_destroy_flow(fqs, fq_cl, fq);
	}
}