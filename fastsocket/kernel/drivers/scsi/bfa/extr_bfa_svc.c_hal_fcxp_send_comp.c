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
typedef  int u16 ;
struct bfi_fcxp_send_rsp_s {scalar_t__ req_status; int /*<<< orphan*/  fchs; void* residue_len; void* rsp_len; int /*<<< orphan*/  fcxp_tag; } ;
struct bfa_s {int dummy; } ;
struct bfa_fcxp_s {scalar_t__ rsp_status; int /*<<< orphan*/  (* send_cbfn ) (int /*<<< orphan*/ *,struct bfa_fcxp_s*,int /*<<< orphan*/ ,scalar_t__,void*,void*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  hcb_qe; int /*<<< orphan*/  rsp_fchs; void* residue_len; void* rsp_len; int /*<<< orphan*/  send_cbarg; int /*<<< orphan*/ * caller; } ;
struct bfa_fcxp_mod_s {struct bfa_s* bfa; } ;

/* Variables and functions */
 struct bfa_fcxp_s* BFA_FCXP_FROM_TAG (struct bfa_fcxp_mod_s*,int) ; 
 struct bfa_fcxp_mod_s* BFA_FCXP_MOD (struct bfa_s*) ; 
 scalar_t__ BFA_STATUS_OK ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __bfa_fcxp_send_cbfn ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (void*) ; 
 int /*<<< orphan*/  bfa_cb_queue (struct bfa_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_free (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int) ; 
 int /*<<< orphan*/  hal_fcxp_rx_plog (struct bfa_s*,struct bfa_fcxp_s*,struct bfi_fcxp_send_rsp_s*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct bfa_fcxp_s*,int /*<<< orphan*/ ,scalar_t__,void*,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hal_fcxp_send_comp(struct bfa_s *bfa, struct bfi_fcxp_send_rsp_s *fcxp_rsp)
{
	struct bfa_fcxp_mod_s	*mod = BFA_FCXP_MOD(bfa);
	struct bfa_fcxp_s	*fcxp;
	u16		fcxp_tag = be16_to_cpu(fcxp_rsp->fcxp_tag);

	bfa_trc(bfa, fcxp_tag);

	fcxp_rsp->rsp_len = be32_to_cpu(fcxp_rsp->rsp_len);

	/*
	 * @todo f/w should not set residue to non-0 when everything
	 *	 is received.
	 */
	if (fcxp_rsp->req_status == BFA_STATUS_OK)
		fcxp_rsp->residue_len = 0;
	else
		fcxp_rsp->residue_len = be32_to_cpu(fcxp_rsp->residue_len);

	fcxp = BFA_FCXP_FROM_TAG(mod, fcxp_tag);

	WARN_ON(fcxp->send_cbfn == NULL);

	hal_fcxp_rx_plog(mod->bfa, fcxp, fcxp_rsp);

	if (fcxp->send_cbfn != NULL) {
		bfa_trc(mod->bfa, (NULL == fcxp->caller));
		if (fcxp->caller == NULL) {
			fcxp->send_cbfn(fcxp->caller, fcxp, fcxp->send_cbarg,
					fcxp_rsp->req_status, fcxp_rsp->rsp_len,
					fcxp_rsp->residue_len, &fcxp_rsp->fchs);
			/*
			 * fcxp automatically freed on return from the callback
			 */
			bfa_fcxp_free(fcxp);
		} else {
			fcxp->rsp_status = fcxp_rsp->req_status;
			fcxp->rsp_len = fcxp_rsp->rsp_len;
			fcxp->residue_len = fcxp_rsp->residue_len;
			fcxp->rsp_fchs = fcxp_rsp->fchs;

			bfa_cb_queue(bfa, &fcxp->hcb_qe,
					__bfa_fcxp_send_cbfn, fcxp);
		}
	} else {
		bfa_trc(bfa, (NULL == fcxp->send_cbfn));
	}
}