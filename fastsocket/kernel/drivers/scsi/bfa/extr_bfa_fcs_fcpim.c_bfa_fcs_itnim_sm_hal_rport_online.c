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
struct bfa_fcs_itnim_s {TYPE_1__* fcs; TYPE_2__* rport; int /*<<< orphan*/  seq_rec; int /*<<< orphan*/  bfa_itnim; } ;
typedef  enum bfa_fcs_itnim_event { ____Placeholder_bfa_fcs_itnim_event } bfa_fcs_itnim_event ;
struct TYPE_5__ {int pwwn; int /*<<< orphan*/  bfa_rport; } ;
struct TYPE_4__ {int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
#define  BFA_FCS_ITNIM_SM_DELETE 130 
#define  BFA_FCS_ITNIM_SM_HAL_ONLINE 129 
#define  BFA_FCS_ITNIM_SM_OFFLINE 128 
 int /*<<< orphan*/  RPSM_EVENT_DELETE ; 
 int /*<<< orphan*/  RPSM_EVENT_FC4_OFFLINE ; 
 int /*<<< orphan*/  bfa_fcs_itnim_free (struct bfa_fcs_itnim_s*) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_sm_hcb_online ; 
 int /*<<< orphan*/  bfa_fcs_itnim_sm_offline ; 
 int /*<<< orphan*/  bfa_itnim_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfa_fcs_itnim_s*) ; 
 int /*<<< orphan*/  bfa_itnim_online (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfa_sm_send_event (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int) ; 

__attribute__((used)) static void
bfa_fcs_itnim_sm_hal_rport_online(struct bfa_fcs_itnim_s *itnim,
				enum bfa_fcs_itnim_event event)
{
	bfa_trc(itnim->fcs, itnim->rport->pwwn);
	bfa_trc(itnim->fcs, event);

	switch (event) {
	case BFA_FCS_ITNIM_SM_HAL_ONLINE:
		if (!itnim->bfa_itnim)
			itnim->bfa_itnim = bfa_itnim_create(itnim->fcs->bfa,
					itnim->rport->bfa_rport, itnim);

		if (itnim->bfa_itnim) {
			bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_hcb_online);
			bfa_itnim_online(itnim->bfa_itnim, itnim->seq_rec);
		} else {
			bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
			bfa_sm_send_event(itnim->rport, RPSM_EVENT_DELETE);
		}

		break;

	case BFA_FCS_ITNIM_SM_OFFLINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_sm_send_event(itnim->rport, RPSM_EVENT_FC4_OFFLINE);
		break;

	case BFA_FCS_ITNIM_SM_DELETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);
		bfa_fcs_itnim_free(itnim);
		break;

	default:
		bfa_sm_fault(itnim->fcs, event);
	}
}