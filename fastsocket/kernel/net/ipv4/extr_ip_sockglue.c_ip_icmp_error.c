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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int ee_errno; scalar_t__ ee_data; int /*<<< orphan*/  ee_info; scalar_t__ ee_pad; int /*<<< orphan*/  ee_code; int /*<<< orphan*/  ee_type; int /*<<< orphan*/  ee_origin; } ;
struct sock_exterr_skb {int /*<<< orphan*/  port; int /*<<< orphan*/ * addr_offset; TYPE_1__ ee; } ;
struct sock {int dummy; } ;
struct sk_buff {int data; } ;
struct iphdr {int /*<<< orphan*/  daddr; } ;
struct inet_sock {int /*<<< orphan*/  recverr; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sock_exterr_skb* SKB_EXT_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  SO_EE_ORIGIN_ICMP ; 
 TYPE_2__* icmp_hdr (struct sk_buff*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_pull (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 scalar_t__ sock_queue_err_skb (struct sock*,struct sk_buff*) ; 

void ip_icmp_error(struct sock *sk, struct sk_buff *skb, int err,
		   __be16 port, u32 info, u8 *payload)
{
	struct inet_sock *inet = inet_sk(sk);
	struct sock_exterr_skb *serr;

	if (!inet->recverr)
		return;

	skb = skb_clone(skb, GFP_ATOMIC);
	if (!skb)
		return;

	serr = SKB_EXT_ERR(skb);
	serr->ee.ee_errno = err;
	serr->ee.ee_origin = SO_EE_ORIGIN_ICMP;
	serr->ee.ee_type = icmp_hdr(skb)->type;
	serr->ee.ee_code = icmp_hdr(skb)->code;
	serr->ee.ee_pad = 0;
	serr->ee.ee_info = info;
	serr->ee.ee_data = 0;
	serr->addr_offset = (u8 *)&(((struct iphdr *)(icmp_hdr(skb) + 1))->daddr) -
				   skb_network_header(skb);
	serr->port = port;

	if (skb_pull(skb, payload - skb->data) != NULL) {
		skb_reset_transport_header(skb);
		if (sock_queue_err_skb(sk, skb) == 0)
			return;
	}
	kfree_skb(skb);
}