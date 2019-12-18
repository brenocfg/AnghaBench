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
struct sk_buff {scalar_t__ data; } ;
struct fip_header {int fip_subcode; } ;
struct fcoe_rport {int dummy; } ;
struct fcoe_ctlr {int /*<<< orphan*/  ctlr_mutex; } ;
struct fc_rport_priv {int dummy; } ;
typedef  enum fip_vn2vn_subcode { ____Placeholder_fip_vn2vn_subcode } fip_vn2vn_subcode ;

/* Variables and functions */
#define  FIP_SC_VN_BEACON 132 
#define  FIP_SC_VN_CLAIM_NOTIFY 131 
#define  FIP_SC_VN_CLAIM_REP 130 
#define  FIP_SC_VN_PROBE_REP 129 
#define  FIP_SC_VN_PROBE_REQ 128 
 int /*<<< orphan*/  LIBFCOE_FIP_DBG (struct fcoe_ctlr*,char*,int) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_beacon (struct fcoe_ctlr*,struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_claim_notify (struct fcoe_ctlr*,struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_claim_resp (struct fcoe_ctlr*,struct fc_rport_priv*) ; 
 int fcoe_ctlr_vn_parse (struct fcoe_ctlr*,struct sk_buff*,struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_probe_reply (struct fcoe_ctlr*,struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_probe_req (struct fcoe_ctlr*,struct fc_rport_priv*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fcoe_ctlr_vn_recv(struct fcoe_ctlr *fip, struct sk_buff *skb)
{
	struct fip_header *fiph;
	enum fip_vn2vn_subcode sub;
	struct {
		struct fc_rport_priv rdata;
		struct fcoe_rport frport;
	} buf;
	int rc;

	fiph = (struct fip_header *)skb->data;
	sub = fiph->fip_subcode;

	rc = fcoe_ctlr_vn_parse(fip, skb, &buf.rdata);
	if (rc) {
		LIBFCOE_FIP_DBG(fip, "vn_recv vn_parse error %d\n", rc);
		goto drop;
	}

	mutex_lock(&fip->ctlr_mutex);
	switch (sub) {
	case FIP_SC_VN_PROBE_REQ:
		fcoe_ctlr_vn_probe_req(fip, &buf.rdata);
		break;
	case FIP_SC_VN_PROBE_REP:
		fcoe_ctlr_vn_probe_reply(fip, &buf.rdata);
		break;
	case FIP_SC_VN_CLAIM_NOTIFY:
		fcoe_ctlr_vn_claim_notify(fip, &buf.rdata);
		break;
	case FIP_SC_VN_CLAIM_REP:
		fcoe_ctlr_vn_claim_resp(fip, &buf.rdata);
		break;
	case FIP_SC_VN_BEACON:
		fcoe_ctlr_vn_beacon(fip, &buf.rdata);
		break;
	default:
		LIBFCOE_FIP_DBG(fip, "vn_recv unknown subcode %d\n", sub);
		rc = -1;
		break;
	}
	mutex_unlock(&fip->ctlr_mutex);
drop:
	kfree_skb(skb);
	return rc;
}