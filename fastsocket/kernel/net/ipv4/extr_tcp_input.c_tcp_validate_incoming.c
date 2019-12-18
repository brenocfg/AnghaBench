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
struct tcphdr {scalar_t__ syn; scalar_t__ rst; } ;
struct TYPE_3__ {scalar_t__ saw_tstamp; } ;
struct tcp_sock {scalar_t__ rcv_nxt; TYPE_1__ rx_opt; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {scalar_t__ seq; int /*<<< orphan*/  end_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_PAWSESTABREJECTED ; 
 int /*<<< orphan*/  LINUX_MIB_TCPSYNCHALLENGE ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_MIB_INERRS ; 
 TYPE_2__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ tcp_fast_parse_options (struct sk_buff*,struct tcphdr*,struct tcp_sock*) ; 
 scalar_t__ tcp_paws_discard (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_reset (struct sock*) ; 
 int /*<<< orphan*/  tcp_send_challenge_ack (struct sock*) ; 
 int /*<<< orphan*/  tcp_send_dupack (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_sequence (struct tcp_sock*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static bool tcp_validate_incoming(struct sock *sk, struct sk_buff *skb,
			      struct tcphdr *th, int syn_inerr)
{
	struct tcp_sock *tp = tcp_sk(sk);

	/* RFC1323: H1. Apply PAWS check first. */
	if (tcp_fast_parse_options(skb, th, tp) && tp->rx_opt.saw_tstamp &&
	    tcp_paws_discard(sk, skb)) {
		if (!th->rst) {
			NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_PAWSESTABREJECTED);
			tcp_send_dupack(sk, skb);
			goto discard;
		}
		/* Reset is accepted even if it did not pass PAWS. */
	}

	/* Step 1: check sequence number */
	if (!tcp_sequence(tp, TCP_SKB_CB(skb)->seq, TCP_SKB_CB(skb)->end_seq)) {
		/* RFC793, page 37: "In all states except SYN-SENT, all reset
		 * (RST) segments are validated by checking their SEQ-fields."
		 * And page 69: "If an incoming segment is not acceptable,
		 * an acknowledgment should be sent in reply (unless the RST
		 * bit is set, if so drop the segment and return)".
		 */
		if (!th->rst) {
			if (th->syn)
				goto syn_challenge;
			tcp_send_dupack(sk, skb);
		}
		goto discard;
	}

	/* Step 2: check RST bit */
	if (th->rst) {
		/* RFC 5961 3.2 :
		 * If sequence number exactly matches RCV.NXT, then
		 *     RESET the connection
		 * else
		 *     Send a challenge ACK
		 */
		if (TCP_SKB_CB(skb)->seq == tp->rcv_nxt)
			tcp_reset(sk);
		else
			tcp_send_challenge_ack(sk);
		goto discard;
	}

	/* step 3: check security and precedence [ignored] */

	/* step 4: Check for a SYN
	 * RFC 5691 4.2 : Send a challenge ack
	 */
	if (th->syn) {
syn_challenge:
		if (syn_inerr)
			TCP_INC_STATS_BH(sock_net(sk), TCP_MIB_INERRS);
		NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPSYNCHALLENGE);
		tcp_send_challenge_ack(sk);
		goto discard;
	}

	return true;

discard:
	__kfree_skb(skb);
	return false;
}