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
typedef  void* u32 ;
struct fcp_srr {int srr_r_ctl; int /*<<< orphan*/  srr_rel_off; void* srr_rx_id; void* srr_ox_id; int /*<<< orphan*/  srr_op; } ;
struct fc_seq {int dummy; } ;
struct fc_rport_libfc_priv {int flags; scalar_t__ rp_state; TYPE_1__* local_port; } ;
struct fc_rport {int /*<<< orphan*/  port_id; struct fc_rport_libfc_priv* dd_data; } ;
struct TYPE_4__ {struct fc_seq* (* exch_seq_send ) (struct fc_lport*,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_fcp_pkt*,int /*<<< orphan*/ ) ;} ;
struct fc_lport {TYPE_2__ tt; } ;
struct fc_frame {int dummy; } ;
struct fc_fcp_pkt {int /*<<< orphan*/  state; void* xfer_contig_end; void* xfer_len; struct fc_seq* recov_seq; struct fc_rport* rport; int /*<<< orphan*/  seq_ptr; struct fc_lport* lp; } ;
struct fc_exch {int /*<<< orphan*/  rxid; int /*<<< orphan*/  oxid; } ;
typedef  enum fc_rctl { ____Placeholder_fc_rctl } fc_rctl ;
struct TYPE_3__ {int /*<<< orphan*/  port_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_SRR ; 
 int /*<<< orphan*/  FC_FCTL_REQ ; 
 int /*<<< orphan*/  FC_RCTL_ELS4_REQ ; 
 int FC_RP_FLAGS_RETRY ; 
 int /*<<< orphan*/  FC_SRB_RCV_STATUS ; 
 int /*<<< orphan*/  FC_TYPE_FCP ; 
 scalar_t__ RPORT_ST_READY ; 
 struct fc_frame* fc_fcp_frame_alloc (struct fc_lport*,int) ; 
 int /*<<< orphan*/  fc_fcp_pkt_destroy ; 
 int /*<<< orphan*/  fc_fcp_pkt_hold (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_fcp_retry_cmd (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  fc_fcp_srr_resp ; 
 int /*<<< orphan*/  fc_fill_fc_hdr (struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fcp_srr* fc_frame_payload_get (struct fc_frame*,int) ; 
 struct fc_exch* fc_seq_exch (int /*<<< orphan*/ ) ; 
 unsigned int get_fsp_rec_tov (struct fc_fcp_pkt*) ; 
 int /*<<< orphan*/  htonl (void*) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned int) ; 
 int /*<<< orphan*/  memset (struct fcp_srr*,int /*<<< orphan*/ ,int) ; 
 struct fc_seq* stub1 (struct fc_lport*,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_fcp_pkt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_fcp_srr(struct fc_fcp_pkt *fsp, enum fc_rctl r_ctl, u32 offset)
{
	struct fc_lport *lport = fsp->lp;
	struct fc_rport *rport;
	struct fc_rport_libfc_priv *rpriv;
	struct fc_exch *ep = fc_seq_exch(fsp->seq_ptr);
	struct fc_seq *seq;
	struct fcp_srr *srr;
	struct fc_frame *fp;
	unsigned int rec_tov;

	rport = fsp->rport;
	rpriv = rport->dd_data;

	if (!(rpriv->flags & FC_RP_FLAGS_RETRY) ||
	    rpriv->rp_state != RPORT_ST_READY)
		goto retry;			/* shouldn't happen */
	fp = fc_fcp_frame_alloc(lport, sizeof(*srr));
	if (!fp)
		goto retry;

	srr = fc_frame_payload_get(fp, sizeof(*srr));
	memset(srr, 0, sizeof(*srr));
	srr->srr_op = ELS_SRR;
	srr->srr_ox_id = htons(ep->oxid);
	srr->srr_rx_id = htons(ep->rxid);
	srr->srr_r_ctl = r_ctl;
	srr->srr_rel_off = htonl(offset);

	fc_fill_fc_hdr(fp, FC_RCTL_ELS4_REQ, rport->port_id,
		       rpriv->local_port->port_id, FC_TYPE_FCP,
		       FC_FCTL_REQ, 0);

	rec_tov = get_fsp_rec_tov(fsp);
	seq = lport->tt.exch_seq_send(lport, fp, fc_fcp_srr_resp,
				      fc_fcp_pkt_destroy,
				      fsp, jiffies_to_msecs(rec_tov));
	if (!seq)
		goto retry;

	fsp->recov_seq = seq;
	fsp->xfer_len = offset;
	fsp->xfer_contig_end = offset;
	fsp->state &= ~FC_SRB_RCV_STATUS;
	fc_fcp_pkt_hold(fsp);		/* hold for outstanding SRR */
	return;
retry:
	fc_fcp_retry_cmd(fsp);
}