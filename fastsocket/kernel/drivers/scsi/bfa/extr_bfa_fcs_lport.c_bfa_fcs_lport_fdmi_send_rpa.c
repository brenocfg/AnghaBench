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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct fchs_s {int dummy; } ;
struct ct_hdr_s {int dummy; } ;
struct bfa_fcxp_s {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  pwwn; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  lp_tag; TYPE_3__* fabric; TYPE_4__* fcs; TYPE_2__ port_cfg; } ;
struct bfa_fcs_lport_fdmi_s {struct bfa_fcxp_s* fcxp; int /*<<< orphan*/  fcxp_wqe; TYPE_1__* ms; } ;
struct TYPE_9__ {int /*<<< orphan*/  bfa; } ;
struct TYPE_8__ {int /*<<< orphan*/  vf_id; } ;
struct TYPE_6__ {struct bfa_fcs_lport_s* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  FC_FCCT_TOV ; 
 int /*<<< orphan*/  FC_MAX_PDUSZ ; 
 int /*<<< orphan*/  FDMISM_EVENT_RPA_SENT ; 
 int /*<<< orphan*/  FDMI_RPA ; 
 struct bfa_fcxp_s* bfa_fcs_fcxp_alloc (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_fcxp_alloc_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void (*) (void*,struct bfa_fcxp_s*),struct bfa_fcs_lport_fdmi_s*,int /*<<< orphan*/ ) ; 
 scalar_t__ bfa_fcs_lport_fdmi_build_rpa_pyld (struct bfa_fcs_lport_fdmi_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_lport_fdmi_rpa_response ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_fcid (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/ * bfa_fcxp_get_reqbuf (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_send (struct bfa_fcxp_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct fchs_s*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_lport_fdmi_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ fc_fdmi_reqhdr_build (struct fchs_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_lport_fdmi_send_rpa(void *fdmi_cbarg, struct bfa_fcxp_s *fcxp_alloced)
{
	struct bfa_fcs_lport_fdmi_s *fdmi = fdmi_cbarg;
	struct bfa_fcs_lport_s *port = fdmi->ms->port;
	struct fchs_s fchs;
	u16        len, attr_len;
	struct bfa_fcxp_s *fcxp;
	u8        *pyld;

	bfa_trc(port->fcs, port->port_cfg.pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	if (!fcxp) {
		bfa_fcs_fcxp_alloc_wait(port->fcs->bfa, &fdmi->fcxp_wqe,
				bfa_fcs_lport_fdmi_send_rpa, fdmi, BFA_TRUE);
		return;
	}
	fdmi->fcxp = fcxp;

	pyld = bfa_fcxp_get_reqbuf(fcxp);
	memset(pyld, 0, FC_MAX_PDUSZ);

	len = fc_fdmi_reqhdr_build(&fchs, pyld, bfa_fcs_lport_get_fcid(port),
				   FDMI_RPA);

	attr_len = bfa_fcs_lport_fdmi_build_rpa_pyld(fdmi,
				(u8 *) ((struct ct_hdr_s *) pyld + 1));

	bfa_fcxp_send(fcxp, NULL, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len + attr_len, &fchs,
			  bfa_fcs_lport_fdmi_rpa_response, (void *)fdmi,
			  FC_MAX_PDUSZ, FC_FCCT_TOV);

	bfa_sm_send_event(fdmi, FDMISM_EVENT_RPA_SENT);
}