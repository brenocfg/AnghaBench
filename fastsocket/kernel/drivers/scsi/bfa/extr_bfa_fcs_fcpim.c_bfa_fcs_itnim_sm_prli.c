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
struct bfa_fcs_itnim_s {TYPE_1__* fcs; int /*<<< orphan*/  fcxp; TYPE_2__* rport; int /*<<< orphan*/  timer; } ;
typedef  enum bfa_fcs_itnim_event { ____Placeholder_bfa_fcs_itnim_event } bfa_fcs_itnim_event ;
struct TYPE_5__ {int pwwn; int /*<<< orphan*/  scsi_function; } ;
struct TYPE_4__ {int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
#define  BFA_FCS_ITNIM_SM_DELETE 133 
#define  BFA_FCS_ITNIM_SM_INITIATOR 132 
#define  BFA_FCS_ITNIM_SM_OFFLINE 131 
#define  BFA_FCS_ITNIM_SM_RSP_ERROR 130 
#define  BFA_FCS_ITNIM_SM_RSP_NOT_SUPP 129 
#define  BFA_FCS_ITNIM_SM_RSP_OK 128 
 int /*<<< orphan*/  BFA_FCS_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  BFA_RPORT_INITIATOR ; 
 int /*<<< orphan*/  RPSM_EVENT_FC4_FCS_ONLINE ; 
 int /*<<< orphan*/  RPSM_EVENT_FC4_OFFLINE ; 
 int /*<<< orphan*/  bfa_fcs_itnim_free (struct bfa_fcs_itnim_s*) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_sm_hal_rport_online ; 
 int /*<<< orphan*/  bfa_fcs_itnim_sm_initiator ; 
 int /*<<< orphan*/  bfa_fcs_itnim_sm_offline ; 
 int /*<<< orphan*/  bfa_fcs_itnim_sm_prli_retry ; 
 int /*<<< orphan*/  bfa_fcs_itnim_timeout ; 
 int /*<<< orphan*/  bfa_fcxp_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfa_sm_send_event (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_fcs_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int) ; 

__attribute__((used)) static void
bfa_fcs_itnim_sm_prli(struct bfa_fcs_itnim_s *itnim,
		 enum bfa_fcs_itnim_event event)
{
	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_trc(itnim->fcs, event);

	switch (event) {
	case BFA_FCS_ITNIM_SM_RSP_OK:
		if (itnim->rport->scsi_function == BFA_RPORT_INITIATOR)
			bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_initiator);
		else
			bfa_sm_set_state(itnim,
				bfa_fcs_itnim_sm_hal_rport_online);

		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_FCS_ONLINE);
		break;

	case BFA_FCS_ITNIM_SM_RSP_ERROR:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_prli_retry);
		bfa_timer_start(itnim->fcs->bfa, &itnim->timer,
				bfa_fcs_itnim_timeout, itnim,
				BFA_FCS_RETRY_TIMEOUT);
		break;

	case BFA_FCS_ITNIM_SM_RSP_NOT_SUPP:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		break;

	case BFA_FCS_ITNIM_SM_OFFLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_fcxp_discard(itnim->fcxp);
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_OFFLINE);
		break;

	case BFA_FCS_ITNIM_SM_INITIATOR:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_initiator);
		bfa_fcxp_discard(itnim->fcxp);
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_FCS_ONLINE);
		break;

	case BFA_FCS_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_fcxp_discard(itnim->fcxp);
		bfa_fcs_itnim_free(itnim);
		break;

	default:
		bfa_sm_fault(itnim->fcs, event);
	}
}