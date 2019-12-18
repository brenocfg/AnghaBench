#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mac; int /*<<< orphan*/  lsap; } ;
struct llc_sock {TYPE_2__ daddr; TYPE_3__* dev; int /*<<< orphan*/  vR; struct llc_sap* sap; } ;
struct TYPE_4__ {int /*<<< orphan*/  lsap; } ;
struct llc_sap {TYPE_1__ laddr; } ;
struct llc_pdu_sn {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  LLC_I_GET_NR (struct llc_pdu_sn*) ; 
 int /*<<< orphan*/  LLC_PDU_RSP ; 
 int /*<<< orphan*/  LLC_PDU_TYPE_U ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 struct sk_buff* llc_alloc_frame (struct sock*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_conn_resend_i_pdu_as_cmd (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_conn_send_pdu (struct sock*,struct sk_buff*) ; 
 int llc_mac_hdr_init (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_header_init (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_init_as_rr_rsp (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct llc_pdu_sn* llc_pdu_sn_hdr (struct sk_buff*) ; 
 struct llc_sock* llc_sk (struct sock*) ; 

int llc_conn_ac_resend_i_xxx_x_set_0_or_send_rr(struct sock *sk,
						struct sk_buff *skb)
{
	u8 nr;
	struct llc_pdu_sn *pdu = llc_pdu_sn_hdr(skb);
	int rc = -ENOBUFS;
	struct llc_sock *llc = llc_sk(sk);
	struct sk_buff *nskb = llc_alloc_frame(sk, llc->dev, LLC_PDU_TYPE_U, 0);

	if (nskb) {
		struct llc_sap *sap = llc->sap;

		llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, sap->laddr.lsap,
				    llc->daddr.lsap, LLC_PDU_RSP);
		llc_pdu_init_as_rr_rsp(nskb, 0, llc->vR);
		rc = llc_mac_hdr_init(nskb, llc->dev->dev_addr, llc->daddr.mac);
		if (likely(!rc))
			llc_conn_send_pdu(sk, nskb);
		else
			kfree_skb(skb);
	}
	if (rc) {
		nr = LLC_I_GET_NR(pdu);
		rc = 0;
		llc_conn_resend_i_pdu_as_cmd(sk, nr, 0);
	}
	return rc;
}