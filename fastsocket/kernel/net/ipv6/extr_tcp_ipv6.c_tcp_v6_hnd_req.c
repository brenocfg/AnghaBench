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
struct tcphdr {scalar_t__ ack; int /*<<< orphan*/  syn; int /*<<< orphan*/  rst; int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 scalar_t__ TCP_TIME_WAIT ; 
 struct sock* __inet6_lookup_established (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 struct sock* cookie_v6_check (struct sock*,struct sk_buff*) ; 
 struct request_sock* inet6_csk_search_req (struct sock*,struct request_sock***,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet6_iif (struct sk_buff*) ; 
 int /*<<< orphan*/  inet_twsk (struct sock*) ; 
 int /*<<< orphan*/  inet_twsk_put (int /*<<< orphan*/ ) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 struct sock* tcp_check_req (struct sock*,struct sk_buff*,struct request_sock*,struct request_sock**) ; 
 int /*<<< orphan*/  tcp_hashinfo ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 

__attribute__((used)) static struct sock *tcp_v6_hnd_req(struct sock *sk,struct sk_buff *skb)
{
	struct request_sock *req, **prev;
	const struct tcphdr *th = tcp_hdr(skb);
	struct sock *nsk;

	/* Find possible connection requests. */
	req = inet6_csk_search_req(sk, &prev, th->source,
				   &ipv6_hdr(skb)->saddr,
				   &ipv6_hdr(skb)->daddr, inet6_iif(skb));
	if (req)
		return tcp_check_req(sk, skb, req, prev);

	nsk = __inet6_lookup_established(sock_net(sk), &tcp_hashinfo,
			&ipv6_hdr(skb)->saddr, th->source,
			&ipv6_hdr(skb)->daddr, ntohs(th->dest), inet6_iif(skb));

	if (nsk) {
		if (nsk->sk_state != TCP_TIME_WAIT) {
			bh_lock_sock(nsk);
			return nsk;
		}
		inet_twsk_put(inet_twsk(nsk));
		return NULL;
	}

#ifdef CONFIG_SYN_COOKIES
	if (!th->rst && !th->syn && th->ack)
		sk = cookie_v6_check(sk, skb);
#endif
	return sk;
}