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
typedef  scalar_t__ u16 ;
struct bfi_tskim_rsp_s {scalar_t__ tsk_status; int /*<<< orphan*/  tsk_tag; } ;
struct bfi_msg_s {int dummy; } ;
struct bfa_tskim_s {scalar_t__ tsk_tag; scalar_t__ tsk_status; int /*<<< orphan*/  itnim; } ;
struct bfa_s {int dummy; } ;
struct bfa_fcpim_s {int dummy; } ;

/* Variables and functions */
 struct bfa_fcpim_s* BFA_FCPIM (struct bfa_s*) ; 
 struct bfa_tskim_s* BFA_TSKIM_FROM_TAG (struct bfa_fcpim_s*,scalar_t__) ; 
 int /*<<< orphan*/  BFA_TSKIM_SM_CLEANUP_DONE ; 
 int /*<<< orphan*/  BFA_TSKIM_SM_DONE ; 
 int /*<<< orphan*/  BFA_TSKIM_SM_UTAG ; 
 scalar_t__ BFI_TSKIM_STS_ABORTED ; 
 scalar_t__ BFI_TSKIM_STS_UTAG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_tskim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tm_cleanup_comps ; 
 int /*<<< orphan*/  tm_fw_rsps ; 

void
bfa_tskim_isr(struct bfa_s *bfa, struct bfi_msg_s *m)
{
	struct bfa_fcpim_s *fcpim = BFA_FCPIM(bfa);
	struct bfi_tskim_rsp_s *rsp = (struct bfi_tskim_rsp_s *) m;
	struct bfa_tskim_s *tskim;
	u16	tsk_tag = be16_to_cpu(rsp->tsk_tag);

	tskim = BFA_TSKIM_FROM_TAG(fcpim, tsk_tag);
	WARN_ON(tskim->tsk_tag != tsk_tag);

	tskim->tsk_status = rsp->tsk_status;

	/*
	 * Firmware sends BFI_TSKIM_STS_ABORTED status for abort
	 * requests. All other statuses are for normal completions.
	 */
	if (rsp->tsk_status == BFI_TSKIM_STS_ABORTED) {
		bfa_stats(tskim->itnim, tm_cleanup_comps);
		bfa_sm_send_event(tskim, BFA_TSKIM_SM_CLEANUP_DONE);
	} else if (rsp->tsk_status == BFI_TSKIM_STS_UTAG) {
		bfa_sm_send_event(tskim, BFA_TSKIM_SM_UTAG);
	} else {
		bfa_stats(tskim->itnim, tm_fw_rsps);
		bfa_sm_send_event(tskim, BFA_TSKIM_SM_DONE);
	}
}