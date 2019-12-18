#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bfi_lps_login_rsp_s {scalar_t__ bfa_tag; int status; int /*<<< orphan*/  ext_status; int /*<<< orphan*/  lsrjt_expl; int /*<<< orphan*/  lsrjt_rsn; int /*<<< orphan*/  fcf_mac; int /*<<< orphan*/  brcd_switch; int /*<<< orphan*/  lp_mac; int /*<<< orphan*/  auth_req; int /*<<< orphan*/  node_name; int /*<<< orphan*/  port_name; int /*<<< orphan*/  bb_credit; int /*<<< orphan*/  npiv_en; int /*<<< orphan*/  lp_pid; int /*<<< orphan*/  f_port; int /*<<< orphan*/  fw_tag; } ;
struct bfa_s {int dummy; } ;
struct bfa_lps_s {int status; int /*<<< orphan*/  qe; int /*<<< orphan*/  ext_status; int /*<<< orphan*/  lsrjt_expl; int /*<<< orphan*/  lsrjt_rsn; int /*<<< orphan*/  fcf_mac; int /*<<< orphan*/  brcd_switch; int /*<<< orphan*/  lp_mac; int /*<<< orphan*/  auth_req; int /*<<< orphan*/  pr_nwwn; int /*<<< orphan*/  pr_pwwn; int /*<<< orphan*/  pr_bbcred; int /*<<< orphan*/  npiv_en; int /*<<< orphan*/  lp_pid; int /*<<< orphan*/  fport; int /*<<< orphan*/  fw_tag; } ;
struct bfa_lps_mod_s {scalar_t__ num_lps; int /*<<< orphan*/  lps_active_q; } ;

/* Variables and functions */
 struct bfa_lps_s* BFA_LPS_FROM_TAG (struct bfa_lps_mod_s*,scalar_t__) ; 
 struct bfa_lps_mod_s* BFA_LPS_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  BFA_LPS_SM_FWRSP ; 
#define  BFA_STATUS_EPROTOCOL 131 
#define  BFA_STATUS_FABRIC_RJT 130 
#define  BFA_STATUS_OK 129 
#define  BFA_STATUS_VPORT_MAX 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_lps_no_res (struct bfa_lps_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_lps_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_lps_login_rsp(struct bfa_s *bfa, struct bfi_lps_login_rsp_s *rsp)
{
	struct bfa_lps_mod_s	*mod = BFA_LPS_MOD(bfa);
	struct bfa_lps_s	*lps;

	WARN_ON(rsp->bfa_tag >= mod->num_lps);
	lps = BFA_LPS_FROM_TAG(mod, rsp->bfa_tag);

	lps->status = rsp->status;
	switch (rsp->status) {
	case BFA_STATUS_OK:
		lps->fw_tag	= rsp->fw_tag;
		lps->fport	= rsp->f_port;
		if (lps->fport)
			lps->lp_pid = rsp->lp_pid;
		lps->npiv_en	= rsp->npiv_en;
		lps->pr_bbcred	= be16_to_cpu(rsp->bb_credit);
		lps->pr_pwwn	= rsp->port_name;
		lps->pr_nwwn	= rsp->node_name;
		lps->auth_req	= rsp->auth_req;
		lps->lp_mac	= rsp->lp_mac;
		lps->brcd_switch = rsp->brcd_switch;
		lps->fcf_mac	= rsp->fcf_mac;

		break;

	case BFA_STATUS_FABRIC_RJT:
		lps->lsrjt_rsn = rsp->lsrjt_rsn;
		lps->lsrjt_expl = rsp->lsrjt_expl;

		break;

	case BFA_STATUS_EPROTOCOL:
		lps->ext_status = rsp->ext_status;

		break;

	case BFA_STATUS_VPORT_MAX:
		if (rsp->ext_status)
			bfa_lps_no_res(lps, rsp->ext_status);
		break;

	default:
		/* Nothing to do with other status */
		break;
	}

	list_del(&lps->qe);
	list_add_tail(&lps->qe, &mod->lps_active_q);
	bfa_sm_send_event(lps, BFA_LPS_SM_FWRSP);
}