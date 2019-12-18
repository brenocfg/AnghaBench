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
typedef  scalar_t__ u8 ;
struct sk_buff {int len; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_802_2 ; 
 scalar_t__ LLC_SAP_SNAP ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static __be16 parse_ethertype(struct sk_buff *skb)
{
	struct llc_snap_hdr {
		u8  dsap;  /* Always 0xAA */
		u8  ssap;  /* Always 0xAA */
		u8  ctrl;
		u8  oui[3];
		__be16 ethertype;
	};
	struct llc_snap_hdr *llc;
	__be16 proto;

	proto = *(__be16 *) skb->data;
	__skb_pull(skb, sizeof(__be16));

	if (ntohs(proto) >= 1536)
		return proto;

	if (skb->len < sizeof(struct llc_snap_hdr))
		return htons(ETH_P_802_2);

	if (unlikely(!pskb_may_pull(skb, sizeof(struct llc_snap_hdr))))
		return htons(0);

	llc = (struct llc_snap_hdr *) skb->data;
	if (llc->dsap != LLC_SAP_SNAP ||
	    llc->ssap != LLC_SAP_SNAP ||
	    (llc->oui[0] | llc->oui[1] | llc->oui[2]) != 0)
		return htons(ETH_P_802_2);

	__skb_pull(skb, sizeof(struct llc_snap_hdr));

	if (ntohs(llc->ethertype) >= 1536)
		return llc->ethertype;

	return htons(ETH_P_802_2);
}