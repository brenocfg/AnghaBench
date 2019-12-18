#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfa_fcs_rport_s {int pwwn; int pid; int old_pid; TYPE_2__* fcs; int /*<<< orphan*/  fcxp; int /*<<< orphan*/  ns_retries; TYPE_3__* port; int /*<<< orphan*/  timer; int /*<<< orphan*/  plogi_retries; int /*<<< orphan*/  prlo; } ;
typedef  enum rport_event { ____Placeholder_rport_event } rport_event ;
struct TYPE_7__ {TYPE_1__* fcs; } ;
struct TYPE_6__ {int /*<<< orphan*/  bfa; } ;
struct TYPE_5__ {int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
 int BFA_FCS_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  BFA_FCS_RPORT_MAX_RETRIES ; 
 int /*<<< orphan*/  BFA_PORT_TOPOLOGY_LOOP ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int FC_RA_TOV ; 
#define  RPSM_EVENT_ACCEPTED 140 
#define  RPSM_EVENT_ADDRESS_CHANGE 139 
#define  RPSM_EVENT_DELETE 138 
#define  RPSM_EVENT_FAB_SCN 137 
#define  RPSM_EVENT_FAILED 136 
#define  RPSM_EVENT_LOGO_IMP 135 
#define  RPSM_EVENT_LOGO_RCVD 134 
#define  RPSM_EVENT_PLOGI_COMP 133 
#define  RPSM_EVENT_PLOGI_RCVD 132 
#define  RPSM_EVENT_PLOGI_RETRY 131 
#define  RPSM_EVENT_PRLO_RCVD 130 
#define  RPSM_EVENT_SCN_OFFLINE 129 
#define  RPSM_EVENT_SCN_ONLINE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_fcport_get_topology (int /*<<< orphan*/ ) ; 
 int bfa_fcs_rport_del_timeout ; 
 int /*<<< orphan*/  bfa_fcs_rport_fcs_online_action (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_free (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_send_logo_acc (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_send_nsdisc (struct bfa_fcs_rport_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_rport_send_plogiacc (struct bfa_fcs_rport_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_rport_send_prlo_acc (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_fc4_fcs_online ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_nsdisc_sending ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_offline ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_plogi_retry ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_plogiacc_sending ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_uninit ; 
 int /*<<< orphan*/  bfa_fcs_rport_timeout ; 
 int /*<<< orphan*/  bfa_fcxp_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_fcs_rport_s*,int) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  rport_del_max_plogi_retry ; 

__attribute__((used)) static void
bfa_fcs_rport_sm_plogi(struct bfa_fcs_rport_s *rport, enum rport_event event)
{
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	switch (event) {
	case RPSM_EVENT_ACCEPTED:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_fcs_online);
		rport->plogi_retries = 0;
		bfa_fcs_rport_fcs_online_action(rport);
		break;

	case RPSM_EVENT_LOGO_RCVD:
		bfa_fcs_rport_send_logo_acc(rport);
		/*
		 * !! fall through !!
		 */
	case RPSM_EVENT_PRLO_RCVD:
		if (rport->prlo == BFA_TRUE)
			bfa_fcs_rport_send_prlo_acc(rport);

		bfa_fcxp_discard(rport->fcxp);
		/*
		 * !! fall through !!
		 */
	case RPSM_EVENT_FAILED:
		if (rport->plogi_retries < BFA_FCS_RPORT_MAX_RETRIES) {
			rport->plogi_retries++;
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogi_retry);
			bfa_timer_start(rport->fcs->bfa, &rport->timer,
					bfa_fcs_rport_timeout, rport,
					BFA_FCS_RETRY_TIMEOUT);
		} else {
			bfa_stats(rport->port, rport_del_max_plogi_retry);
			rport->old_pid = rport->pid;
			rport->pid = 0;
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
			bfa_timer_start(rport->fcs->bfa, &rport->timer,
					bfa_fcs_rport_timeout, rport,
					bfa_fcs_rport_del_timeout);
		}
		break;

	case RPSM_EVENT_SCN_ONLINE:
		break;

	case RPSM_EVENT_SCN_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_fcxp_discard(rport->fcxp);
		bfa_timer_start(rport->fcs->bfa, &rport->timer,
				bfa_fcs_rport_timeout, rport,
				bfa_fcs_rport_del_timeout);
		break;

	case RPSM_EVENT_PLOGI_RETRY:
		rport->plogi_retries = 0;
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogi_retry);
		bfa_timer_start(rport->fcs->bfa, &rport->timer,
				bfa_fcs_rport_timeout, rport,
				(FC_RA_TOV * 1000));
		break;

	case RPSM_EVENT_LOGO_IMP:
		rport->pid = 0;
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_offline);
		bfa_fcxp_discard(rport->fcxp);
		bfa_timer_start(rport->fcs->bfa, &rport->timer,
				bfa_fcs_rport_timeout, rport,
				bfa_fcs_rport_del_timeout);
		break;

	case RPSM_EVENT_ADDRESS_CHANGE:
	case RPSM_EVENT_FAB_SCN:
		bfa_fcxp_discard(rport->fcxp);
		WARN_ON(!(bfa_fcport_get_topology(rport->port->fcs->bfa) !=
					BFA_PORT_TOPOLOGY_LOOP));
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_nsdisc_sending);
		rport->ns_retries = 0;
		bfa_fcs_rport_send_nsdisc(rport, NULL);
		break;

	case RPSM_EVENT_PLOGI_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_plogiacc_sending);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_send_plogiacc(rport, NULL);
		break;

	case RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_free(rport);
		break;

	case RPSM_EVENT_PLOGI_COMP:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_fcs_online);
		bfa_fcxp_discard(rport->fcxp);
		bfa_fcs_rport_fcs_online_action(rport);
		break;

	default:
		bfa_sm_fault(rport->fcs, event);
	}
}