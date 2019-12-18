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
struct tcphdr {int /*<<< orphan*/  check; } ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  csum; int /*<<< orphan*/  len; } ;
struct request_sock {int dummy; } ;
struct inet_request_sock {int /*<<< orphan*/  opt; int /*<<< orphan*/  rmt_addr; int /*<<< orphan*/  loc_addr; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  csum_partial (struct tcphdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 struct dst_entry* inet_csk_route_req (struct sock*,struct request_sock*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 int ip_build_and_send_pkt (struct sk_buff*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int net_xmit_eval (int) ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 
 struct sk_buff* tcp_make_synack (struct sock*,struct dst_entry*,struct request_sock*) ; 
 int /*<<< orphan*/  tcp_v4_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __tcp_v4_send_synack(struct sock *sk, struct request_sock *req,
				struct dst_entry *dst)
{
	const struct inet_request_sock *ireq = inet_rsk(req);
	int err = -1;
	struct sk_buff * skb;

	/* First, grab a route. */
	if (!dst && (dst = inet_csk_route_req(sk, req)) == NULL)
		return -1;

	skb = tcp_make_synack(sk, dst, req);

	if (skb) {
		struct tcphdr *th = tcp_hdr(skb);

		th->check = tcp_v4_check(skb->len,
					 ireq->loc_addr,
					 ireq->rmt_addr,
					 csum_partial(th, skb->len,
						      skb->csum));

		err = ip_build_and_send_pkt(skb, sk, ireq->loc_addr,
					    ireq->rmt_addr,
					    ireq->opt);
		err = net_xmit_eval(err);
	}

	dst_release(dst);
	return err;
}