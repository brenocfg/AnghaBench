#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  users; } ;
struct request_sock {int dummy; } ;
struct TYPE_5__ {scalar_t__ rxohlim; scalar_t__ rxhlim; scalar_t__ rxoinfo; scalar_t__ rxinfo; } ;
struct TYPE_6__ {TYPE_1__ bits; } ;
struct ipv6_pinfo {TYPE_2__ rxopt; } ;
struct inet6_request_sock {int /*<<< orphan*/  iif; int /*<<< orphan*/  rmt_addr; struct sk_buff* pktopts; int /*<<< orphan*/  loc_addr; } ;
struct dccp_skb_cb {int /*<<< orphan*/  dccpd_seq; int /*<<< orphan*/  dccpd_reset_code; } ;
struct dccp_request_sock {int /*<<< orphan*/  dreq_service; int /*<<< orphan*/  dreq_iss; int /*<<< orphan*/  dreq_isr; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_8__ {int /*<<< orphan*/  dccph_req_service; } ;
struct TYPE_7__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_INC_STATS_BH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCP_MIB_ATTEMPTFAILS ; 
 int /*<<< orphan*/  DCCP_RESET_CODE_BAD_SERVICE_CODE ; 
 int /*<<< orphan*/  DCCP_RESET_CODE_TOO_BUSY ; 
 struct dccp_skb_cb* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  DCCP_TIMEOUT_INIT ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dccp6_request_sock_ops ; 
 scalar_t__ dccp_bad_service_code (struct sock*,int /*<<< orphan*/  const) ; 
 TYPE_4__* dccp_hdr_request (struct sk_buff*) ; 
 scalar_t__ dccp_parse_options (struct sock*,struct dccp_request_sock*,struct sk_buff*) ; 
 scalar_t__ dccp_reqsk_init (struct request_sock*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct dccp_request_sock* dccp_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  dccp_sk (struct sock*) ; 
 int dccp_v4_conn_request (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_v6_init_sequence (struct sk_buff*) ; 
 scalar_t__ dccp_v6_send_response (struct sock*,struct request_sock*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_csk_reqsk_queue_hash_add (struct sock*,struct request_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_iif (struct sk_buff*) ; 
 struct request_sock* inet6_reqsk_alloc (int /*<<< orphan*/ *) ; 
 struct inet6_request_sock* inet6_rsk (struct request_sock*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 scalar_t__ inet_csk_reqsk_queue_is_full (struct sock*) ; 
 int inet_csk_reqsk_queue_young (struct sock*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 TYPE_3__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ ipv6_opt_accepted (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_unicast_destination (struct sk_buff*) ; 
 int /*<<< orphan*/  reqsk_free (struct request_sock*) ; 
 scalar_t__ security_inet_conn_request (struct sock*,struct sk_buff*,struct request_sock*) ; 
 scalar_t__ sk_acceptq_is_full (struct sock*) ; 

__attribute__((used)) static int dccp_v6_conn_request(struct sock *sk, struct sk_buff *skb)
{
	struct request_sock *req;
	struct dccp_request_sock *dreq;
	struct inet6_request_sock *ireq6;
	struct ipv6_pinfo *np = inet6_sk(sk);
	const __be32 service = dccp_hdr_request(skb)->dccph_req_service;
	struct dccp_skb_cb *dcb = DCCP_SKB_CB(skb);

	if (skb->protocol == htons(ETH_P_IP))
		return dccp_v4_conn_request(sk, skb);

	if (!ipv6_unicast_destination(skb))
		return 0;	/* discard, don't send a reset here */

	if (dccp_bad_service_code(sk, service)) {
		dcb->dccpd_reset_code = DCCP_RESET_CODE_BAD_SERVICE_CODE;
		goto drop;
	}
	/*
	 * There are no SYN attacks on IPv6, yet...
	 */
	dcb->dccpd_reset_code = DCCP_RESET_CODE_TOO_BUSY;
	if (inet_csk_reqsk_queue_is_full(sk))
		goto drop;

	if (sk_acceptq_is_full(sk) && inet_csk_reqsk_queue_young(sk) > 1)
		goto drop;

	req = inet6_reqsk_alloc(&dccp6_request_sock_ops);
	if (req == NULL)
		goto drop;

	if (dccp_reqsk_init(req, dccp_sk(sk), skb))
		goto drop_and_free;

	dreq = dccp_rsk(req);
	if (dccp_parse_options(sk, dreq, skb))
		goto drop_and_free;

	if (security_inet_conn_request(sk, skb, req))
		goto drop_and_free;

	ireq6 = inet6_rsk(req);
	ipv6_addr_copy(&ireq6->rmt_addr, &ipv6_hdr(skb)->saddr);
	ipv6_addr_copy(&ireq6->loc_addr, &ipv6_hdr(skb)->daddr);

	if (ipv6_opt_accepted(sk, skb) ||
	    np->rxopt.bits.rxinfo || np->rxopt.bits.rxoinfo ||
	    np->rxopt.bits.rxhlim || np->rxopt.bits.rxohlim) {
		atomic_inc(&skb->users);
		ireq6->pktopts = skb;
	}
	ireq6->iif = sk->sk_bound_dev_if;

	/* So that link locals have meaning */
	if (!sk->sk_bound_dev_if &&
	    ipv6_addr_type(&ireq6->rmt_addr) & IPV6_ADDR_LINKLOCAL)
		ireq6->iif = inet6_iif(skb);

	/*
	 * Step 3: Process LISTEN state
	 *
	 *   Set S.ISR, S.GSR, S.SWL, S.SWH from packet or Init Cookie
	 *
	 *   In fact we defer setting S.GSR, S.SWL, S.SWH to
	 *   dccp_create_openreq_child.
	 */
	dreq->dreq_isr	   = dcb->dccpd_seq;
	dreq->dreq_iss	   = dccp_v6_init_sequence(skb);
	dreq->dreq_service = service;

	if (dccp_v6_send_response(sk, req))
		goto drop_and_free;

	inet6_csk_reqsk_queue_hash_add(sk, req, DCCP_TIMEOUT_INIT);
	return 0;

drop_and_free:
	reqsk_free(req);
drop:
	DCCP_INC_STATS_BH(DCCP_MIB_ATTEMPTFAILS);
	return -1;
}