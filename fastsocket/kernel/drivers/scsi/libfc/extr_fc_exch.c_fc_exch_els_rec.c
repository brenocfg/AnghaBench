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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int /*<<< orphan*/  (* frame_send ) (struct fc_lport*,struct fc_frame*) ;} ;
struct fc_lport {TYPE_2__ tt; int /*<<< orphan*/  host; } ;
struct fc_frame {int dummy; } ;
struct TYPE_3__ {int rec_data; } ;
struct fc_exch {scalar_t__ oid; scalar_t__ oxid; scalar_t__ rxid; scalar_t__ sid; scalar_t__ did; int esb_stat; TYPE_1__ seq; } ;
struct fc_els_rec_acc {void* reca_e_stat; void* reca_fc4value; int /*<<< orphan*/  reca_rfid; int /*<<< orphan*/  reca_rx_id; int /*<<< orphan*/  reca_ofid; int /*<<< orphan*/  reca_ox_id; int /*<<< orphan*/  reca_cmd; } ;
struct fc_els_rec {int /*<<< orphan*/  rec_s_id; int /*<<< orphan*/  rec_ox_id; int /*<<< orphan*/  rec_rx_id; } ;
typedef  enum fc_els_rjt_reason { ____Placeholder_fc_els_rjt_reason } fc_els_rjt_reason ;
typedef  enum fc_els_rjt_explan { ____Placeholder_fc_els_rjt_explan } fc_els_rjt_explan ;

/* Variables and functions */
 int ELS_EXPL_INV_LEN ; 
 int ELS_EXPL_OXID_RXID ; 
 int /*<<< orphan*/  ELS_LS_ACC ; 
 int ELS_RJT_LOGIC ; 
 int ESB_ST_COMPLETE ; 
 int ESB_ST_RESP ; 
 int ESB_ST_SEQ_INIT ; 
 int /*<<< orphan*/  FC_RCTL_ELS_REP ; 
 scalar_t__ FC_XID_UNKNOWN ; 
 struct fc_exch* fc_exch_lookup (struct fc_lport*,scalar_t__) ; 
 int /*<<< orphan*/  fc_exch_release (struct fc_exch*) ; 
 int /*<<< orphan*/  fc_fill_reply_hdr (struct fc_frame*,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,int) ; 
 void* fc_frame_payload_get (struct fc_frame*,int) ; 
 scalar_t__ fc_host_port_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_seq_ls_rjt (struct fc_frame*,int,int) ; 
 struct fc_lport* fr_dev (struct fc_frame*) ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,scalar_t__) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct fc_els_rec_acc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntoh24 (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,struct fc_frame*) ; 

__attribute__((used)) static void fc_exch_els_rec(struct fc_frame *rfp)
{
	struct fc_lport *lport;
	struct fc_frame *fp;
	struct fc_exch *ep;
	struct fc_els_rec *rp;
	struct fc_els_rec_acc *acc;
	enum fc_els_rjt_reason reason = ELS_RJT_LOGIC;
	enum fc_els_rjt_explan explan;
	u32 sid;
	u16 rxid;
	u16 oxid;

	lport = fr_dev(rfp);
	rp = fc_frame_payload_get(rfp, sizeof(*rp));
	explan = ELS_EXPL_INV_LEN;
	if (!rp)
		goto reject;
	sid = ntoh24(rp->rec_s_id);
	rxid = ntohs(rp->rec_rx_id);
	oxid = ntohs(rp->rec_ox_id);

	ep = fc_exch_lookup(lport,
			    sid == fc_host_port_id(lport->host) ? oxid : rxid);
	explan = ELS_EXPL_OXID_RXID;
	if (!ep)
		goto reject;
	if (ep->oid != sid || oxid != ep->oxid)
		goto rel;
	if (rxid != FC_XID_UNKNOWN && rxid != ep->rxid)
		goto rel;
	fp = fc_frame_alloc(lport, sizeof(*acc));
	if (!fp)
		goto out;

	acc = fc_frame_payload_get(fp, sizeof(*acc));
	memset(acc, 0, sizeof(*acc));
	acc->reca_cmd = ELS_LS_ACC;
	acc->reca_ox_id = rp->rec_ox_id;
	memcpy(acc->reca_ofid, rp->rec_s_id, 3);
	acc->reca_rx_id = htons(ep->rxid);
	if (ep->sid == ep->oid)
		hton24(acc->reca_rfid, ep->did);
	else
		hton24(acc->reca_rfid, ep->sid);
	acc->reca_fc4value = htonl(ep->seq.rec_data);
	acc->reca_e_stat = htonl(ep->esb_stat & (ESB_ST_RESP |
						 ESB_ST_SEQ_INIT |
						 ESB_ST_COMPLETE));
	fc_fill_reply_hdr(fp, rfp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);
out:
	fc_exch_release(ep);
	return;

rel:
	fc_exch_release(ep);
reject:
	fc_seq_ls_rjt(rfp, reason, explan);
}