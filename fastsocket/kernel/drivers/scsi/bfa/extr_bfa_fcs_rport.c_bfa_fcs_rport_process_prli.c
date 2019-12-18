#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct fchs_s {int /*<<< orphan*/  ox_id; int /*<<< orphan*/  s_id; int /*<<< orphan*/  d_id; } ;
struct TYPE_7__ {scalar_t__ target; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; TYPE_2__ servparams; } ;
struct fc_prli_s {TYPE_3__ parampage; } ;
struct bfa_fcxp_s {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  prli_rcvd; } ;
struct bfa_fcs_rport_s {int /*<<< orphan*/  itnim; int /*<<< orphan*/  scsi_function; int /*<<< orphan*/  fcs; TYPE_1__ stats; struct bfa_fcs_lport_s* port; } ;
struct TYPE_9__ {int /*<<< orphan*/  roles; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  lp_tag; TYPE_5__* fabric; TYPE_4__ port_cfg; int /*<<< orphan*/  fcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_RPORT_INITIATOR ; 
 int /*<<< orphan*/  BFA_RPORT_TARGET ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  FC_MAX_PDUSZ ; 
 struct bfa_fcxp_s* bfa_fcs_fcxp_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_is_initiator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_fcid (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_get_reqbuf (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_send (struct bfa_fcxp_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fchs_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_prli_acc_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_rport_process_prli(struct bfa_fcs_rport_s *rport,
			struct fchs_s *rx_fchs, u16 len)
{
	struct bfa_fcxp_s *fcxp;
	struct fchs_s	fchs;
	struct bfa_fcs_lport_s *port = rport->port;
	struct fc_prli_s	*prli;

	bfa_trc(port->fcs, rx_fchs->s_id);
	bfa_trc(port->fcs, rx_fchs->d_id);

	rport->stats.prli_rcvd++;

	/*
	 * We are in Initiator Mode
	 */
	prli = (struct fc_prli_s *) (rx_fchs + 1);

	if (prli->parampage.servparams.target) {
		/*
		 * PRLI from a target ?
		 * Send the Acc.
		 * PRLI sent by us will be used to transition the IT nexus,
		 * once the response is received from the target.
		 */
		bfa_trc(port->fcs, rx_fchs->s_id);
		rport->scsi_function = BFA_RPORT_TARGET;
	} else {
		bfa_trc(rport->fcs, prli->parampage.type);
		rport->scsi_function = BFA_RPORT_INITIATOR;
		bfa_fcs_itnim_is_initiator(rport->itnim);
	}

	fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	if (!fcxp)
		return;

	len = fc_prli_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				rx_fchs->s_id, bfa_fcs_lport_get_fcid(port),
				rx_fchs->ox_id, port->port_cfg.roles);

	bfa_fcxp_send(fcxp, NULL, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			FC_CLASS_3, len, &fchs, NULL, NULL, FC_MAX_PDUSZ, 0);
}