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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int dummy; } ;
struct inet_request_sock {int /*<<< orphan*/  rmt_addr; int /*<<< orphan*/  loc_addr; } ;
struct dccp_skb_cb {int /*<<< orphan*/  dccpd_seq; int /*<<< orphan*/  dccpd_reset_code; } ;
struct dccp_request_sock {int /*<<< orphan*/  dreq_service; int /*<<< orphan*/  dreq_iss; int /*<<< orphan*/  dreq_isr; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {int /*<<< orphan*/  dccph_req_service; } ;
struct TYPE_5__ {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct TYPE_4__ {int rt_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_INC_STATS_BH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCP_MIB_ATTEMPTFAILS ; 
 int /*<<< orphan*/  DCCP_RESET_CODE_BAD_SERVICE_CODE ; 
 int /*<<< orphan*/  DCCP_RESET_CODE_TOO_BUSY ; 
 struct dccp_skb_cb* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  DCCP_TIMEOUT_INIT ; 
 int RTCF_BROADCAST ; 
 int RTCF_MULTICAST ; 
 scalar_t__ dccp_bad_service_code (struct sock*,int /*<<< orphan*/  const) ; 
 TYPE_3__* dccp_hdr_request (struct sk_buff*) ; 
 scalar_t__ dccp_parse_options (struct sock*,struct dccp_request_sock*,struct sk_buff*) ; 
 scalar_t__ dccp_reqsk_init (struct request_sock*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_request_sock_ops ; 
 struct dccp_request_sock* dccp_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_v4_init_sequence (struct sk_buff*) ; 
 scalar_t__ dccp_v4_send_response (struct sock*,struct request_sock*) ; 
 int /*<<< orphan*/  inet_csk_reqsk_queue_hash_add (struct sock*,struct request_sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ inet_csk_reqsk_queue_is_full (struct sock*) ; 
 int inet_csk_reqsk_queue_young (struct sock*) ; 
 struct request_sock* inet_reqsk_alloc (int /*<<< orphan*/ *) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  reqsk_free (struct request_sock*) ; 
 scalar_t__ security_inet_conn_request (struct sock*,struct sk_buff*,struct request_sock*) ; 
 scalar_t__ sk_acceptq_is_full (struct sock*) ; 
 TYPE_1__* skb_rtable (struct sk_buff*) ; 

int dccp_v4_conn_request(struct sock *sk, struct sk_buff *skb)
{
	struct inet_request_sock *ireq;
	struct request_sock *req;
	struct dccp_request_sock *dreq;
	const __be32 service = dccp_hdr_request(skb)->dccph_req_service;
	struct dccp_skb_cb *dcb = DCCP_SKB_CB(skb);

	/* Never answer to DCCP_PKT_REQUESTs send to broadcast or multicast */
	if (skb_rtable(skb)->rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST))
		return 0;	/* discard, don't send a reset here */

	if (dccp_bad_service_code(sk, service)) {
		dcb->dccpd_reset_code = DCCP_RESET_CODE_BAD_SERVICE_CODE;
		goto drop;
	}
	/*
	 * TW buckets are converted to open requests without
	 * limitations, they conserve resources and peer is
	 * evidently real one.
	 */
	dcb->dccpd_reset_code = DCCP_RESET_CODE_TOO_BUSY;
	if (inet_csk_reqsk_queue_is_full(sk))
		goto drop;

	/*
	 * Accept backlog is full. If we have already queued enough
	 * of warm entries in syn queue, drop request. It is better than
	 * clogging syn queue with openreqs with exponentially increasing
	 * timeout.
	 */
	if (sk_acceptq_is_full(sk) && inet_csk_reqsk_queue_young(sk) > 1)
		goto drop;

	req = inet_reqsk_alloc(&dccp_request_sock_ops);
	if (req == NULL)
		goto drop;

	if (dccp_reqsk_init(req, dccp_sk(sk), skb))
		goto drop_and_free;

	dreq = dccp_rsk(req);
	if (dccp_parse_options(sk, dreq, skb))
		goto drop_and_free;

	if (security_inet_conn_request(sk, skb, req))
		goto drop_and_free;

	ireq = inet_rsk(req);
	ireq->loc_addr = ip_hdr(skb)->daddr;
	ireq->rmt_addr = ip_hdr(skb)->saddr;

	/*
	 * Step 3: Process LISTEN state
	 *
	 * Set S.ISR, S.GSR, S.SWL, S.SWH from packet or Init Cookie
	 *
	 * In fact we defer setting S.GSR, S.SWL, S.SWH to
	 * dccp_create_openreq_child.
	 */
	dreq->dreq_isr	   = dcb->dccpd_seq;
	dreq->dreq_iss	   = dccp_v4_init_sequence(skb);
	dreq->dreq_service = service;

	if (dccp_v4_send_response(sk, req))
		goto drop_and_free;

	inet_csk_reqsk_queue_hash_add(sk, req, DCCP_TIMEOUT_INIT);
	return 0;

drop_and_free:
	reqsk_free(req);
drop:
	DCCP_INC_STATS_BH(DCCP_MIB_ATTEMPTFAILS);
	return -1;
}