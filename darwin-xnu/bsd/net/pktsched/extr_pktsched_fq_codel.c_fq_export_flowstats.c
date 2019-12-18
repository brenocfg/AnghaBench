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
struct fq_codel_flowstats {int /*<<< orphan*/  fqst_flags; int /*<<< orphan*/  fqst_flowhash; int /*<<< orphan*/  fqst_bytes; int /*<<< orphan*/  fqst_min_qdelay; } ;
struct TYPE_5__ {int fq_flags; int /*<<< orphan*/  fq_flowhash; int /*<<< orphan*/  fq_bytes; int /*<<< orphan*/  fq_min_qdelay; } ;
typedef  TYPE_1__ fq_t ;
struct TYPE_6__ {TYPE_1__* fqs_large_flow; } ;
typedef  TYPE_2__ fq_if_t ;

/* Variables and functions */
 int FQF_DELAY_HIGH ; 
 int FQF_FLOWCTL_ON ; 
 int FQF_NEW_FLOW ; 
 int FQF_OLD_FLOW ; 
 int /*<<< orphan*/  FQ_FLOWSTATS_DELAY_HIGH ; 
 int /*<<< orphan*/  FQ_FLOWSTATS_FLOWCTL_ON ; 
 int /*<<< orphan*/  FQ_FLOWSTATS_LARGE_FLOW ; 
 int /*<<< orphan*/  FQ_FLOWSTATS_NEW_FLOW ; 
 int /*<<< orphan*/  FQ_FLOWSTATS_OLD_FLOW ; 
 int /*<<< orphan*/  bzero (struct fq_codel_flowstats*,int) ; 

__attribute__((used)) static void
fq_export_flowstats(fq_if_t *fqs, fq_t *fq,
    struct fq_codel_flowstats *flowstat)
{
	bzero(flowstat, sizeof (*flowstat));
	flowstat->fqst_min_qdelay = fq->fq_min_qdelay;
	flowstat->fqst_bytes = fq->fq_bytes;
	flowstat->fqst_flowhash = fq->fq_flowhash;
	if (fq->fq_flags & FQF_NEW_FLOW)
		flowstat->fqst_flags |= FQ_FLOWSTATS_NEW_FLOW;
	if (fq->fq_flags & FQF_OLD_FLOW)
		flowstat->fqst_flags |= FQ_FLOWSTATS_OLD_FLOW;
	if (fq->fq_flags & FQF_DELAY_HIGH)
		flowstat->fqst_flags |= FQ_FLOWSTATS_DELAY_HIGH;
	if (fq->fq_flags & FQF_FLOWCTL_ON)
		flowstat->fqst_flags |= FQ_FLOWSTATS_FLOWCTL_ON;
	if (fqs->fqs_large_flow == fq)
		flowstat->fqst_flags |= FQ_FLOWSTATS_LARGE_FLOW;
}