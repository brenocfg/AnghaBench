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
struct fc_seq_els_data {int /*<<< orphan*/  explan; int /*<<< orphan*/  reason; } ;
struct fc_rport_priv {struct fc_lport* local_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* seq_els_rsp_send ) (struct fc_frame*,int /*<<< orphan*/ ,struct fc_seq_els_data*) ;int /*<<< orphan*/  (* frame_send ) (struct fc_lport*,struct fc_frame*) ;int /*<<< orphan*/  (* get_lesb ) (struct fc_lport*,struct fc_els_lesb*) ;} ;
struct fc_host_statistics {int /*<<< orphan*/  invalid_crc_count; int /*<<< orphan*/  invalid_tx_word_count; int /*<<< orphan*/  prim_seq_protocol_err_count; int /*<<< orphan*/  loss_of_signal_count; int /*<<< orphan*/  loss_of_sync_count; int /*<<< orphan*/  link_failure_count; } ;
struct fc_lport {TYPE_1__ tt; struct fc_host_statistics host_stats; int /*<<< orphan*/  host; } ;
struct fc_frame {int dummy; } ;
struct fc_els_lesb {void* lesb_inv_crc; void* lesb_inv_word; void* lesb_prim_err; void* lesb_sig_loss; void* lesb_sync_loss; void* lesb_link_fail; } ;
struct fc_els_rls_resp {struct fc_els_lesb rls_lesb; int /*<<< orphan*/  rls_cmd; } ;
struct fc_els_rls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_EXPL_INSUF_RES ; 
 int /*<<< orphan*/  ELS_EXPL_INV_LEN ; 
 int /*<<< orphan*/  ELS_LS_ACC ; 
 int /*<<< orphan*/  ELS_LS_RJT ; 
 int /*<<< orphan*/  ELS_RJT_PROT ; 
 int /*<<< orphan*/  ELS_RJT_UNAB ; 
 int /*<<< orphan*/  FC_RCTL_ELS_REP ; 
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_fill_reply_hdr (struct fc_frame*,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,int) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 void* fc_frame_payload_get (struct fc_frame*,int) ; 
 int /*<<< orphan*/  fc_get_host_stats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rport_state (struct fc_rport_priv*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fc_els_rls_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,struct fc_els_lesb*) ; 
 int /*<<< orphan*/  stub2 (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  stub3 (struct fc_frame*,int /*<<< orphan*/ ,struct fc_seq_els_data*) ; 

__attribute__((used)) static void fc_rport_recv_rls_req(struct fc_rport_priv *rdata,
				  struct fc_frame *rx_fp)

{
	struct fc_lport *lport = rdata->local_port;
	struct fc_frame *fp;
	struct fc_els_rls *rls;
	struct fc_els_rls_resp *rsp;
	struct fc_els_lesb *lesb;
	struct fc_seq_els_data rjt_data;
	struct fc_host_statistics *hst;

	FC_RPORT_DBG(rdata, "Received RLS request while in state %s\n",
		     fc_rport_state(rdata));

	rls = fc_frame_payload_get(rx_fp, sizeof(*rls));
	if (!rls) {
		rjt_data.reason = ELS_RJT_PROT;
		rjt_data.explan = ELS_EXPL_INV_LEN;
		goto out_rjt;
	}

	fp = fc_frame_alloc(lport, sizeof(*rsp));
	if (!fp) {
		rjt_data.reason = ELS_RJT_UNAB;
		rjt_data.explan = ELS_EXPL_INSUF_RES;
		goto out_rjt;
	}

	rsp = fc_frame_payload_get(fp, sizeof(*rsp));
	memset(rsp, 0, sizeof(*rsp));
	rsp->rls_cmd = ELS_LS_ACC;
	lesb = &rsp->rls_lesb;
	if (lport->tt.get_lesb) {
		/* get LESB from LLD if it supports it */
		lport->tt.get_lesb(lport, lesb);
	} else {
		fc_get_host_stats(lport->host);
		hst = &lport->host_stats;
		lesb->lesb_link_fail = htonl(hst->link_failure_count);
		lesb->lesb_sync_loss = htonl(hst->loss_of_sync_count);
		lesb->lesb_sig_loss = htonl(hst->loss_of_signal_count);
		lesb->lesb_prim_err = htonl(hst->prim_seq_protocol_err_count);
		lesb->lesb_inv_word = htonl(hst->invalid_tx_word_count);
		lesb->lesb_inv_crc = htonl(hst->invalid_crc_count);
	}

	fc_fill_reply_hdr(fp, rx_fp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);
	goto out;

out_rjt:
	lport->tt.seq_els_rsp_send(rx_fp, ELS_LS_RJT, &rjt_data);
out:
	fc_frame_free(rx_fp);
}