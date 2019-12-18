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
struct tcp_sock {scalar_t__ snd_una; scalar_t__ snd_cwnd; scalar_t__ srtt; int sacked_out; scalar_t__ max_window; scalar_t__ snd_nxt; scalar_t__ fackets_out; int packets_out; scalar_t__ frto_highmark; scalar_t__ frto_counter; int /*<<< orphan*/  rcv_tstamp; int /*<<< orphan*/  mss_cache; int /*<<< orphan*/  bytes_acked; } ;
struct sock {int /*<<< orphan*/  sk_dst_cache; scalar_t__ sk_err_soft; } ;
struct sk_buff {int dummy; } ;
struct inet_connection_sock {scalar_t__ icsk_ca_state; scalar_t__ icsk_probes_out; } ;
struct TYPE_2__ {scalar_t__ seq; scalar_t__ ack_seq; scalar_t__ end_seq; scalar_t__ sacked; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_EVENT_FAST_ACK ; 
 int /*<<< orphan*/  CA_EVENT_SLOW_ACK ; 
 int FLAG_DATA ; 
 int FLAG_DATA_ACKED ; 
 int FLAG_DSACKING_ACK ; 
 int FLAG_ECE ; 
 int FLAG_FORWARD_PROGRESS ; 
 int FLAG_NOT_DUP ; 
 int FLAG_SLOWPATH ; 
 int FLAG_SND_UNA_ADVANCED ; 
 int FLAG_WIN_UPDATE ; 
 int /*<<< orphan*/  LINUX_MIB_TCPHPACKS ; 
 int /*<<< orphan*/  LINUX_MIB_TCPPUREACKS ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_DEBUG (struct sock*,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ TCP_CA_CWR ; 
 scalar_t__ TCP_CA_Loss ; 
 scalar_t__ TCP_ECN_rcv_ecn_echo (struct tcp_sock*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ after (scalar_t__,scalar_t__) ; 
 scalar_t__ before (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dst_confirm (int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ sysctl_tcp_abc ; 
 scalar_t__ tcp_ack_is_dubious (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_ack_probe (struct sock*) ; 
 int tcp_ack_update_window (struct sock*,struct sk_buff*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tcp_ca_event (struct sock*,int /*<<< orphan*/ ) ; 
 int tcp_clean_rtx_queue (struct sock*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tcp_cong_avoid (struct sock*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tcp_fastretrans_alert (struct sock*,int,int,int,int) ; 
 int /*<<< orphan*/  tcp_hdr (struct sk_buff*) ; 
 scalar_t__ tcp_may_raise_cwnd (struct sock*,int) ; 
 scalar_t__ tcp_packets_in_flight (struct tcp_sock*) ; 
 int tcp_process_frto (struct sock*,int) ; 
 int tcp_sacktag_write_queue (struct sock*,struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  tcp_send_challenge_ack (struct sock*) ; 
 scalar_t__ tcp_send_head (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_time_stamp ; 
 int /*<<< orphan*/  tcp_update_pacing_rate (struct sock*) ; 
 int /*<<< orphan*/  tcp_update_wl (struct tcp_sock*,scalar_t__) ; 

__attribute__((used)) static int tcp_ack(struct sock *sk, struct sk_buff *skb, int flag)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	u32 prior_snd_una = tp->snd_una;
	u32 ack_seq = TCP_SKB_CB(skb)->seq;
	u32 ack = TCP_SKB_CB(skb)->ack_seq;
	bool is_dupack = false;
	u32 prior_in_flight, prior_cwnd = tp->snd_cwnd, prior_rtt = tp->srtt;
	u32 prior_fackets;
	int prior_packets;
	int prior_sacked = tp->sacked_out;
	int pkts_acked = 0;
	int newly_acked_sacked = 0;
	int frto_cwnd = 0;

	/* If the ack is older than previous acks
	 * then we can probably ignore it.
	 */
	if (before(ack, prior_snd_una)) {
		/* RFC 5961 5.2 [Blind Data Injection Attack].[Mitigation] */
		if (before(ack, prior_snd_una - tp->max_window)) {
			tcp_send_challenge_ack(sk);
			return -1;
		}
		goto old_ack;
	}

	/* If the ack includes data we haven't sent yet, discard
	 * this segment (RFC793 Section 3.9).
	 */
	if (after(ack, tp->snd_nxt))
		goto invalid_ack;

	if (after(ack, prior_snd_una))
		flag |= FLAG_SND_UNA_ADVANCED;

	if (sysctl_tcp_abc) {
		if (icsk->icsk_ca_state < TCP_CA_CWR)
			tp->bytes_acked += ack - prior_snd_una;
		else if (icsk->icsk_ca_state == TCP_CA_Loss)
			/* we assume just one segment left network */
			tp->bytes_acked += min(ack - prior_snd_una,
					       tp->mss_cache);
	}

	prior_fackets = tp->fackets_out;
	prior_in_flight = tcp_packets_in_flight(tp);

	if (!(flag & FLAG_SLOWPATH) && after(ack, prior_snd_una)) {
		/* Window is constant, pure forward advance.
		 * No more checks are required.
		 * Note, we use the fact that SND.UNA>=SND.WL2.
		 */
		tcp_update_wl(tp, ack_seq);
		tp->snd_una = ack;
		flag |= FLAG_WIN_UPDATE;

		tcp_ca_event(sk, CA_EVENT_FAST_ACK);

		NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPHPACKS);
	} else {
		if (ack_seq != TCP_SKB_CB(skb)->end_seq)
			flag |= FLAG_DATA;
		else
			NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPPUREACKS);

		flag |= tcp_ack_update_window(sk, skb, ack, ack_seq);

		if (TCP_SKB_CB(skb)->sacked)
			flag |= tcp_sacktag_write_queue(sk, skb, prior_snd_una);

		if (TCP_ECN_rcv_ecn_echo(tp, tcp_hdr(skb)))
			flag |= FLAG_ECE;

		tcp_ca_event(sk, CA_EVENT_SLOW_ACK);
	}

	/* We passed data and got it acked, remove any soft error
	 * log. Something worked...
	 */
	sk->sk_err_soft = 0;
	icsk->icsk_probes_out = 0;
	tp->rcv_tstamp = tcp_time_stamp;
	prior_packets = tp->packets_out;
	if (!prior_packets)
		goto no_queue;

	/* See if we can take anything off of the retransmit queue. */
	flag |= tcp_clean_rtx_queue(sk, prior_fackets, prior_snd_una);

	pkts_acked = prior_packets - tp->packets_out;
	newly_acked_sacked = (prior_packets - prior_sacked) -
			     (tp->packets_out - tp->sacked_out);

	if (tp->frto_counter)
		frto_cwnd = tcp_process_frto(sk, flag);
	/* Guarantee sacktag reordering detection against wrap-arounds */
	if (before(tp->frto_highmark, tp->snd_una))
		tp->frto_highmark = 0;

	if (tcp_ack_is_dubious(sk, flag)) {
		/* Advance CWND, if state allows this. */
		if ((flag & FLAG_DATA_ACKED) && !frto_cwnd &&
		    tcp_may_raise_cwnd(sk, flag))
			tcp_cong_avoid(sk, ack, prior_in_flight);
		is_dupack = !(flag & (FLAG_SND_UNA_ADVANCED | FLAG_NOT_DUP));
		tcp_fastretrans_alert(sk, pkts_acked, newly_acked_sacked,
				      is_dupack, flag);
	} else {
		if ((flag & FLAG_DATA_ACKED) && !frto_cwnd)
			tcp_cong_avoid(sk, ack, prior_in_flight);
	}

	if ((flag & FLAG_FORWARD_PROGRESS) || !(flag & FLAG_NOT_DUP))
		dst_confirm(sk->sk_dst_cache);

	if (tp->srtt != prior_rtt || tp->snd_cwnd != prior_cwnd)
		tcp_update_pacing_rate(sk);
	return 1;

no_queue:
	/* If data was DSACKed, see if we can undo a cwnd reduction. */
	if (flag & FLAG_DSACKING_ACK)
		tcp_fastretrans_alert(sk, pkts_acked, newly_acked_sacked,
				      is_dupack, flag);
	/* If this ack opens up a zero window, clear backoff.  It was
	 * being used to time the probes, and is probably far higher than
	 * it needs to be for normal retransmission.
	 */
	if (tcp_send_head(sk))
		tcp_ack_probe(sk);
	return 1;

invalid_ack:
	SOCK_DEBUG(sk, "Ack %u after %u:%u\n", ack, tp->snd_una, tp->snd_nxt);
	return -1;

old_ack:
	/* If data was SACKed, tag it and see if we should send more data.
	 * If data was DSACKed, see if we can undo a cwnd reduction.
	 */
	if (TCP_SKB_CB(skb)->sacked) {
		flag |= tcp_sacktag_write_queue(sk, skb, prior_snd_una);
		newly_acked_sacked = tp->sacked_out - prior_sacked;
		tcp_fastretrans_alert(sk, pkts_acked, newly_acked_sacked,
				      is_dupack, flag);
	}

	SOCK_DEBUG(sk, "Ack %u before %u:%u\n", ack, tp->snd_una, tp->snd_nxt);
	return 0;
}