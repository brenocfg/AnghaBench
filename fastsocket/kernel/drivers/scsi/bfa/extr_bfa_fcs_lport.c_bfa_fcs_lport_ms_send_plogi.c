#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct fchs_s {int dummy; } ;
struct bfa_fcxp_s {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  ms_plogi_sent; int /*<<< orphan*/  ms_plogi_alloc_wait; } ;
struct TYPE_6__ {int /*<<< orphan*/  nwwn; int /*<<< orphan*/  pwwn; } ;
struct bfa_fcs_lport_s {TYPE_3__ stats; int /*<<< orphan*/  lp_tag; TYPE_2__* fabric; TYPE_4__* fcs; TYPE_1__ port_cfg; int /*<<< orphan*/  pid; } ;
struct bfa_fcs_lport_ms_s {struct bfa_fcxp_s* fcxp; int /*<<< orphan*/  fcxp_wqe; struct bfa_fcs_lport_s* port; } ;
struct TYPE_9__ {int /*<<< orphan*/  bfa; } ;
struct TYPE_7__ {int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  FC_ELS_TOV ; 
 int /*<<< orphan*/  FC_MAX_PDUSZ ; 
 int /*<<< orphan*/  FC_MGMT_SERVER ; 
 int /*<<< orphan*/  MSSM_EVENT_FCXP_SENT ; 
 int /*<<< orphan*/  bfa_fcport_get_maxfrsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcport_get_rx_bbcredit (int /*<<< orphan*/ ) ; 
 struct bfa_fcxp_s* bfa_fcs_fcxp_alloc (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_fcxp_alloc_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void (*) (void*,struct bfa_fcxp_s*),struct bfa_fcs_lport_ms_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_fcid (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_lport_ms_plogi_response ; 
 int /*<<< orphan*/  bfa_fcxp_get_reqbuf (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_send (struct bfa_fcxp_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct fchs_s*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_hton3b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_lport_ms_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int fc_plogi_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_lport_ms_send_plogi(void *ms_cbarg, struct bfa_fcxp_s *fcxp_alloced)
{
	struct bfa_fcs_lport_ms_s *ms = ms_cbarg;
	struct bfa_fcs_lport_s *port = ms->port;
	struct fchs_s	fchs;
	int	len;
	struct bfa_fcxp_s *fcxp;

	bfa_trc(port->fcs, port->pid);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	if (!fcxp) {
		port->stats.ms_plogi_alloc_wait++;
		bfa_fcs_fcxp_alloc_wait(port->fcs->bfa, &ms->fcxp_wqe,
				bfa_fcs_lport_ms_send_plogi, ms, BFA_TRUE);
		return;
	}
	ms->fcxp = fcxp;

	len = fc_plogi_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
			     bfa_hton3b(FC_MGMT_SERVER),
			     bfa_fcs_lport_get_fcid(port), 0,
			     port->port_cfg.pwwn, port->port_cfg.nwwn,
			     bfa_fcport_get_maxfrsize(port->fcs->bfa),
			     bfa_fcport_get_rx_bbcredit(port->fcs->bfa));

	bfa_fcxp_send(fcxp, NULL, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_ms_plogi_response, (void *)ms,
			  FC_MAX_PDUSZ, FC_ELS_TOV);

	port->stats.ms_plogi_sent++;
	bfa_sm_send_event(ms, MSSM_EVENT_FCXP_SENT);
}