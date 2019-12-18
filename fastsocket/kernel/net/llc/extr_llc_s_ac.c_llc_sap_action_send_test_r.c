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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  lsap; } ;
struct llc_sap {TYPE_1__ laddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  LLC_PDU_RSP ; 
 int /*<<< orphan*/  LLC_PDU_TYPE_U ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 TYPE_2__* eth_hdr (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 struct sk_buff* llc_alloc_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int llc_mac_hdr_init (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llc_pdu_decode_da (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llc_pdu_decode_sa (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llc_pdu_decode_ssap (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llc_pdu_header_init (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_init_as_test_rsp (struct sk_buff*,struct sk_buff*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

int llc_sap_action_send_test_r(struct llc_sap *sap, struct sk_buff *skb)
{
	u8 mac_da[ETH_ALEN], mac_sa[ETH_ALEN], dsap;
	struct sk_buff *nskb;
	int rc = 1;
	u32 data_size;

	llc_pdu_decode_sa(skb, mac_da);
	llc_pdu_decode_da(skb, mac_sa);
	llc_pdu_decode_ssap(skb, &dsap);

	/* The test request command is type U (llc_len = 3) */
	data_size = ntohs(eth_hdr(skb)->h_proto) - 3;
	nskb = llc_alloc_frame(NULL, skb->dev, LLC_PDU_TYPE_U, data_size);
	if (!nskb)
		goto out;
	llc_pdu_header_init(nskb, LLC_PDU_TYPE_U, sap->laddr.lsap, dsap,
			    LLC_PDU_RSP);
	llc_pdu_init_as_test_rsp(nskb, skb);
	rc = llc_mac_hdr_init(nskb, mac_sa, mac_da);
	if (likely(!rc))
		rc = dev_queue_xmit(nskb);
out:
	return rc;
}