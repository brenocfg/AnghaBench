#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fchs_s {int dummy; } ;
struct bfa_fcxp_s {int dummy; } ;
struct bfa_fcs_rport_s {int /*<<< orphan*/  bfa_rport; int /*<<< orphan*/  pid; int /*<<< orphan*/  pwwn; struct bfa_fcs_lport_s* port; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  lp_tag; TYPE_1__* fabric; TYPE_3__* fcs; } ;
struct TYPE_5__ {int /*<<< orphan*/  prli_sent; int /*<<< orphan*/  fcxp_alloc_wait; } ;
struct bfa_fcs_itnim_s {TYPE_2__ stats; struct bfa_fcs_rport_s* rport; struct bfa_fcxp_s* fcxp; int /*<<< orphan*/  fcxp_wqe; int /*<<< orphan*/  fcs; } ;
struct TYPE_6__ {int /*<<< orphan*/  bfa; } ;
struct TYPE_4__ {int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_FCS_ITNIM_SM_FRMSENT ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  FC_ELS_TOV ; 
 int /*<<< orphan*/  FC_MAX_PDUSZ ; 
 struct bfa_fcxp_s* bfa_fcs_fcxp_alloc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_fcxp_alloc_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void (*) (void*,struct bfa_fcxp_s*),struct bfa_fcs_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_prli_response ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_fcid (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_get_reqbuf (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_send (struct bfa_fcxp_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct fchs_s*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fc_prli_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_itnim_send_prli(void *itnim_cbarg, struct bfa_fcxp_s *fcxp_alloced)
{
	struct bfa_fcs_itnim_s *itnim = itnim_cbarg;
	struct bfa_fcs_rport_s *rport = itnim->rport;
	struct bfa_fcs_lport_s *port = rport->port;
	struct fchs_s	fchs;
	struct bfa_fcxp_s *fcxp;
	int		len;

	bfa_trc(itnim->fcs, itnim->rport->pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	if (!fcxp) {
		itnim->stats.fcxp_alloc_wait++;
		bfa_fcs_fcxp_alloc_wait(port->fcs->bfa, &itnim->fcxp_wqe,
				bfa_fcs_itnim_send_prli, itnim, BFA_TRUE);
		return;
	}
	itnim->fcxp = fcxp;

	len = fc_prli_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			    itnim->rport->pid, bfa_fcs_lport_get_fcid(port), 0);

	bfa_fcxp_send(fcxp, rport->bfa_rport, port->fabric->vf_id, port->lp_tag,
		      BFA_FALSE, FC_CLASS_3, len, &fchs,
		      bfa_fcs_itnim_prli_response, (void *)itnim,
		      FC_MAX_PDUSZ, FC_ELS_TOV);

	itnim->stats.prli_sent++;
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_FRMSENT);
}