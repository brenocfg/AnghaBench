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
struct request_sock {int dummy; } ;
struct inet_sock {int /*<<< orphan*/  id; int /*<<< orphan*/  mc_ttl; int /*<<< orphan*/  mc_index; int /*<<< orphan*/ * opt; int /*<<< orphan*/  saddr; int /*<<< orphan*/  rcv_saddr; int /*<<< orphan*/  daddr; } ;
struct inet_request_sock {int /*<<< orphan*/ * opt; int /*<<< orphan*/  loc_addr; int /*<<< orphan*/  rmt_addr; } ;
struct dst_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ttl; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_LISTENDROPS ; 
 int /*<<< orphan*/  LINUX_MIB_LISTENOVERFLOWS ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __inet_hash_nolisten (struct sock*) ; 
 scalar_t__ __inet_inherit_port (struct sock*,struct sock*) ; 
 struct sock* dccp_create_openreq_child (struct sock*,struct request_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_sync_mss (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 struct dst_entry* inet_csk_route_req (struct sock*,struct request_sock*) ; 
 int /*<<< orphan*/  inet_iif (struct sk_buff*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ sk_acceptq_is_full (struct sock*) ; 
 int /*<<< orphan*/  sk_setup_caps (struct sock*,struct dst_entry*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

struct sock *dccp_v4_request_recv_sock(struct sock *sk, struct sk_buff *skb,
				       struct request_sock *req,
				       struct dst_entry *dst)
{
	struct inet_request_sock *ireq;
	struct inet_sock *newinet;
	struct sock *newsk;

	if (sk_acceptq_is_full(sk))
		goto exit_overflow;

	if (dst == NULL && (dst = inet_csk_route_req(sk, req)) == NULL)
		goto exit;

	newsk = dccp_create_openreq_child(sk, req, skb);
	if (newsk == NULL)
		goto exit_nonewsk;

	sk_setup_caps(newsk, dst);

	newinet		   = inet_sk(newsk);
	ireq		   = inet_rsk(req);
	newinet->daddr	   = ireq->rmt_addr;
	newinet->rcv_saddr = ireq->loc_addr;
	newinet->saddr	   = ireq->loc_addr;
	newinet->opt	   = ireq->opt;
	ireq->opt	   = NULL;
	newinet->mc_index  = inet_iif(skb);
	newinet->mc_ttl	   = ip_hdr(skb)->ttl;
	newinet->id	   = jiffies;

	dccp_sync_mss(newsk, dst_mtu(dst));

	if (__inet_inherit_port(sk, newsk) < 0) {
		sock_put(newsk);
		goto exit;
	}
	__inet_hash_nolisten(newsk);

	return newsk;

exit_overflow:
	NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_LISTENOVERFLOWS);
exit_nonewsk:
	dst_release(dst);
exit:
	NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_LISTENDROPS);
	return NULL;
}