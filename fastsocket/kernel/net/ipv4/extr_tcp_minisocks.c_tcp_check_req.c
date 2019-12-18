#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tcphdr {int doff; int /*<<< orphan*/  rst; } ;
struct tcp_options_received {scalar_t__ rcv_tsecr; scalar_t__ saw_tstamp; int /*<<< orphan*/  rcv_tsval; scalar_t__ ts_recent_stamp; int /*<<< orphan*/  ts_recent; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int retrans; scalar_t__ rcv_wnd; TYPE_3__* rsk_ops; int /*<<< orphan*/  ts_recent; } ;
typedef  int __be32 ;
struct TYPE_14__ {scalar_t__ seq; scalar_t__ ack_seq; scalar_t__ end_seq; } ;
struct TYPE_8__ {int rskq_defer_accept; } ;
struct TYPE_13__ {TYPE_2__* icsk_af_ops; TYPE_1__ icsk_accept_queue; } ;
struct TYPE_12__ {int acked; } ;
struct TYPE_11__ {scalar_t__ rcv_isn; scalar_t__ snt_isn; scalar_t__ snt_synack; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* send_reset ) (struct sock*,struct sk_buff*) ;int /*<<< orphan*/  (* send_ack ) (struct sock*,struct sk_buff*,struct request_sock*) ;int /*<<< orphan*/  (* rtx_syn_ack ) (struct sock*,struct request_sock*) ;} ;
struct TYPE_9__ {struct sock* (* syn_recv_sock ) (struct sock*,struct sk_buff*,struct request_sock*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  LINUX_MIB_EMBRYONICRSTS ; 
 int /*<<< orphan*/  LINUX_MIB_PAWSESTABREJECTED ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TCP_FLAG_ACK ; 
 int TCP_FLAG_RST ; 
 int TCP_FLAG_SYN ; 
 int /*<<< orphan*/  TCP_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_MIB_ATTEMPTFAILS ; 
 TYPE_7__* TCP_SKB_CB (struct sk_buff*) ; 
 int TCP_TIMEOUT_INIT ; 
 int /*<<< orphan*/  after (scalar_t__,scalar_t__) ; 
 scalar_t__ get_seconds () ; 
 TYPE_6__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reqsk_queue_add (struct sock*,struct request_sock*,struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reqsk_queue_drop (struct sock*,struct request_sock*,struct request_sock**) ; 
 int /*<<< orphan*/  inet_csk_reqsk_queue_removed (struct sock*,struct request_sock*) ; 
 int /*<<< orphan*/  inet_csk_reqsk_queue_unlink (struct sock*,struct request_sock*,struct request_sock**) ; 
 TYPE_5__* inet_rsk (struct request_sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,struct request_sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*,struct sk_buff*,struct request_sock*) ; 
 struct sock* stub3 (struct sock*,struct sk_buff*,struct request_sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  sysctl_tcp_abort_on_overflow ; 
 int tcp_flag_word (struct tcphdr const*) ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_in_window (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tcp_parse_options (struct sk_buff*,struct tcp_options_received*,int /*<<< orphan*/ ) ; 
 int tcp_paws_reject (struct tcp_options_received*,int /*<<< orphan*/ ) ; 
 TYPE_4__* tcp_rsk (struct request_sock*) ; 

struct sock *tcp_check_req(struct sock *sk, struct sk_buff *skb,
			   struct request_sock *req,
			   struct request_sock **prev)
{
	const struct tcphdr *th = tcp_hdr(skb);
	__be32 flg = tcp_flag_word(th) & (TCP_FLAG_RST|TCP_FLAG_SYN|TCP_FLAG_ACK);
	int paws_reject = 0;
	struct tcp_options_received tmp_opt;
	struct sock *child;

	tmp_opt.saw_tstamp = 0;
	if (th->doff > (sizeof(struct tcphdr)>>2)) {
		tcp_parse_options(skb, &tmp_opt, 0);

		if (tmp_opt.saw_tstamp) {
			tmp_opt.ts_recent = req->ts_recent;
			/* We do not store true stamp, but it is not required,
			 * it can be estimated (approximately)
			 * from another data.
			 */
			tmp_opt.ts_recent_stamp = get_seconds() - ((TCP_TIMEOUT_INIT/HZ)<<req->retrans);
			paws_reject = tcp_paws_reject(&tmp_opt, th->rst);
		}
	}

	/* Check for pure retransmitted SYN. */
	if (TCP_SKB_CB(skb)->seq == tcp_rsk(req)->rcv_isn &&
	    flg == TCP_FLAG_SYN &&
	    !paws_reject) {
		/*
		 * RFC793 draws (Incorrectly! It was fixed in RFC1122)
		 * this case on figure 6 and figure 8, but formal
		 * protocol description says NOTHING.
		 * To be more exact, it says that we should send ACK,
		 * because this segment (at least, if it has no data)
		 * is out of window.
		 *
		 *  CONCLUSION: RFC793 (even with RFC1122) DOES NOT
		 *  describe SYN-RECV state. All the description
		 *  is wrong, we cannot believe to it and should
		 *  rely only on common sense and implementation
		 *  experience.
		 *
		 * Enforce "SYN-ACK" according to figure 8, figure 6
		 * of RFC793, fixed by RFC1122.
		 */
		req->rsk_ops->rtx_syn_ack(sk, req);
		return NULL;
	}

	/* Further reproduces section "SEGMENT ARRIVES"
	   for state SYN-RECEIVED of RFC793.
	   It is broken, however, it does not work only
	   when SYNs are crossed.

	   You would think that SYN crossing is impossible here, since
	   we should have a SYN_SENT socket (from connect()) on our end,
	   but this is not true if the crossed SYNs were sent to both
	   ends by a malicious third party.  We must defend against this,
	   and to do that we first verify the ACK (as per RFC793, page
	   36) and reset if it is invalid.  Is this a true full defense?
	   To convince ourselves, let us consider a way in which the ACK
	   test can still pass in this 'malicious crossed SYNs' case.
	   Malicious sender sends identical SYNs (and thus identical sequence
	   numbers) to both A and B:

		A: gets SYN, seq=7
		B: gets SYN, seq=7

	   By our good fortune, both A and B select the same initial
	   send sequence number of seven :-)

		A: sends SYN|ACK, seq=7, ack_seq=8
		B: sends SYN|ACK, seq=7, ack_seq=8

	   So we are now A eating this SYN|ACK, ACK test passes.  So
	   does sequence test, SYN is truncated, and thus we consider
	   it a bare ACK.

	   If icsk->icsk_accept_queue.rskq_defer_accept, we silently drop this
	   bare ACK.  Otherwise, we create an established connection.  Both
	   ends (listening sockets) accept the new incoming connection and try
	   to talk to each other. 8-)

	   Note: This case is both harmless, and rare.  Possibility is about the
	   same as us discovering intelligent life on another plant tomorrow.

	   But generally, we should (RFC lies!) to accept ACK
	   from SYNACK both here and in tcp_rcv_state_process().
	   tcp_rcv_state_process() does not, hence, we do not too.

	   Note that the case is absolutely generic:
	   we cannot optimize anything here without
	   violating protocol. All the checks must be made
	   before attempt to create socket.
	 */

	/* RFC793 page 36: "If the connection is in any non-synchronized state ...
	 *                  and the incoming segment acknowledges something not yet
	 *                  sent (the segment carries an unacceptable ACK) ...
	 *                  a reset is sent."
	 *
	 * Invalid ACK: reset will be sent by listening socket
	 */
	if ((flg & TCP_FLAG_ACK) &&
	    (TCP_SKB_CB(skb)->ack_seq != tcp_rsk(req)->snt_isn + 1))
		return sk;

	/* Also, it would be not so bad idea to check rcv_tsecr, which
	 * is essentially ACK extension and too early or too late values
	 * should cause reset in unsynchronized states.
	 */

	/* RFC793: "first check sequence number". */

	if (paws_reject || !tcp_in_window(TCP_SKB_CB(skb)->seq, TCP_SKB_CB(skb)->end_seq,
					  tcp_rsk(req)->rcv_isn + 1, tcp_rsk(req)->rcv_isn + 1 + req->rcv_wnd)) {
		/* Out of window: send ACK and drop. */
		if (!(flg & TCP_FLAG_RST))
			req->rsk_ops->send_ack(sk, skb, req);
		if (paws_reject)
			NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_PAWSESTABREJECTED);
		return NULL;
	}

	/* In sequence, PAWS is OK. */

	if (tmp_opt.saw_tstamp && !after(TCP_SKB_CB(skb)->seq, tcp_rsk(req)->rcv_isn + 1))
		req->ts_recent = tmp_opt.rcv_tsval;

	if (TCP_SKB_CB(skb)->seq == tcp_rsk(req)->rcv_isn) {
		/* Truncate SYN, it is out of window starting
		   at tcp_rsk(req)->rcv_isn + 1. */
		flg &= ~TCP_FLAG_SYN;
	}

	/* RFC793: "second check the RST bit" and
	 *	   "fourth, check the SYN bit"
	 */
	if (flg & (TCP_FLAG_RST|TCP_FLAG_SYN)) {
		TCP_INC_STATS_BH(sock_net(sk), TCP_MIB_ATTEMPTFAILS);
		goto embryonic_reset;
	}

	/* ACK sequence verified above, just make sure ACK is
	 * set.  If ACK not set, just silently drop the packet.
	 */
	if (!(flg & TCP_FLAG_ACK))
		return NULL;

	/* While TCP_DEFER_ACCEPT is active, drop bare ACK. */
	if (req->retrans < inet_csk(sk)->icsk_accept_queue.rskq_defer_accept &&
	    TCP_SKB_CB(skb)->end_seq == tcp_rsk(req)->rcv_isn + 1) {
		inet_rsk(req)->acked = 1;
		return NULL;
	}
	if (tmp_opt.saw_tstamp && tmp_opt.rcv_tsecr)
		tcp_rsk(req)->snt_synack = tmp_opt.rcv_tsecr;
	else if (req->retrans) /* don't take RTT sample if retrans && ~TS */
		tcp_rsk(req)->snt_synack = 0;

	/* OK, ACK is valid, create big socket and
	 * feed this segment to it. It will repeat all
	 * the tests. THIS SEGMENT MUST MOVE SOCKET TO
	 * ESTABLISHED STATE. If it will be dropped after
	 * socket is created, wait for troubles.
	 */
	child = inet_csk(sk)->icsk_af_ops->syn_recv_sock(sk, skb, req, NULL);
	if (child == NULL)
		goto listen_overflow;

	inet_csk_reqsk_queue_unlink(sk, req, prev);
	inet_csk_reqsk_queue_removed(sk, req);

	inet_csk_reqsk_queue_add(sk, req, child);
	return child;

listen_overflow:
	if (!sysctl_tcp_abort_on_overflow) {
		inet_rsk(req)->acked = 1;
		return NULL;
	}

embryonic_reset:
	NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_EMBRYONICRSTS);
	if (!(flg & TCP_FLAG_RST))
		req->rsk_ops->send_reset(sk, skb);

	inet_csk_reqsk_queue_drop(sk, req, prev);
	return NULL;
}