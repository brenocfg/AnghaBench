#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct fchs_s {int dummy; } ;
struct bfa_fcxp_s {int dummy; } ;
struct bfa_fcs_lport_ms_s {struct bfa_fcxp_s* fcxp; int /*<<< orphan*/  fcxp_wqe; TYPE_3__* port; } ;
struct TYPE_9__ {int /*<<< orphan*/  lp_tag; TYPE_2__* fabric; TYPE_4__* fcs; int /*<<< orphan*/  pid; } ;
typedef  TYPE_3__ bfa_fcs_lport_t ;
struct TYPE_10__ {int /*<<< orphan*/  bfa; } ;
struct TYPE_8__ {int /*<<< orphan*/  vf_id; TYPE_1__* lps; } ;
struct TYPE_7__ {int /*<<< orphan*/  pr_nwwn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  FC_FCCT_TOV ; 
 int /*<<< orphan*/  FC_MAX_PDUSZ ; 
 int /*<<< orphan*/  MSSM_EVENT_FCXP_SENT ; 
 struct bfa_fcxp_s* bfa_fcs_fcxp_alloc (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_fcxp_alloc_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void (*) (void*,struct bfa_fcxp_s*),struct bfa_fcs_lport_ms_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_fcid (TYPE_3__*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_ms_gfn_response ; 
 int /*<<< orphan*/  bfa_fcxp_get_reqbuf (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_send (struct bfa_fcxp_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct fchs_s*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_lport_ms_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int fc_gfn_req_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_lport_ms_send_gfn(void *ms_cbarg, struct bfa_fcxp_s *fcxp_alloced)
{
	struct bfa_fcs_lport_ms_s *ms = ms_cbarg;
	bfa_fcs_lport_t *port = ms->port;
	struct fchs_s		fchs;
	int			len;
	struct bfa_fcxp_s *fcxp;

	bfa_trc(port->fcs, port->pid);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	if (!fcxp) {
		bfa_fcs_fcxp_alloc_wait(port->fcs->bfa, &ms->fcxp_wqe,
				bfa_fcs_lport_ms_send_gfn, ms, BFA_TRUE);
		return;
	}
	ms->fcxp = fcxp;

	len = fc_gfn_req_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			     bfa_fcs_lport_get_fcid(port),
				 port->fabric->lps->pr_nwwn);

	bfa_fcxp_send(fcxp, NULL, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_ms_gfn_response, (void *)ms,
			  FC_MAX_PDUSZ, FC_FCCT_TOV);

	bfa_sm_send_event(ms, MSSM_EVENT_FCXP_SENT);
}