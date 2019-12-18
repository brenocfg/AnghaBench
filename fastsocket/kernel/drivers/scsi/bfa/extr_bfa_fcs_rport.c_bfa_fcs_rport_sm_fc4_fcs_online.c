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
struct bfa_fcs_rport_s {int pwwn; int pid; TYPE_1__* fcs; int /*<<< orphan*/  plogi_pending; int /*<<< orphan*/  bfa_rport; int /*<<< orphan*/  scsi_function; } ;
typedef  enum rport_event { ____Placeholder_rport_event } rport_event ;
struct TYPE_3__ {int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_PID_IS_WKA (int) ; 
 int /*<<< orphan*/  BFA_RPORT_INITIATOR ; 
 int /*<<< orphan*/  BFA_TRUE ; 
#define  RPSM_EVENT_ADDRESS_CHANGE 137 
#define  RPSM_EVENT_DELETE 136 
#define  RPSM_EVENT_FAB_SCN 135 
#define  RPSM_EVENT_FC4_FCS_ONLINE 134 
#define  RPSM_EVENT_LOGO_IMP 133 
#define  RPSM_EVENT_LOGO_RCVD 132 
#define  RPSM_EVENT_PLOGI_COMP 131 
#define  RPSM_EVENT_PLOGI_RCVD 130 
#define  RPSM_EVENT_PRLO_RCVD 129 
#define  RPSM_EVENT_SCN_OFFLINE 128 
 int /*<<< orphan*/  bfa_fcs_rpf_rport_online (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_fcs_offline_action (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_hal_online (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_fc4_logorcv ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_fc4_logosend ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_fc4_offline ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_hal_online ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_online ; 
 int /*<<< orphan*/  bfa_rport_create (int /*<<< orphan*/ ,struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int) ; 

__attribute__((used)) static void
bfa_fcs_rport_sm_fc4_fcs_online(struct bfa_fcs_rport_s *rport,
				enum rport_event event)
{
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	switch (event) {
	case RPSM_EVENT_FC4_FCS_ONLINE:
		if (rport->scsi_function == BFA_RPORT_INITIATOR) {
			if (!BFA_FCS_PID_IS_WKA(rport->pid))
				bfa_fcs_rpf_rport_online(rport);
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_online);
			break;
		}

		if (!rport->bfa_rport)
			rport->bfa_rport =
				bfa_rport_create(rport->fcs->bfa, rport);

		if (rport->bfa_rport) {
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_hal_online);
			bfa_fcs_rport_hal_online(rport);
		} else {
			bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
			bfa_fcs_rport_fcs_offline_action(rport);
		}
		break;

	case RPSM_EVENT_PLOGI_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		rport->plogi_pending = BFA_TRUE;
		bfa_fcs_rport_fcs_offline_action(rport);
		break;

	case RPSM_EVENT_PLOGI_COMP:
	case RPSM_EVENT_LOGO_IMP:
	case RPSM_EVENT_ADDRESS_CHANGE:
	case RPSM_EVENT_FAB_SCN:
	case RPSM_EVENT_SCN_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_offline);
		bfa_fcs_rport_fcs_offline_action(rport);
		break;

	case RPSM_EVENT_LOGO_RCVD:
	case RPSM_EVENT_PRLO_RCVD:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logorcv);
		bfa_fcs_rport_fcs_offline_action(rport);
		break;

	case RPSM_EVENT_DELETE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_fc4_logosend);
		bfa_fcs_rport_fcs_offline_action(rport);
		break;

	default:
		bfa_sm_fault(rport->fcs, event);
		break;
	}
}