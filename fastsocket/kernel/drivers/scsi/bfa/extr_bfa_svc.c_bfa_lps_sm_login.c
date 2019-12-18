#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfa_lps_s {int bfa_tag; int fport; int lp_pid; TYPE_1__* bfa; int /*<<< orphan*/  fdisc; int /*<<< orphan*/  status; } ;
typedef  enum bfa_lps_event { ____Placeholder_bfa_lps_event } bfa_lps_event ;
struct TYPE_3__ {int /*<<< orphan*/  plog; } ;

/* Variables and functions */
#define  BFA_LPS_SM_DELETE 131 
#define  BFA_LPS_SM_FWRSP 130 
#define  BFA_LPS_SM_OFFLINE 129 
#define  BFA_LPS_SM_SET_N2N_PID 128 
 int /*<<< orphan*/  BFA_PL_EID_LOGIN ; 
 int /*<<< orphan*/  BFA_PL_MID_LPS ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_lps_login_comp (struct bfa_lps_s*) ; 
 int /*<<< orphan*/  bfa_lps_sm_init ; 
 int /*<<< orphan*/  bfa_lps_sm_online ; 
 int /*<<< orphan*/  bfa_plog_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_lps_s*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_lps_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int) ; 

__attribute__((used)) static void
bfa_lps_sm_login(struct bfa_lps_s *lps, enum bfa_lps_event event)
{
	bfa_trc(lps->bfa, lps->bfa_tag);
	bfa_trc(lps->bfa, event);

	switch (event) {
	case BFA_LPS_SM_FWRSP:
		if (lps->status == BFA_STATUS_OK) {
			bfa_sm_set_state(lps, bfa_lps_sm_online);
			if (lps->fdisc)
				bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
					BFA_PL_EID_LOGIN, 0, "FDISC Accept");
			else
				bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
					BFA_PL_EID_LOGIN, 0, "FLOGI Accept");
			/* If N2N, send the assigned PID to FW */
			bfa_trc(lps->bfa, lps->fport);
			bfa_trc(lps->bfa, lps->lp_pid);

			if (!lps->fport && lps->lp_pid)
				bfa_sm_send_event(lps, BFA_LPS_SM_SET_N2N_PID);
		} else {
			bfa_sm_set_state(lps, bfa_lps_sm_init);
			if (lps->fdisc)
				bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
					BFA_PL_EID_LOGIN, 0,
					"FDISC Fail (RJT or timeout)");
			else
				bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
					BFA_PL_EID_LOGIN, 0,
					"FLOGI Fail (RJT or timeout)");
		}
		bfa_lps_login_comp(lps);
		break;

	case BFA_LPS_SM_OFFLINE:
	case BFA_LPS_SM_DELETE:
		bfa_sm_set_state(lps, bfa_lps_sm_init);
		break;

	case BFA_LPS_SM_SET_N2N_PID:
		bfa_trc(lps->bfa, lps->fport);
		bfa_trc(lps->bfa, lps->lp_pid);
		break;

	default:
		bfa_sm_fault(lps->bfa, event);
	}
}