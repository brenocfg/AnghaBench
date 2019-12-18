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
struct fc_seq_els_data {int /*<<< orphan*/  explan; int /*<<< orphan*/  reason; } ;
struct fc_rport_priv {int rp_state; int /*<<< orphan*/  rp_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* seq_els_rsp_send ) (struct fc_frame*,int const,struct fc_seq_els_data*) ;struct fc_rport_priv* (* rport_lookup ) (struct fc_lport*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  disc_mutex; } ;
struct fc_lport {TYPE_2__ tt; TYPE_1__ disc; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
#define  ELS_ADISC 137 
 int /*<<< orphan*/  ELS_EXPL_PLOGI_REQD ; 
 int const ELS_LS_RJT ; 
#define  ELS_PRLI 136 
#define  ELS_PRLO 135 
#define  ELS_REC 134 
 int /*<<< orphan*/  ELS_RJT_UNAB ; 
#define  ELS_RLS 133 
#define  ELS_RRQ 132 
#define  RPORT_ST_ADISC 131 
#define  RPORT_ST_PRLI 130 
#define  RPORT_ST_READY 129 
#define  RPORT_ST_RTV 128 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 int fc_frame_payload_op (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_frame_sid (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_recv_adisc_req (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_recv_prli_req (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_recv_prlo_req (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_recv_rls_req (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct fc_rport_priv* stub1 (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct fc_frame*,int const,struct fc_seq_els_data*) ; 
 int /*<<< orphan*/  stub3 (struct fc_frame*,int const,struct fc_seq_els_data*) ; 
 int /*<<< orphan*/  stub4 (struct fc_frame*,int const,struct fc_seq_els_data*) ; 

__attribute__((used)) static void fc_rport_recv_els_req(struct fc_lport *lport, struct fc_frame *fp)
{
	struct fc_rport_priv *rdata;
	struct fc_seq_els_data els_data;

	mutex_lock(&lport->disc.disc_mutex);
	rdata = lport->tt.rport_lookup(lport, fc_frame_sid(fp));
	if (!rdata) {
		mutex_unlock(&lport->disc.disc_mutex);
		goto reject;
	}
	mutex_lock(&rdata->rp_mutex);
	mutex_unlock(&lport->disc.disc_mutex);

	switch (rdata->rp_state) {
	case RPORT_ST_PRLI:
	case RPORT_ST_RTV:
	case RPORT_ST_READY:
	case RPORT_ST_ADISC:
		break;
	default:
		mutex_unlock(&rdata->rp_mutex);
		goto reject;
	}

	switch (fc_frame_payload_op(fp)) {
	case ELS_PRLI:
		fc_rport_recv_prli_req(rdata, fp);
		break;
	case ELS_PRLO:
		fc_rport_recv_prlo_req(rdata, fp);
		break;
	case ELS_ADISC:
		fc_rport_recv_adisc_req(rdata, fp);
		break;
	case ELS_RRQ:
		lport->tt.seq_els_rsp_send(fp, ELS_RRQ, NULL);
		fc_frame_free(fp);
		break;
	case ELS_REC:
		lport->tt.seq_els_rsp_send(fp, ELS_REC, NULL);
		fc_frame_free(fp);
		break;
	case ELS_RLS:
		fc_rport_recv_rls_req(rdata, fp);
		break;
	default:
		fc_frame_free(fp);	/* can't happen */
		break;
	}

	mutex_unlock(&rdata->rp_mutex);
	return;

reject:
	els_data.reason = ELS_RJT_UNAB;
	els_data.explan = ELS_EXPL_PLOGI_REQD;
	lport->tt.seq_els_rsp_send(fp, ELS_LS_RJT, &els_data);
	fc_frame_free(fp);
}