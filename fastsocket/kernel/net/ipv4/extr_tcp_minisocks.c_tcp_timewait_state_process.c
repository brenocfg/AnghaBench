#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tcphdr {int doff; scalar_t__ ack; int /*<<< orphan*/  rst; scalar_t__ syn; int /*<<< orphan*/  fin; } ;
struct tcp_timewait_sock {scalar_t__ tw_rcv_nxt; scalar_t__ tw_rcv_wnd; scalar_t__ tw_snd_nxt; scalar_t__ tw_ts_recent; void* tw_ts_recent_stamp; } ;
struct tcp_options_received {scalar_t__ rcv_tsval; scalar_t__ saw_tstamp; void* ts_recent_stamp; scalar_t__ ts_recent; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct inet_timewait_sock {scalar_t__ tw_substate; scalar_t__ tw_family; int /*<<< orphan*/  tw_timeout; } ;
typedef  scalar_t__ s32 ;
typedef  enum tcp_tw_status { ____Placeholder_tcp_tw_status } tcp_tw_status ;
struct TYPE_6__ {scalar_t__ seq; scalar_t__ end_seq; scalar_t__ when; } ;
struct TYPE_5__ {scalar_t__ sysctl_tw_recycle; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  LINUX_MIB_PAWSESTABREJECTED ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TCP_FIN_WAIT2 ; 
 TYPE_4__* TCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  TCP_TIMEWAIT_LEN ; 
 scalar_t__ TCP_TIME_WAIT ; 
 int TCP_TW_ACK ; 
 int TCP_TW_RST ; 
 int TCP_TW_SUCCESS ; 
 int TCP_TW_SYN ; 
 scalar_t__ after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  before (scalar_t__,scalar_t__) ; 
 void* get_seconds () ; 
 int /*<<< orphan*/  inet_twsk_deschedule (struct inet_timewait_sock*,TYPE_1__*) ; 
 int /*<<< orphan*/  inet_twsk_put (struct inet_timewait_sock*) ; 
 int /*<<< orphan*/  inet_twsk_schedule (struct inet_timewait_sock*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl_tcp_rfc1337 ; 
 TYPE_1__ tcp_death_row ; 
 int /*<<< orphan*/  tcp_in_window (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tcp_parse_options (struct sk_buff*,struct tcp_options_received*,int /*<<< orphan*/ ) ; 
 int tcp_paws_reject (struct tcp_options_received*,int /*<<< orphan*/ ) ; 
 struct tcp_timewait_sock* tcp_twsk (struct sock*) ; 
 scalar_t__ tcp_v4_tw_remember_stamp (struct inet_timewait_sock*) ; 
 int /*<<< orphan*/  twsk_net (struct inet_timewait_sock*) ; 

enum tcp_tw_status
tcp_timewait_state_process(struct inet_timewait_sock *tw, struct sk_buff *skb,
			   const struct tcphdr *th)
{
	struct tcp_timewait_sock *tcptw = tcp_twsk((struct sock *)tw);
	struct tcp_options_received tmp_opt;
	int paws_reject = 0;

	tmp_opt.saw_tstamp = 0;
	if (th->doff > (sizeof(*th) >> 2) && tcptw->tw_ts_recent_stamp) {
		tcp_parse_options(skb, &tmp_opt, 0);

		if (tmp_opt.saw_tstamp) {
			tmp_opt.ts_recent	= tcptw->tw_ts_recent;
			tmp_opt.ts_recent_stamp	= tcptw->tw_ts_recent_stamp;
			paws_reject = tcp_paws_reject(&tmp_opt, th->rst);
		}
	}

	if (tw->tw_substate == TCP_FIN_WAIT2) {
		/* Just repeat all the checks of tcp_rcv_state_process() */

		/* Out of window, send ACK */
		if (paws_reject ||
		    !tcp_in_window(TCP_SKB_CB(skb)->seq, TCP_SKB_CB(skb)->end_seq,
				   tcptw->tw_rcv_nxt,
				   tcptw->tw_rcv_nxt + tcptw->tw_rcv_wnd))
			return TCP_TW_ACK;

		if (th->rst)
			goto kill;

		if (th->syn && !before(TCP_SKB_CB(skb)->seq, tcptw->tw_rcv_nxt))
			goto kill_with_rst;

		/* Dup ACK? */
		if (!th->ack ||
		    !after(TCP_SKB_CB(skb)->end_seq, tcptw->tw_rcv_nxt) ||
		    TCP_SKB_CB(skb)->end_seq == TCP_SKB_CB(skb)->seq) {
			inet_twsk_put(tw);
			return TCP_TW_SUCCESS;
		}

		/* New data or FIN. If new data arrive after half-duplex close,
		 * reset.
		 */
		if (!th->fin ||
		    TCP_SKB_CB(skb)->end_seq != tcptw->tw_rcv_nxt + 1) {
kill_with_rst:
			inet_twsk_deschedule(tw, &tcp_death_row);
			inet_twsk_put(tw);
			return TCP_TW_RST;
		}

		/* FIN arrived, enter true time-wait state. */
		tw->tw_substate	  = TCP_TIME_WAIT;
		tcptw->tw_rcv_nxt = TCP_SKB_CB(skb)->end_seq;
		if (tmp_opt.saw_tstamp) {
			tcptw->tw_ts_recent_stamp = get_seconds();
			tcptw->tw_ts_recent	  = tmp_opt.rcv_tsval;
		}

		/* I am shamed, but failed to make it more elegant.
		 * Yes, it is direct reference to IP, which is impossible
		 * to generalize to IPv6. Taking into account that IPv6
		 * do not understand recycling in any case, it not
		 * a big problem in practice. --ANK */
		if (tw->tw_family == AF_INET &&
		    tcp_death_row.sysctl_tw_recycle && tcptw->tw_ts_recent_stamp &&
		    tcp_v4_tw_remember_stamp(tw))
			inet_twsk_schedule(tw, &tcp_death_row, tw->tw_timeout,
					   TCP_TIMEWAIT_LEN);
		else
			inet_twsk_schedule(tw, &tcp_death_row, TCP_TIMEWAIT_LEN,
					   TCP_TIMEWAIT_LEN);
		return TCP_TW_ACK;
	}

	/*
	 *	Now real TIME-WAIT state.
	 *
	 *	RFC 1122:
	 *	"When a connection is [...] on TIME-WAIT state [...]
	 *	[a TCP] MAY accept a new SYN from the remote TCP to
	 *	reopen the connection directly, if it:
	 *
	 *	(1)  assigns its initial sequence number for the new
	 *	connection to be larger than the largest sequence
	 *	number it used on the previous connection incarnation,
	 *	and
	 *
	 *	(2)  returns to TIME-WAIT state if the SYN turns out
	 *	to be an old duplicate".
	 */

	if (!paws_reject &&
	    (TCP_SKB_CB(skb)->seq == tcptw->tw_rcv_nxt &&
	     (TCP_SKB_CB(skb)->seq == TCP_SKB_CB(skb)->end_seq || th->rst))) {
		/* In window segment, it may be only reset or bare ack. */

		if (th->rst) {
			/* This is TIME_WAIT assassination, in two flavors.
			 * Oh well... nobody has a sufficient solution to this
			 * protocol bug yet.
			 */
			if (sysctl_tcp_rfc1337 == 0) {
kill:
				inet_twsk_deschedule(tw, &tcp_death_row);
				inet_twsk_put(tw);
				return TCP_TW_SUCCESS;
			}
		}
		inet_twsk_schedule(tw, &tcp_death_row, TCP_TIMEWAIT_LEN,
				   TCP_TIMEWAIT_LEN);

		if (tmp_opt.saw_tstamp) {
			tcptw->tw_ts_recent	  = tmp_opt.rcv_tsval;
			tcptw->tw_ts_recent_stamp = get_seconds();
		}

		inet_twsk_put(tw);
		return TCP_TW_SUCCESS;
	}

	/* Out of window segment.

	   All the segments are ACKed immediately.

	   The only exception is new SYN. We accept it, if it is
	   not old duplicate and we are not in danger to be killed
	   by delayed old duplicates. RFC check is that it has
	   newer sequence number works at rates <40Mbit/sec.
	   However, if paws works, it is reliable AND even more,
	   we even may relax silly seq space cutoff.

	   RED-PEN: we violate main RFC requirement, if this SYN will appear
	   old duplicate (i.e. we receive RST in reply to SYN-ACK),
	   we must return socket to time-wait state. It is not good,
	   but not fatal yet.
	 */

	if (th->syn && !th->rst && !th->ack && !paws_reject &&
	    (after(TCP_SKB_CB(skb)->seq, tcptw->tw_rcv_nxt) ||
	     (tmp_opt.saw_tstamp &&
	      (s32)(tcptw->tw_ts_recent - tmp_opt.rcv_tsval) < 0))) {
		u32 isn = tcptw->tw_snd_nxt + 65535 + 2;
		if (isn == 0)
			isn++;
		TCP_SKB_CB(skb)->when = isn;
		return TCP_TW_SYN;
	}

	if (paws_reject)
		NET_INC_STATS_BH(twsk_net(tw), LINUX_MIB_PAWSESTABREJECTED);

	if (!th->rst) {
		/* In this case we must reset the TIMEWAIT timer.
		 *
		 * If it is ACKless SYN it may be both old duplicate
		 * and new good SYN with random sequence number <rcv_nxt.
		 * Do not reschedule in the last case.
		 */
		if (paws_reject || th->ack)
			inet_twsk_schedule(tw, &tcp_death_row, TCP_TIMEWAIT_LEN,
					   TCP_TIMEWAIT_LEN);

		/* Send ACK. Note, we do not put the bucket,
		 * it will be released by caller.
		 */
		return TCP_TW_ACK;
	}
	inet_twsk_put(tw);
	return TCP_TW_SUCCESS;
}