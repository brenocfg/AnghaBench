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
typedef  int u8 ;
struct sk_buff {int transport_header; scalar_t__ protocol; scalar_t__ data; } ;
struct llc_pdu_un {int ctrl_1; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int LLC_PDU_TYPE_MASK ; 
 int LLC_PDU_TYPE_U ; 
 TYPE_1__* eth_hdr (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int pskb_trim_rcsum (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int* skb_tail_pointer (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int llc_fixup_skb(struct sk_buff *skb)
{
	u8 llc_len = 2;
	struct llc_pdu_un *pdu;

	if (unlikely(!pskb_may_pull(skb, sizeof(*pdu))))
		return 0;

	pdu = (struct llc_pdu_un *)skb->data;
	if ((pdu->ctrl_1 & LLC_PDU_TYPE_MASK) == LLC_PDU_TYPE_U)
		llc_len = 1;
	llc_len += 2;

	if (unlikely(!pskb_may_pull(skb, llc_len)))
		return 0;

	skb->transport_header += llc_len;
	skb_pull(skb, llc_len);
	if (skb->protocol == htons(ETH_P_802_2)) {
		__be16 pdulen = eth_hdr(skb)->h_proto;
		s32 data_size = ntohs(pdulen) - llc_len;

		if (data_size < 0 ||
		    ((skb_tail_pointer(skb) -
		      (u8 *)pdu) - llc_len) < data_size)
			return 0;
		if (unlikely(pskb_trim_rcsum(skb, data_size)))
			return 0;
	}
	return 1;
}