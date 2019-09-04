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
typedef  int u_int32_t ;
struct tcpopt {scalar_t__ to_tsecr; } ;
struct tcpcb {int t_flagsext; scalar_t__ rfbuf_ts; int rfbuf_cnt; int t_maxseg; TYPE_1__* t_bwmeas; int /*<<< orphan*/  t_segq; } ;
struct socket {int so_flags1; } ;
struct sockbuf {int sb_flags; int sb_hiwat; struct socket* sb_so; } ;
typedef  int int32_t ;
struct TYPE_2__ {int bw_rcvbw_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int SB_AUTOSIZE ; 
 int SOF1_EXTEND_BK_IDLE_WANTED ; 
 scalar_t__ TCPTV_RCVBUFIDLE ; 
 scalar_t__ TCPTV_RCVNOTS_QUANTUM ; 
 int TCP_RCVNOTS_BYTELEVEL ; 
 int TF_RECV_THROTTLE ; 
 scalar_t__ TSTMP_GEQ (scalar_t__,scalar_t__) ; 
 scalar_t__ TSTMP_GT (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TSTMP_SUPPORTED (struct tcpcb*) ; 
 int max (int,int) ; 
 int tcp_autorcvbuf_inc_shift ; 
 int tcp_autorcvbuf_max ; 
 scalar_t__ tcp_cansbgrow (struct sockbuf*) ; 
 scalar_t__ tcp_do_autorcvbuf ; 
 scalar_t__ tcp_now ; 
 int /*<<< orphan*/  tcp_sbrcv_reserve (struct tcpcb*,struct sockbuf*,int,int,int) ; 

__attribute__((used)) static void
tcp_sbrcv_grow(struct tcpcb *tp, struct sockbuf *sbrcv,
	struct tcpopt *to, u_int32_t pktlen, u_int32_t rcvbuf_max)
{
	struct socket *so = sbrcv->sb_so;

	/*
	 * Do not grow the receive socket buffer if
	 * - auto resizing is disabled, globally or on this socket
	 * - the high water mark already reached the maximum
	 * - the stream is in background and receive side is being
	 * throttled
	 * - if there are segments in reassembly queue indicating loss,
	 * do not need to increase recv window during recovery as more
	 * data is not going to be sent. A duplicate ack sent during
	 * recovery should not change the receive window
	 */
	if (tcp_do_autorcvbuf == 0 ||
		(sbrcv->sb_flags & SB_AUTOSIZE) == 0 ||
		tcp_cansbgrow(sbrcv) == 0 ||
		sbrcv->sb_hiwat >= rcvbuf_max ||
		(tp->t_flagsext & TF_RECV_THROTTLE) ||
		(so->so_flags1 & SOF1_EXTEND_BK_IDLE_WANTED) ||
		!LIST_EMPTY(&tp->t_segq)) {
		/* Can not resize the socket buffer, just return */
		goto out;
	}

	if (TSTMP_GT(tcp_now,
		tp->rfbuf_ts + TCPTV_RCVBUFIDLE)) {
		/* If there has been an idle period in the
		 * connection, just restart the measurement
		 */
		goto out;
	}

	if (!TSTMP_SUPPORTED(tp)) {
		/*
		 * Timestamp option is not supported on this connection.
		 * If the connection reached a state to indicate that
		 * the receive socket buffer needs to grow, increase
		 * the high water mark.
		 */
		if (TSTMP_GEQ(tcp_now,
			tp->rfbuf_ts + TCPTV_RCVNOTS_QUANTUM)) {
			if (tp->rfbuf_cnt >= TCP_RCVNOTS_BYTELEVEL) {
				tcp_sbrcv_reserve(tp, sbrcv,
				    tcp_autorcvbuf_max, 0,
				    tcp_autorcvbuf_max);
			}
			goto out;
		} else {
			tp->rfbuf_cnt += pktlen;
			return;
		}
	} else if (to->to_tsecr != 0) {
		/*
		 * If the timestamp shows that one RTT has
		 * completed, we can stop counting the
		 * bytes. Here we consider increasing
		 * the socket buffer if the bandwidth measured in
		 * last rtt, is more than half of sb_hiwat, this will
		 * help to scale the buffer according to the bandwidth
		 * on the link.
		 */
		if (TSTMP_GEQ(to->to_tsecr, tp->rfbuf_ts)) {
			if (tp->rfbuf_cnt > (sbrcv->sb_hiwat -
				(sbrcv->sb_hiwat >> 1))) {
				int32_t rcvbuf_inc, min_incr;
				/*
				 * Increment the receive window by a
				 * multiple of maximum sized segments.
				 * This will prevent a connection from
				 * sending smaller segments on wire if it
				 * is limited by the receive window.
				 *
				 * Set the ideal size based on current
				 * bandwidth measurements. We set the
				 * ideal size on receive socket buffer to
				 * be twice the bandwidth delay product.
				 */
				rcvbuf_inc = (tp->rfbuf_cnt << 1)
				    - sbrcv->sb_hiwat;

				/*
				 * Make the increment equal to 8 segments
				 * at least
				 */
				min_incr = tp->t_maxseg << tcp_autorcvbuf_inc_shift;
				if (rcvbuf_inc < min_incr)
					rcvbuf_inc = min_incr;

				rcvbuf_inc =
				    (rcvbuf_inc / tp->t_maxseg) * tp->t_maxseg;
				tcp_sbrcv_reserve(tp, sbrcv,
				    sbrcv->sb_hiwat + rcvbuf_inc,
				    (tp->rfbuf_cnt * 2), rcvbuf_max);
			}
			/* Measure instantaneous receive bandwidth */
			if (tp->t_bwmeas != NULL && tp->rfbuf_cnt > 0 &&
			    TSTMP_GT(tcp_now, tp->rfbuf_ts)) {
				u_int32_t rcv_bw;
				rcv_bw = tp->rfbuf_cnt /
				    (int)(tcp_now - tp->rfbuf_ts);
				if (tp->t_bwmeas->bw_rcvbw_max == 0) {
					tp->t_bwmeas->bw_rcvbw_max = rcv_bw;
				} else {
					tp->t_bwmeas->bw_rcvbw_max = max(
					    tp->t_bwmeas->bw_rcvbw_max, rcv_bw);
				}
			}
			goto out;
		} else {
			tp->rfbuf_cnt += pktlen;
			return;
		}
	}
out:
	/* Restart the measurement */
	tp->rfbuf_ts = 0;
	tp->rfbuf_cnt = 0;
	return;
}