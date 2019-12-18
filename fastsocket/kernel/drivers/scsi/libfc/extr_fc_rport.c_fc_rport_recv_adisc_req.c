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
struct TYPE_2__ {int /*<<< orphan*/  (* frame_send ) (struct fc_lport*,struct fc_frame*) ;int /*<<< orphan*/  (* seq_els_rsp_send ) (struct fc_frame*,int /*<<< orphan*/ ,struct fc_seq_els_data*) ;} ;
struct fc_lport {TYPE_1__ tt; } ;
struct fc_frame {int dummy; } ;
struct fc_els_adisc {int /*<<< orphan*/  adisc_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_EXPL_INV_LEN ; 
 int /*<<< orphan*/  ELS_LS_ACC ; 
 int /*<<< orphan*/  ELS_LS_RJT ; 
 int /*<<< orphan*/  ELS_RJT_PROT ; 
 int /*<<< orphan*/  FC_RCTL_ELS_REP ; 
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*) ; 
 int /*<<< orphan*/  fc_adisc_fill (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_fill_reply_hdr (struct fc_frame*,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,int) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_els_adisc* fc_frame_payload_get (struct fc_frame*,int) ; 
 int /*<<< orphan*/  stub1 (struct fc_frame*,int /*<<< orphan*/ ,struct fc_seq_els_data*) ; 
 int /*<<< orphan*/  stub2 (struct fc_lport*,struct fc_frame*) ; 

__attribute__((used)) static void fc_rport_recv_adisc_req(struct fc_rport_priv *rdata,
				    struct fc_frame *in_fp)
{
	struct fc_lport *lport = rdata->local_port;
	struct fc_frame *fp;
	struct fc_els_adisc *adisc;
	struct fc_seq_els_data rjt_data;

	FC_RPORT_DBG(rdata, "Received ADISC request\n");

	adisc = fc_frame_payload_get(in_fp, sizeof(*adisc));
	if (!adisc) {
		rjt_data.reason = ELS_RJT_PROT;
		rjt_data.explan = ELS_EXPL_INV_LEN;
		lport->tt.seq_els_rsp_send(in_fp, ELS_LS_RJT, &rjt_data);
		goto drop;
	}

	fp = fc_frame_alloc(lport, sizeof(*adisc));
	if (!fp)
		goto drop;
	fc_adisc_fill(lport, fp);
	adisc = fc_frame_payload_get(fp, sizeof(*adisc));
	adisc->adisc_cmd = ELS_LS_ACC;
	fc_fill_reply_hdr(fp, in_fp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);
drop:
	fc_frame_free(in_fp);
}