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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct rt0_hdr {struct in6_addr* addr; } ;
struct request_sock {int dummy; } ;
struct ipv6_txoptions {int /*<<< orphan*/  tot_len; int /*<<< orphan*/ * srcrt; } ;
struct ipv6_pinfo {struct ipv6_txoptions* opt; } ;
struct in6_addr {int dummy; } ;
struct inet6_request_sock {struct in6_addr rmt_addr; struct in6_addr loc_addr; int /*<<< orphan*/  iif; } ;
struct flowi {struct in6_addr fl6_dst; int /*<<< orphan*/  fl_ip_sport; int /*<<< orphan*/  fl_ip_dport; int /*<<< orphan*/  oif; scalar_t__ fl6_flowlabel; struct in6_addr fl6_src; int /*<<< orphan*/  proto; } ;
struct dst_entry {int dummy; } ;
struct dccp_hdr {int /*<<< orphan*/  dccph_checksum; } ;
typedef  int /*<<< orphan*/  fl ;
struct TYPE_2__ {int /*<<< orphan*/  loc_port; int /*<<< orphan*/  rmt_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_DCCP ; 
 struct dccp_hdr* dccp_hdr (struct sk_buff*) ; 
 struct sk_buff* dccp_make_response (struct sock*,struct dst_entry*,struct request_sock*) ; 
 int /*<<< orphan*/  dccp_v6_csum_finish (struct sk_buff*,struct in6_addr*,struct in6_addr*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 struct inet6_request_sock* inet6_rsk (struct request_sock*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 TYPE_1__* inet_rsk (struct request_sock*) ; 
 int ip6_dst_lookup (struct sock*,struct dst_entry**,struct flowi*) ; 
 int ip6_xmit (struct sock*,struct sk_buff*,struct flowi*,struct ipv6_txoptions*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_addr_copy (struct in6_addr*,struct in6_addr*) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 int net_xmit_eval (int) ; 
 int /*<<< orphan*/  security_req_classify_flow (struct request_sock*,struct flowi*) ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,struct ipv6_txoptions*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int xfrm_lookup (int /*<<< orphan*/ ,struct dst_entry**,struct flowi*,struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dccp_v6_send_response(struct sock *sk, struct request_sock *req)
{
	struct inet6_request_sock *ireq6 = inet6_rsk(req);
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct sk_buff *skb;
	struct ipv6_txoptions *opt = NULL;
	struct in6_addr *final_p = NULL, final;
	struct flowi fl;
	int err = -1;
	struct dst_entry *dst;

	memset(&fl, 0, sizeof(fl));
	fl.proto = IPPROTO_DCCP;
	ipv6_addr_copy(&fl.fl6_dst, &ireq6->rmt_addr);
	ipv6_addr_copy(&fl.fl6_src, &ireq6->loc_addr);
	fl.fl6_flowlabel = 0;
	fl.oif = ireq6->iif;
	fl.fl_ip_dport = inet_rsk(req)->rmt_port;
	fl.fl_ip_sport = inet_rsk(req)->loc_port;
	security_req_classify_flow(req, &fl);

	opt = np->opt;

	if (opt != NULL && opt->srcrt != NULL) {
		const struct rt0_hdr *rt0 = (struct rt0_hdr *)opt->srcrt;

		ipv6_addr_copy(&final, &fl.fl6_dst);
		ipv6_addr_copy(&fl.fl6_dst, rt0->addr);
		final_p = &final;
	}

	err = ip6_dst_lookup(sk, &dst, &fl);
	if (err)
		goto done;

	if (final_p)
		ipv6_addr_copy(&fl.fl6_dst, final_p);

	err = xfrm_lookup(sock_net(sk), &dst, &fl, sk, 0);
	if (err < 0)
		goto done;

	skb = dccp_make_response(sk, dst, req);
	if (skb != NULL) {
		struct dccp_hdr *dh = dccp_hdr(skb);

		dh->dccph_checksum = dccp_v6_csum_finish(skb,
							 &ireq6->loc_addr,
							 &ireq6->rmt_addr);
		ipv6_addr_copy(&fl.fl6_dst, &ireq6->rmt_addr);
		err = ip6_xmit(sk, skb, &fl, opt, 0);
		err = net_xmit_eval(err);
	}

done:
	if (opt != NULL && opt != np->opt)
		sock_kfree_s(sk, opt, opt->tot_len);
	dst_release(dst);
	return err;
}