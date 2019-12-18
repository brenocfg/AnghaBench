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
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  rxhash; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_CHECK_TIMER (struct sock*) ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  TCP_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  TCP_MIB_INERRS ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_rps_save_rxhash (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_checksum_complete (struct sk_buff*) ; 
 scalar_t__ tcp_child_process (struct sock*,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_hdr (struct sk_buff*) ; 
 scalar_t__ tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ tcp_rcv_established (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tcp_rcv_state_process (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sock* tcp_v4_hnd_req (struct sock*,struct sk_buff*) ; 
 scalar_t__ tcp_v4_inbound_md5_hash (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_v4_send_reset (struct sock*,struct sk_buff*) ; 

int tcp_v4_do_rcv(struct sock *sk, struct sk_buff *skb)
{
	struct sock *rsk;
#ifdef CONFIG_TCP_MD5SIG
	/*
	 * We really want to reject the packet as early as possible
	 * if:
	 *  o We're expecting an MD5'd packet and this is no MD5 tcp option
	 *  o There is an MD5 option and we're not expecting one
	 */
	if (tcp_v4_inbound_md5_hash(sk, skb))
		goto discard;
#endif

	if (sk->sk_state == TCP_ESTABLISHED) { /* Fast path */
		TCP_CHECK_TIMER(sk);
		if (tcp_rcv_established(sk, skb, tcp_hdr(skb), skb->len)) {
			rsk = sk;
			goto reset;
		}
		TCP_CHECK_TIMER(sk);
		return 0;
	}

	if (skb->len < tcp_hdrlen(skb) || tcp_checksum_complete(skb))
		goto csum_err;

	if (sk->sk_state == TCP_LISTEN) {
		struct sock *nsk = tcp_v4_hnd_req(sk, skb);
		if (!nsk)
			goto discard;

		if (nsk != sk) {
			sock_rps_save_rxhash(nsk, skb->rxhash);
			if (tcp_child_process(sk, nsk, skb)) {
				rsk = nsk;
				goto reset;
			}
			return 0;
		}
	}

	TCP_CHECK_TIMER(sk);
	if (tcp_rcv_state_process(sk, skb, tcp_hdr(skb), skb->len)) {
		rsk = sk;
		goto reset;
	}
	TCP_CHECK_TIMER(sk);
	return 0;

reset:
	tcp_v4_send_reset(rsk, skb);
discard:
	kfree_skb(skb);
	/* Be careful here. If this function gets more complicated and
	 * gcc suffers from register pressure on the x86, sk (in %ebx)
	 * might be destroyed here. This current version compiles correctly,
	 * but you have been warned.
	 */
	return 0;

csum_err:
	TCP_INC_STATS_BH(sock_net(sk), TCP_MIB_INERRS);
	goto discard;
}