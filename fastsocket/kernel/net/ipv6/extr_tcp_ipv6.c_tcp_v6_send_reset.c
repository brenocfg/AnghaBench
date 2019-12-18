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
typedef  scalar_t__ u32 ;
struct tcphdr {int doff; scalar_t__ fin; scalar_t__ syn; int /*<<< orphan*/  seq; int /*<<< orphan*/  ack_seq; scalar_t__ ack; scalar_t__ rst; } ;
struct tcp_md5sig_key {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_unicast_destination (struct sk_buff*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 
 struct tcp_md5sig_key* tcp_v6_md5_do_lookup (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_v6_send_response (struct sk_buff*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tcp_md5sig_key*,int) ; 

__attribute__((used)) static void tcp_v6_send_reset(struct sock *sk, struct sk_buff *skb)
{
	struct tcphdr *th = tcp_hdr(skb);
	u32 seq = 0, ack_seq = 0;
	struct tcp_md5sig_key *key = NULL;

	if (th->rst)
		return;

	if (!ipv6_unicast_destination(skb))
		return;

#ifdef CONFIG_TCP_MD5SIG
	if (sk)
		key = tcp_v6_md5_do_lookup(sk, &ipv6_hdr(skb)->daddr);
#endif

	if (th->ack)
		seq = ntohl(th->ack_seq);
	else
		ack_seq = ntohl(th->seq) + th->syn + th->fin + skb->len -
			  (th->doff << 2);

	tcp_v6_send_response(skb, seq, ack_seq, 0, 0, key, 1);
}