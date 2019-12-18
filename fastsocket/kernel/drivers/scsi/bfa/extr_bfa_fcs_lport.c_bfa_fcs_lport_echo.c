#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct fchs_s {int s_id; int d_id; int /*<<< orphan*/  ox_id; } ;
struct fc_echo_s {int dummy; } ;
struct bfa_rport_s {int dummy; } ;
struct bfa_fcxp_s {int dummy; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  lp_tag; TYPE_1__* fabric; int /*<<< orphan*/  fcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  FC_MAX_PDUSZ ; 
 struct bfa_fcxp_s* bfa_fcs_fcxp_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_fcid (struct bfa_fcs_lport_s*) ; 
 scalar_t__ bfa_fcxp_get_reqbuf (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_send (struct bfa_fcxp_s*,struct bfa_rport_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct fchs_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 
 int fc_ls_acc_build (struct fchs_s*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct fc_echo_s*,int) ; 

__attribute__((used)) static void
bfa_fcs_lport_echo(struct bfa_fcs_lport_s *port, struct fchs_s *rx_fchs,
		struct fc_echo_s *echo, u16 rx_len)
{
	struct fchs_s		fchs;
	struct bfa_fcxp_s	*fcxp;
	struct bfa_rport_s	*bfa_rport = NULL;
	int			len, pyld_len;

	bfa_trc(port->fcs, rx_fchs->s_id);
	bfa_trc(port->fcs, rx_fchs->d_id);

	fcxp = bfa_fcs_fcxp_alloc(port->fcs, BFA_FALSE);
	if (!fcxp)
		return;

	len = fc_ls_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				rx_fchs->s_id, bfa_fcs_lport_get_fcid(port),
				rx_fchs->ox_id);

	/*
	 * Copy the payload (if any) from the echo frame
	 */
	pyld_len = rx_len - sizeof(struct fchs_s);
	bfa_trc(port->fcs, rx_len);
	bfa_trc(port->fcs, pyld_len);

	if (pyld_len > len)
		memcpy(((u8 *) bfa_fcxp_get_reqbuf(fcxp)) +
			sizeof(struct fc_echo_s), (echo + 1),
			(pyld_len - sizeof(struct fc_echo_s)));

	bfa_fcxp_send(fcxp, bfa_rport, port->fabric->vf_id, port->lp_tag,
			BFA_FALSE, FC_CLASS_3, pyld_len, &fchs, NULL, NULL,
			FC_MAX_PDUSZ, 0);
}