#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfi_fcxp_send_req_s {int /*<<< orphan*/  mh; int /*<<< orphan*/  rsp_alen; int /*<<< orphan*/  req_alen; void* rsp_maxlen; void* req_len; int /*<<< orphan*/  fchs; int /*<<< orphan*/  cts; int /*<<< orphan*/  rsp_timeout; int /*<<< orphan*/  class; int /*<<< orphan*/  lp_fwtag; void* vf_id; void* max_frmsz; int /*<<< orphan*/  rport_fw_hndl; void* fcxp_tag; } ;
struct bfa_s {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_frmsz; } ;
struct bfa_rport_s {TYPE_2__ rport_info; int /*<<< orphan*/  fw_handle; } ;
struct bfa_fcxp_rsp_info_s {scalar_t__ rsp_maxlen; int /*<<< orphan*/  rsp_timeout; } ;
struct bfa_fcxp_req_info_s {scalar_t__ req_tot_len; int /*<<< orphan*/  fchs; int /*<<< orphan*/  cts; int /*<<< orphan*/  class; int /*<<< orphan*/  lp_tag; int /*<<< orphan*/  vf_id; struct bfa_rport_s* bfa_rport; } ;
struct bfa_fcxp_s {int use_ireqbuf; int nreq_sgles; int use_irspbuf; int nrsp_sgles; int /*<<< orphan*/  caller; int /*<<< orphan*/  (* rsp_sga_cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* req_sga_cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  fcxp_tag; struct bfa_fcxp_rsp_info_s rsp_info; struct bfa_fcxp_req_info_s req_info; TYPE_1__* fcxp_mod; } ;
struct TYPE_3__ {struct bfa_s* bfa; } ;

/* Variables and functions */
 scalar_t__ BFA_FCXP_MAX_LBUF_SZ ; 
 int /*<<< orphan*/  BFA_FCXP_REQ_PLD_PA (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  BFA_FCXP_RSP_PLD_PA (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  BFA_REQQ_FCXP ; 
 int /*<<< orphan*/  BFI_FCXP_H2I_SEND_REQ ; 
 int /*<<< orphan*/  BFI_MC_FCXP ; 
 int /*<<< orphan*/  FC_MAX_PDUSZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_alen_set (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fn_lpu (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_lps_get_fwtag (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_ci (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_pi (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_produce (struct bfa_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  hal_fcxp_tx_plog (struct bfa_s*,scalar_t__,struct bfa_fcxp_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcxp_queue(struct bfa_fcxp_s *fcxp, struct bfi_fcxp_send_req_s *send_req)
{
	struct bfa_s			*bfa = fcxp->fcxp_mod->bfa;
	struct bfa_fcxp_req_info_s	*reqi = &fcxp->req_info;
	struct bfa_fcxp_rsp_info_s	*rspi = &fcxp->rsp_info;
	struct bfa_rport_s		*rport = reqi->bfa_rport;

	bfi_h2i_set(send_req->mh, BFI_MC_FCXP, BFI_FCXP_H2I_SEND_REQ,
		    bfa_fn_lpu(bfa));

	send_req->fcxp_tag = cpu_to_be16(fcxp->fcxp_tag);
	if (rport) {
		send_req->rport_fw_hndl = rport->fw_handle;
		send_req->max_frmsz = cpu_to_be16(rport->rport_info.max_frmsz);
		if (send_req->max_frmsz == 0)
			send_req->max_frmsz = cpu_to_be16(FC_MAX_PDUSZ);
	} else {
		send_req->rport_fw_hndl = 0;
		send_req->max_frmsz = cpu_to_be16(FC_MAX_PDUSZ);
	}

	send_req->vf_id = cpu_to_be16(reqi->vf_id);
	send_req->lp_fwtag = bfa_lps_get_fwtag(bfa, reqi->lp_tag);
	send_req->class = reqi->class;
	send_req->rsp_timeout = rspi->rsp_timeout;
	send_req->cts = reqi->cts;
	send_req->fchs = reqi->fchs;

	send_req->req_len = cpu_to_be32(reqi->req_tot_len);
	send_req->rsp_maxlen = cpu_to_be32(rspi->rsp_maxlen);

	/*
	 * setup req sgles
	 */
	if (fcxp->use_ireqbuf == 1) {
		bfa_alen_set(&send_req->req_alen, reqi->req_tot_len,
					BFA_FCXP_REQ_PLD_PA(fcxp));
	} else {
		if (fcxp->nreq_sgles > 0) {
			WARN_ON(fcxp->nreq_sgles != 1);
			bfa_alen_set(&send_req->req_alen, reqi->req_tot_len,
				fcxp->req_sga_cbfn(fcxp->caller, 0));
		} else {
			WARN_ON(reqi->req_tot_len != 0);
			bfa_alen_set(&send_req->rsp_alen, 0, 0);
		}
	}

	/*
	 * setup rsp sgles
	 */
	if (fcxp->use_irspbuf == 1) {
		WARN_ON(rspi->rsp_maxlen > BFA_FCXP_MAX_LBUF_SZ);

		bfa_alen_set(&send_req->rsp_alen, rspi->rsp_maxlen,
					BFA_FCXP_RSP_PLD_PA(fcxp));
	} else {
		if (fcxp->nrsp_sgles > 0) {
			WARN_ON(fcxp->nrsp_sgles != 1);
			bfa_alen_set(&send_req->rsp_alen, rspi->rsp_maxlen,
				fcxp->rsp_sga_cbfn(fcxp->caller, 0));

		} else {
			WARN_ON(rspi->rsp_maxlen != 0);
			bfa_alen_set(&send_req->rsp_alen, 0, 0);
		}
	}

	hal_fcxp_tx_plog(bfa, reqi->req_tot_len, fcxp, &reqi->fchs);

	bfa_reqq_produce(bfa, BFA_REQQ_FCXP, send_req->mh);

	bfa_trc(bfa, bfa_reqq_pi(bfa, BFA_REQQ_FCXP));
	bfa_trc(bfa, bfa_reqq_ci(bfa, BFA_REQQ_FCXP));
}