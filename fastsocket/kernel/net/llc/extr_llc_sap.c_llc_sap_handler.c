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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct llc_sap {int dummy; } ;
struct llc_addr {int /*<<< orphan*/  mac; int /*<<< orphan*/  lsap; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sock* llc_lookup_dgram (struct llc_sap*,struct llc_addr*) ; 
 scalar_t__ llc_mac_multicast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_decode_da (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_pdu_decode_dsap (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llc_sap_mcast (struct llc_sap*,struct llc_addr*,struct sk_buff*) ; 
 int /*<<< orphan*/  llc_sap_rcv (struct llc_sap*,struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

void llc_sap_handler(struct llc_sap *sap, struct sk_buff *skb)
{
	struct llc_addr laddr;

	llc_pdu_decode_da(skb, laddr.mac);
	llc_pdu_decode_dsap(skb, &laddr.lsap);

	if (llc_mac_multicast(laddr.mac)) {
		llc_sap_mcast(sap, &laddr, skb);
		kfree_skb(skb);
	} else {
		struct sock *sk = llc_lookup_dgram(sap, &laddr);
		if (sk) {
			llc_sap_rcv(sap, skb, sk);
			sock_put(sk);
		} else
			kfree_skb(skb);
	}
}