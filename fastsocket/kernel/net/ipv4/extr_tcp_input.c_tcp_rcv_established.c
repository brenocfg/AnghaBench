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
struct tcphdr {int doff; scalar_t__ ack; } ;
struct TYPE_5__ {unsigned int len; scalar_t__ task; } ;
struct TYPE_4__ {scalar_t__ ts_recent; scalar_t__ rcv_tsval; scalar_t__ saw_tstamp; } ;
struct tcp_sock {int pred_flags; scalar_t__ rcv_nxt; int tcp_header_len; scalar_t__ rcv_wup; scalar_t__ copied_seq; scalar_t__ snd_una; TYPE_2__ ucopy; TYPE_1__ rx_opt; int /*<<< orphan*/  snd_nxt; } ;
struct sock {int sk_forward_alloc; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sk_async_wait_queue; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {scalar_t__ truesize; int /*<<< orphan*/  len; } ;
typedef  scalar_t__ s32 ;
struct TYPE_6__ {scalar_t__ seq; scalar_t__ ack_seq; scalar_t__ end_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_DATA ; 
 int /*<<< orphan*/  FLAG_SLOWPATH ; 
 int /*<<< orphan*/  LINUX_MIB_TCPHPHITS ; 
 int /*<<< orphan*/  LINUX_MIB_TCPHPHITSTOUSER ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int TCPOLEN_TSTAMP_ALIGNED ; 
 int TCP_HP_BITS ; 
 int /*<<< orphan*/  TCP_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_MIB_INERRS ; 
 TYPE_3__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  __tcp_ack_snd_check (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  after (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ current ; 
 int /*<<< orphan*/  inet_csk_ack_scheduled (struct sock*) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_ack (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_ack_snd_check (struct sock*) ; 
 scalar_t__ tcp_checksum_complete_user (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_cleanup_rbuf (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_copy_to_iovec (struct sock*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  tcp_data_queue (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_data_snd_check (struct sock*) ; 
 scalar_t__ tcp_dma_try_early_copy (struct sock*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  tcp_event_data_recv (struct sock*,struct sk_buff*) ; 
 int tcp_flag_word (struct tcphdr*) ; 
 int /*<<< orphan*/  tcp_parse_aligned_timestamp (struct tcp_sock*,struct tcphdr*) ; 
 int /*<<< orphan*/  tcp_rcv_rtt_measure_ts (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_replace_ts_recent (struct tcp_sock*,scalar_t__) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_store_ts_recent (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_urg (struct sock*,struct sk_buff*,struct tcphdr*) ; 
 int /*<<< orphan*/  tcp_validate_incoming (struct sock*,struct sk_buff*,struct tcphdr*,int) ; 

int tcp_rcv_established(struct sock *sk, struct sk_buff *skb,
			struct tcphdr *th, unsigned len)
{
	struct tcp_sock *tp = tcp_sk(sk);

	/*
	 *	Header prediction.
	 *	The code loosely follows the one in the famous
	 *	"30 instruction TCP receive" Van Jacobson mail.
	 *
	 *	Van's trick is to deposit buffers into socket queue
	 *	on a device interrupt, to call tcp_recv function
	 *	on the receive process context and checksum and copy
	 *	the buffer to user space. smart...
	 *
	 *	Our current scheme is not silly either but we take the
	 *	extra cost of the net_bh soft interrupt processing...
	 *	We do checksum and copy also but from device to kernel.
	 */

	tp->rx_opt.saw_tstamp = 0;

	/*	pred_flags is 0xS?10 << 16 + snd_wnd
	 *	if header_prediction is to be made
	 *	'S' will always be tp->tcp_header_len >> 2
	 *	'?' will be 0 for the fast path, otherwise pred_flags is 0 to
	 *  turn it off	(when there are holes in the receive
	 *	 space for instance)
	 *	PSH flag is ignored.
	 */

	if ((tcp_flag_word(th) & TCP_HP_BITS) == tp->pred_flags &&
	    TCP_SKB_CB(skb)->seq == tp->rcv_nxt &&
	    !after(TCP_SKB_CB(skb)->ack_seq, tp->snd_nxt)) {
		int tcp_header_len = tp->tcp_header_len;

		/* Timestamp header prediction: tcp_header_len
		 * is automatically equal to th->doff*4 due to pred_flags
		 * match.
		 */

		/* Check timestamp */
		if (tcp_header_len == sizeof(struct tcphdr) + TCPOLEN_TSTAMP_ALIGNED) {
			/* No? Slow path! */
			if (!tcp_parse_aligned_timestamp(tp, th))
				goto slow_path;

			/* If PAWS failed, check it more carefully in slow path */
			if ((s32)(tp->rx_opt.rcv_tsval - tp->rx_opt.ts_recent) < 0)
				goto slow_path;

			/* DO NOT update ts_recent here, if checksum fails
			 * and timestamp was corrupted part, it will result
			 * in a hung connection since we will drop all
			 * future packets due to the PAWS test.
			 */
		}

		if (len <= tcp_header_len) {
			/* Bulk data transfer: sender */
			if (len == tcp_header_len) {
				/* Predicted packet is in window by definition.
				 * seq == rcv_nxt and rcv_wup <= rcv_nxt.
				 * Hence, check seq<=rcv_wup reduces to:
				 */
				if (tcp_header_len ==
				    (sizeof(struct tcphdr) + TCPOLEN_TSTAMP_ALIGNED) &&
				    tp->rcv_nxt == tp->rcv_wup)
					tcp_store_ts_recent(tp);

				/* We know that such packets are checksummed
				 * on entry.
				 */
				tcp_ack(sk, skb, 0);
				__kfree_skb(skb);
				tcp_data_snd_check(sk);
				return 0;
			} else { /* Header too small */
				TCP_INC_STATS_BH(sock_net(sk), TCP_MIB_INERRS);
				goto discard;
			}
		} else {
			int eaten = 0;
			int copied_early = 0;

			if (tp->copied_seq == tp->rcv_nxt &&
			    len - tcp_header_len <= tp->ucopy.len) {
#ifdef CONFIG_NET_DMA
				if (tcp_dma_try_early_copy(sk, skb, tcp_header_len)) {
					copied_early = 1;
					eaten = 1;
				}
#endif
				if (tp->ucopy.task == current &&
				    sock_owned_by_user(sk) && !copied_early) {
					__set_current_state(TASK_RUNNING);

					if (!tcp_copy_to_iovec(sk, skb, tcp_header_len))
						eaten = 1;
				}
				if (eaten) {
					/* Predicted packet is in window by definition.
					 * seq == rcv_nxt and rcv_wup <= rcv_nxt.
					 * Hence, check seq<=rcv_wup reduces to:
					 */
					if (tcp_header_len ==
					    (sizeof(struct tcphdr) +
					     TCPOLEN_TSTAMP_ALIGNED) &&
					    tp->rcv_nxt == tp->rcv_wup)
						tcp_store_ts_recent(tp);

					tcp_rcv_rtt_measure_ts(sk, skb);

					__skb_pull(skb, tcp_header_len);
					tp->rcv_nxt = TCP_SKB_CB(skb)->end_seq;
					NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPHPHITSTOUSER);
				}
				if (copied_early)
					tcp_cleanup_rbuf(sk, skb->len);
			}
			if (!eaten) {
				if (tcp_checksum_complete_user(sk, skb))
					goto csum_error;

				/* Predicted packet is in window by definition.
				 * seq == rcv_nxt and rcv_wup <= rcv_nxt.
				 * Hence, check seq<=rcv_wup reduces to:
				 */
				if (tcp_header_len ==
				    (sizeof(struct tcphdr) + TCPOLEN_TSTAMP_ALIGNED) &&
				    tp->rcv_nxt == tp->rcv_wup)
					tcp_store_ts_recent(tp);

				tcp_rcv_rtt_measure_ts(sk, skb);

				if ((int)skb->truesize > sk->sk_forward_alloc)
					goto step5;

				NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPHPHITS);

				/* Bulk data transfer: receiver */
				__skb_pull(skb, tcp_header_len);
				__skb_queue_tail(&sk->sk_receive_queue, skb);
				skb_set_owner_r(skb, sk);
				tp->rcv_nxt = TCP_SKB_CB(skb)->end_seq;
			}

			tcp_event_data_recv(sk, skb);

			if (TCP_SKB_CB(skb)->ack_seq != tp->snd_una) {
				/* Well, only one small jumplet in fast path... */
				tcp_ack(sk, skb, FLAG_DATA);
				tcp_data_snd_check(sk);
				if (!inet_csk_ack_scheduled(sk))
					goto no_ack;
			}

			if (!copied_early || tp->rcv_nxt != tp->rcv_wup)
				__tcp_ack_snd_check(sk, 0);
no_ack:
#ifdef CONFIG_NET_DMA
			if (copied_early)
				__skb_queue_tail(&sk->sk_async_wait_queue, skb);
			else
#endif
			if (eaten)
				__kfree_skb(skb);
			else
				sk->sk_data_ready(sk, 0);
			return 0;
		}
	}

slow_path:
	if (len < (th->doff << 2) || tcp_checksum_complete_user(sk, skb))
		goto csum_error;

	/*
	 *	Standard slow path.
	 */

	if (!tcp_validate_incoming(sk, skb, th, 1))
		return 0;

step5:
	if (th->ack && tcp_ack(sk, skb, FLAG_SLOWPATH) < 0)
		goto discard;

	/* ts_recent update must be made after we are sure that the packet
	 * is in window.
	 */
	tcp_replace_ts_recent(tp, TCP_SKB_CB(skb)->seq);

	tcp_rcv_rtt_measure_ts(sk, skb);

	/* Process urgent data. */
	tcp_urg(sk, skb, th);

	/* step 7: process the segment text */
	tcp_data_queue(sk, skb);

	tcp_data_snd_check(sk);
	tcp_ack_snd_check(sk);
	return 0;

csum_error:
	TCP_INC_STATS_BH(sock_net(sk), TCP_MIB_INERRS);

discard:
	__kfree_skb(skb);
	return 0;
}