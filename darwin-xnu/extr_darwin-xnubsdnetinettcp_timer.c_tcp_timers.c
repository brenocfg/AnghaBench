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
typedef  unsigned long u_int64_t ;
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  tra ;
struct tcptemp {int /*<<< orphan*/  tt_t; int /*<<< orphan*/  tt_ipgen; } ;
struct TYPE_8__ {size_t synrxtshift; } ;
struct tcpcb {scalar_t__ t_rcvtime; int* t_timer; unsigned long t_accsleep_ms; int t_rxtshift; scalar_t__ t_rxt_conndroptime; scalar_t__ t_rxtstart; int t_flagsext; int t_flags; scalar_t__ t_rxt_minimum_timeout; int t_adaptive_wtimo; int t_tfo_flags; int t_tfo_stats; scalar_t__ t_rxtcur; scalar_t__ t_pmtud_lastseg_size; scalar_t__ t_maxopd; scalar_t__ t_maxseg; scalar_t__ t_pmtud_saved_maxopd; scalar_t__ snd_cwnd; int t_rttvar; int t_srtt; scalar_t__ snd_nxt; scalar_t__ snd_una; scalar_t__ snd_recover; scalar_t__ snd_max; void* t_rtimo_probes; void* t_adaptive_rtimo; void* t_tfo_probes; int t_unacksegs; int snd_wnd; scalar_t__ t_tlphighrxt; scalar_t__ sack_newdata; int /*<<< orphan*/  t_sack_recovery_episode; int /*<<< orphan*/  ecn_flags; scalar_t__ t_tlpstart; int /*<<< orphan*/  t_rtttime; int /*<<< orphan*/  snd_holes; int /*<<< orphan*/  t_state; int /*<<< orphan*/  rcv_nostrack_pkts; int /*<<< orphan*/  t_stretchack_delayed; scalar_t__ rcv_nostrack_ts; int /*<<< orphan*/  t_tfo_probe_state; struct inpcb* t_inpcb; int /*<<< orphan*/  rcv_nxt; int /*<<< orphan*/  t_persist_stop; scalar_t__ t_pmtud_start_ts; int /*<<< orphan*/  t_rttmin; TYPE_1__ t_stat; int /*<<< orphan*/  t_sndtime; int /*<<< orphan*/  t_reorderwin; int /*<<< orphan*/  t_softerror; } ;
struct tcp_respond_args {int /*<<< orphan*/  ifscope; int /*<<< orphan*/  intcoproc_allowed; int /*<<< orphan*/  awdl_unrestricted; int /*<<< orphan*/  noexpensive; int /*<<< orphan*/  nocell; } ;
struct TYPE_10__ {void* sb_cc; } ;
struct socket {int so_flags1; int so_options; TYPE_3__ so_snd; void* so_error; } ;
struct mbuf {int dummy; } ;
struct inpcb {int inp_flags; struct ifnet* inp_last_outifp; TYPE_2__* inp_boundifp; struct socket* inp_socket; } ;
struct ifnet {int if_eflags; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* pre_fr ) (struct tcpcb*) ;int /*<<< orphan*/  (* after_timeout ) (struct tcpcb*) ;int /*<<< orphan*/  (* cwnd_init ) (struct tcpcb*) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  rxmit_drop; } ;
struct TYPE_12__ {int /*<<< orphan*/  rxmit_drop; } ;
struct TYPE_11__ {int /*<<< orphan*/  tcps_keepdrops; int /*<<< orphan*/  tcps_sack_recovery_episode; int /*<<< orphan*/  tcps_probe_if; int /*<<< orphan*/  tcps_pto; int /*<<< orphan*/  tcps_delack; int /*<<< orphan*/  tcps_nostretchack; int /*<<< orphan*/  tcps_tfo_blackhole; int /*<<< orphan*/  tcps_keepprobe; int /*<<< orphan*/  tcps_keeptimeo; int /*<<< orphan*/  tcps_persistdrop; int /*<<< orphan*/  tcps_persisttimeo; int /*<<< orphan*/  tcps_tailloss_rto; int /*<<< orphan*/  tcps_tfo_sndblackhole; int /*<<< orphan*/  tcps_rto_after_pto; int /*<<< orphan*/  tcps_rexmttimeo; int /*<<< orphan*/  tcps_timeoutdrop; int /*<<< orphan*/  tcps_drop_after_sleep; int /*<<< orphan*/  tcps_rxtfindrop; } ;
struct TYPE_9__ {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 TYPE_7__* CC_ALGO (struct tcpcb*) ; 
 int /*<<< orphan*/  CLEAR_IAJ_STATE (struct tcpcb*) ; 
 void* ENODATA ; 
 int /*<<< orphan*/  ENTER_FASTRECOVERY (struct tcpcb*) ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  EXIT_FASTRECOVERY (struct tcpcb*) ; 
 int IFEF_PROBE_CONNECTIVITY ; 
 int /*<<< orphan*/  IFSCOPE_NONE ; 
 int /*<<< orphan*/  INP_AWDL_UNRESTRICTED (struct inpcb*) ; 
 int INP_BOUND_IF ; 
 int /*<<< orphan*/  INP_INC_IFNET_STAT (struct inpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INP_INTCOPROC_ALLOWED (struct inpcb*) ; 
 int /*<<< orphan*/  INP_NO_CELLULAR (struct inpcb*) ; 
 int /*<<< orphan*/  INP_NO_EXPENSIVE (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WAIT_FOR_IF_FEEDBACK (struct inpcb*) ; 
 int /*<<< orphan*/  IN_FASTRECOVERY (struct tcpcb*) ; 
 void* OFFSET_FROM_START (struct tcpcb*,scalar_t__) ; 
 int /*<<< orphan*/  SACK_ENABLED (struct tcpcb*) ; 
 int /*<<< orphan*/  SEQ_GEQ (void*,scalar_t__) ; 
 int SOF1_DATA_AUTHENTICATED ; 
 int SO_FILT_HINT_ADAPTIVE_RTIMO ; 
 int SO_FILT_HINT_ADAPTIVE_WTIMO ; 
 int SO_FILT_HINT_LOCKED ; 
 int SO_FILT_HINT_TIMEOUT ; 
 int SO_KEEPALIVE ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TCPS_CLOSING ; 
 int /*<<< orphan*/  TCPS_ESTABLISHED ; 
 int /*<<< orphan*/  TCPS_FIN_WAIT_2 ; 
 int /*<<< orphan*/  TCPS_HAVEESTABLISHED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPS_SYN_RECEIVED ; 
 int /*<<< orphan*/  TCPS_SYN_SENT ; 
 int /*<<< orphan*/  TCPS_TIME_WAIT ; 
 int /*<<< orphan*/  TCPTV_REXMTMAX ; 
#define  TCPT_2MSL 134 
#define  TCPT_DELACK 133 
#define  TCPT_DELAYFR 132 
#define  TCPT_KEEP 131 
#define  TCPT_PERSIST 130 
#define  TCPT_PTO 129 
 int /*<<< orphan*/  TCPT_RANGESET (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TCPT_REXMT 128 
 int /*<<< orphan*/  TCP_ADD_REXMTSLOP (struct tcpcb*) ; 
 int /*<<< orphan*/  TCP_CC_ENTER_FASTRECOVERY ; 
 int /*<<< orphan*/  TCP_CC_REXMT_TIMEOUT ; 
 void* TCP_CONNECTIVITY_PROBES_MAX ; 
 scalar_t__ TCP_CONN_KEEPIDLE (struct tcpcb*) ; 
 scalar_t__ TCP_CONN_KEEPINTVL (struct tcpcb*) ; 
 scalar_t__ TCP_CONN_MAXIDLE (struct tcpcb*) ; 
 int /*<<< orphan*/  TCP_ECN_ENABLED (struct tcpcb*) ; 
 int TCP_MAXRXTSHIFT ; 
 int TCP_RETRANSHZ ; 
 scalar_t__ TCP_REXMTVAL (struct tcpcb*) ; 
 int TCP_RTT_SHIFT ; 
 scalar_t__ TCP_SLEEP_TOO_LONG ; 
 int /*<<< orphan*/  TCP_STRETCHACK_DELAY_THRESHOLD ; 
 int /*<<< orphan*/  TE_SENDCWR ; 
 int TFO_F_HEURISTIC_DONE ; 
 int TFO_F_NO_SNDPROBING ; 
 int TFO_F_SYN_LOSS ; 
 int /*<<< orphan*/  TFO_PROBE_PROBING ; 
 int /*<<< orphan*/  TFO_PROBE_WAIT_DATA ; 
 int TFO_S_RECV_BLACKHOLE ; 
 int TFO_S_SEND_BLACKHOLE ; 
 int TFO_S_SYN_DATA_ACKED ; 
 int TFO_S_SYN_DATA_SENT ; 
 int TF_ACKNOW ; 
 int TF_BLACKHOLE ; 
 int TF_CWND_NONVALIDATED ; 
 int TF_DELACK ; 
 int TF_DELAY_RECOVERY ; 
 int TF_DETECT_READSTALL ; 
 int TF_DISABLE_STRETCHACK ; 
 int TF_FASTOPEN ; 
 int TF_FASTOPEN_HEUR ; 
 int TF_FORCE ; 
 int TF_MAXSEGSNT ; 
 int TF_NOBLACKHOLE_DETECTION ; 
 int TF_PMTUD ; 
 int TF_PROBING ; 
 int TF_REQ_CC ; 
 int TF_REQ_SCALE ; 
 int TF_REQ_TSTMP ; 
 int TF_RXTFINDROP ; 
 int TF_SENTFIN ; 
 int TF_SENT_TLPROBE ; 
 int TF_STRETCHACK ; 
 int /*<<< orphan*/  TSTMP_GT (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TSTMP_LEQ (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TSTMP_LT (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  absolutetime_to_nanoseconds (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  always_keepalive ; 
 int /*<<< orphan*/  bzero (struct tcp_respond_args*,int) ; 
 int /*<<< orphan*/  dtom (struct tcptemp*) ; 
 TYPE_6__ ecn_off ; 
 TYPE_5__ ecn_on ; 
 int /*<<< orphan*/  in_losing (struct inpcb*) ; 
 int /*<<< orphan*/  m_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_absolutetime_asleep ; 
 int maxseg_unacked ; 
 scalar_t__ min (void*,int) ; 
 int /*<<< orphan*/  postevent (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soevent (struct socket*,int) ; 
 int /*<<< orphan*/  sorwakeup (struct socket*) ; 
 int /*<<< orphan*/  sowwakeup (struct socket*) ; 
 int /*<<< orphan*/  stub1 (struct tcpcb*) ; 
 int /*<<< orphan*/  stub2 (struct tcpcb*) ; 
 int /*<<< orphan*/  stub3 (struct tcpcb*) ; 
 scalar_t__* tcp_backoff ; 
 int tcp_broken_peer_syn_rxmit_thres ; 
 int /*<<< orphan*/  tcp_ccdbg_trace (struct tcpcb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tcpcb* tcp_close (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_delack_enabled ; 
 int /*<<< orphan*/  tcp_disable_tfo (struct tcpcb*) ; 
 struct tcpcb* tcp_drop (struct tcpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_free_sackholes (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_heuristic_ecn_droprxmt (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_heuristic_tfo_middlebox (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_keepalive_reset (struct tcpcb*) ; 
 struct tcptemp* tcp_maketemplate (struct tcpcb*) ; 
 scalar_t__ tcp_maxpersistidle ; 
 scalar_t__ tcp_mssdflt ; 
 scalar_t__ tcp_now ; 
 int /*<<< orphan*/  tcp_output (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_pmtud_black_hole_detect ; 
 scalar_t__ tcp_pmtud_black_hole_mss ; 
 int /*<<< orphan*/  tcp_pmtud_revert_segment_size (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_reset_stretch_ack (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_respond (struct tcpcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tcp_respond_args*) ; 
 int /*<<< orphan*/  tcp_rexmt_save_state (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_setpersist (struct tcpcb*) ; 
 scalar_t__* tcp_syn_backoff ; 
 scalar_t__ tcp_totbackoff ; 
 TYPE_4__ tcpstat ; 
 int /*<<< orphan*/  tfo_enabled (struct tcpcb*) ; 

struct tcpcb *
tcp_timers(struct tcpcb *tp, int timer)
{
	int32_t rexmt, optlen = 0, idle_time = 0;
	struct socket *so;
	struct tcptemp *t_template;
#if TCPDEBUG
	int ostate;
#endif

#if INET6
	int isipv6 = (tp->t_inpcb->inp_vflag & INP_IPV4) == 0;
#endif /* INET6 */
	u_int64_t accsleep_ms;
	u_int32_t last_sleep_ms = 0;

	so = tp->t_inpcb->inp_socket;
	idle_time = tcp_now - tp->t_rcvtime;

	switch (timer) {

	/*
	 * 2 MSL timeout in shutdown went off.  If we're closed but
	 * still waiting for peer to close and connection has been idle
	 * too long, or if 2MSL time is up from TIME_WAIT or FIN_WAIT_2,
	 * delete connection control block.
	 * Otherwise, (this case shouldn't happen) check again in a bit
	 * we keep the socket in the main list in that case.
	 */
	case TCPT_2MSL:
		tcp_free_sackholes(tp);
		if (tp->t_state != TCPS_TIME_WAIT &&
		    tp->t_state != TCPS_FIN_WAIT_2 &&
		    ((idle_time > 0) && (idle_time < TCP_CONN_MAXIDLE(tp)))) {
			tp->t_timer[TCPT_2MSL] = OFFSET_FROM_START(tp,
				(u_int32_t)TCP_CONN_KEEPINTVL(tp));
		} else {
			tp = tcp_close(tp);
			return(tp);
		}
		break;

	/*
	 * Retransmission timer went off.  Message has not
	 * been acked within retransmit interval.  Back off
	 * to a longer retransmit interval and retransmit one segment.
	 */
	case TCPT_REXMT:
		absolutetime_to_nanoseconds(mach_absolutetime_asleep,
		    &accsleep_ms);
		accsleep_ms = accsleep_ms / 1000000UL;
		if (accsleep_ms > tp->t_accsleep_ms)
			last_sleep_ms = accsleep_ms - tp->t_accsleep_ms;
		/*
		 * Drop a connection in the retransmit timer
		 * 1. If we have retransmitted more than TCP_MAXRXTSHIFT
		 * times
		 * 2. If the time spent in this retransmission episode is
		 * more than the time limit set with TCP_RXT_CONNDROPTIME
		 * socket option
		 * 3. If TCP_RXT_FINDROP socket option was set and
		 * we have already retransmitted the FIN 3 times without
		 * receiving an ack
		 */
		if (++tp->t_rxtshift > TCP_MAXRXTSHIFT ||
		    (tp->t_rxt_conndroptime > 0 && tp->t_rxtstart > 0 &&
		    (tcp_now - tp->t_rxtstart) >= tp->t_rxt_conndroptime) ||
		    ((tp->t_flagsext & TF_RXTFINDROP) != 0 &&
		    (tp->t_flags & TF_SENTFIN) != 0 && tp->t_rxtshift >= 4) ||
		    (tp->t_rxtshift > 4 && last_sleep_ms >= TCP_SLEEP_TOO_LONG)) {
			if (tp->t_state == TCPS_ESTABLISHED &&
			    tp->t_rxt_minimum_timeout > 0) {
				/*
				 * Avoid dropping a connection if minimum
				 * timeout is set and that time did not
				 * pass. We will retry sending
				 * retransmissions at the maximum interval
				 */
				if (TSTMP_LT(tcp_now, (tp->t_rxtstart +
				    tp->t_rxt_minimum_timeout))) {
					tp->t_rxtshift = TCP_MAXRXTSHIFT - 1;
					goto retransmit_packet;
				}
			}
			if ((tp->t_flagsext & TF_RXTFINDROP) != 0) {
				tcpstat.tcps_rxtfindrop++;
			} else if (last_sleep_ms >= TCP_SLEEP_TOO_LONG) {
				tcpstat.tcps_drop_after_sleep++;
			} else {
				tcpstat.tcps_timeoutdrop++;
			}
			if (tp->t_rxtshift >= TCP_MAXRXTSHIFT) {
				if (TCP_ECN_ENABLED(tp)) {
					INP_INC_IFNET_STAT(tp->t_inpcb,
					    ecn_on.rxmit_drop);
				} else {
					INP_INC_IFNET_STAT(tp->t_inpcb,
					    ecn_off.rxmit_drop);
				}
			}
			tp->t_rxtshift = TCP_MAXRXTSHIFT;
			postevent(so, 0, EV_TIMEOUT);
			soevent(so,
			    (SO_FILT_HINT_LOCKED|SO_FILT_HINT_TIMEOUT));

			if (TCP_ECN_ENABLED(tp) &&
			    tp->t_state == TCPS_ESTABLISHED)
				tcp_heuristic_ecn_droprxmt(tp);

			tp = tcp_drop(tp, tp->t_softerror ?
			    tp->t_softerror : ETIMEDOUT);

			break;
		}
retransmit_packet:
		tcpstat.tcps_rexmttimeo++;
		tp->t_accsleep_ms = accsleep_ms;

		if (tp->t_rxtshift == 1 &&
			tp->t_state == TCPS_ESTABLISHED) {
			/* Set the time at which retransmission started. */
			tp->t_rxtstart = tcp_now;

			/*
			 * if this is the first retransmit timeout, save
			 * the state so that we can recover if the timeout
			 * is spurious.
			 */
			tcp_rexmt_save_state(tp);
		}
#if MPTCP
		if ((tp->t_rxtshift >= mptcp_fail_thresh) &&
		    (tp->t_state == TCPS_ESTABLISHED) &&
		    (tp->t_mpflags & TMPF_MPTCP_TRUE))
			mptcp_act_on_txfail(so);

		if (so->so_flags & SOF_MP_SUBFLOW) {
			struct mptses *mpte = tptomptp(tp)->mpt_mpte;

			mptcp_check_subflows_and_add(mpte);
		}
#endif /* MPTCP */

		if (tp->t_adaptive_wtimo > 0 &&
			tp->t_rxtshift > tp->t_adaptive_wtimo &&
			TCPS_HAVEESTABLISHED(tp->t_state)) {
			/* Send an event to the application */
			soevent(so,
				(SO_FILT_HINT_LOCKED|
				SO_FILT_HINT_ADAPTIVE_WTIMO));
		}

		/*
		 * If this is a retransmit timeout after PTO, the PTO
		 * was not effective
		 */
		if (tp->t_flagsext & TF_SENT_TLPROBE) {
			tp->t_flagsext &= ~(TF_SENT_TLPROBE);
			tcpstat.tcps_rto_after_pto++;
		}

		if (tp->t_flagsext & TF_DELAY_RECOVERY) {
			/*
			 * Retransmit timer fired before entering recovery
			 * on a connection with packet re-ordering. This
			 * suggests that the reordering metrics computed
			 * are not accurate.
			 */
			tp->t_reorderwin = 0;
			tp->t_timer[TCPT_DELAYFR] = 0;
			tp->t_flagsext &= ~(TF_DELAY_RECOVERY);
		}

		if (tp->t_state == TCPS_SYN_RECEIVED)
			tcp_disable_tfo(tp);

		if (!(tp->t_tfo_flags & TFO_F_HEURISTIC_DONE) &&
		    (tp->t_tfo_stats & TFO_S_SYN_DATA_SENT) &&
		    !(tp->t_tfo_flags & TFO_F_NO_SNDPROBING) &&
		    ((tp->t_state != TCPS_SYN_SENT && tp->t_rxtshift > 1) ||
		     tp->t_rxtshift > 4)) {
			/*
			 * For regular retransmissions, a first one is being
			 * done for tail-loss probe.
			 * Thus, if rxtshift > 1, this means we have sent the segment
			 * a total of 3 times.
			 *
			 * If we are in SYN-SENT state, then there is no tail-loss
			 * probe thus we have to let rxtshift go up to 3.
			 */
			tcp_heuristic_tfo_middlebox(tp);

			so->so_error = ENODATA;
			sorwakeup(so);
			sowwakeup(so);

			tp->t_tfo_stats |= TFO_S_SEND_BLACKHOLE;
			tcpstat.tcps_tfo_sndblackhole++;
		}

		if (!(tp->t_tfo_flags & TFO_F_HEURISTIC_DONE) &&
		    (tp->t_tfo_stats & TFO_S_SYN_DATA_ACKED) &&
		    tp->t_rxtshift > 3) {
			if (TSTMP_GT(tp->t_sndtime - 10 * TCP_RETRANSHZ, tp->t_rcvtime)) {
				tcp_heuristic_tfo_middlebox(tp);

				so->so_error = ENODATA;
				sorwakeup(so);
				sowwakeup(so);
			}
		}

		if (tp->t_state == TCPS_SYN_SENT) {
			rexmt = TCP_REXMTVAL(tp) * tcp_syn_backoff[tp->t_rxtshift];
			tp->t_stat.synrxtshift = tp->t_rxtshift;

			/* When retransmitting, disable TFO */
			if (tfo_enabled(tp) &&
			    (!(so->so_flags1 & SOF1_DATA_AUTHENTICATED) ||
			     (tp->t_flagsext & TF_FASTOPEN_HEUR))) {
				tp->t_flagsext &= ~TF_FASTOPEN;
				tp->t_tfo_flags |= TFO_F_SYN_LOSS;
			}
		} else {
			rexmt = TCP_REXMTVAL(tp) * tcp_backoff[tp->t_rxtshift];
		}

		TCPT_RANGESET(tp->t_rxtcur, rexmt, tp->t_rttmin, TCPTV_REXMTMAX,
			TCP_ADD_REXMTSLOP(tp));
		tp->t_timer[TCPT_REXMT] = OFFSET_FROM_START(tp, tp->t_rxtcur);

		if (INP_WAIT_FOR_IF_FEEDBACK(tp->t_inpcb))
			goto fc_output;

		tcp_free_sackholes(tp);
		/*
		 * Check for potential Path MTU Discovery Black Hole
		 */
		if (tcp_pmtud_black_hole_detect &&
			!(tp->t_flagsext & TF_NOBLACKHOLE_DETECTION) &&
			(tp->t_state == TCPS_ESTABLISHED)) {
			if ((tp->t_flags & TF_PMTUD) &&
			    ((tp->t_flags & TF_MAXSEGSNT)
			    || tp->t_pmtud_lastseg_size > tcp_pmtud_black_hole_mss) &&
			    tp->t_rxtshift == 2) {
				/*
				 * Enter Path MTU Black-hole Detection mechanism:
				 * - Disable Path MTU Discovery (IP "DF" bit).
				 * - Reduce MTU to lower value than what we
				 * negotiated with the peer.
				 */
				/* Disable Path MTU Discovery for now */
				tp->t_flags &= ~TF_PMTUD;
				/* Record that we may have found a black hole */
				tp->t_flags |= TF_BLACKHOLE;
				optlen = tp->t_maxopd - tp->t_maxseg;
				/* Keep track of previous MSS */
				tp->t_pmtud_saved_maxopd = tp->t_maxopd;
				tp->t_pmtud_start_ts = tcp_now;
				if (tp->t_pmtud_start_ts == 0)
					tp->t_pmtud_start_ts++;
				/* Reduce the MSS to intermediary value */
				if (tp->t_maxopd > tcp_pmtud_black_hole_mss) {
					tp->t_maxopd = tcp_pmtud_black_hole_mss;
				} else {
					tp->t_maxopd = /* use the default MSS */
#if INET6
						isipv6 ? tcp_v6mssdflt :
#endif /* INET6 */
							tcp_mssdflt;
				}
				tp->t_maxseg = tp->t_maxopd - optlen;

				/*
				 * Reset the slow-start flight size
				 * as it may depend on the new MSS
				 */
				if (CC_ALGO(tp)->cwnd_init != NULL)
					CC_ALGO(tp)->cwnd_init(tp);
				tp->snd_cwnd = tp->t_maxseg;
			}
			/*
			 * If further retransmissions are still
			 * unsuccessful with a lowered MTU, maybe this
			 * isn't a Black Hole and we restore the previous
			 * MSS and blackhole detection flags.
			 */
			else {

				if ((tp->t_flags & TF_BLACKHOLE) &&
				    (tp->t_rxtshift > 4)) {
					tcp_pmtud_revert_segment_size(tp);
					tp->snd_cwnd = tp->t_maxseg;
				}
			}
		}


		/*
		 * Disable rfc1323 and rfc1644 if we haven't got any
		 * response to our SYN (after we reach the threshold)
		 * to work-around some broken terminal servers (most of
		 * which have hopefully been retired) that have bad VJ
		 * header compression code which trashes TCP segments
		 * containing unknown-to-them TCP options.
		 * Do this only on non-local connections.
		 */
		if (tp->t_state == TCPS_SYN_SENT &&
		    tp->t_rxtshift == tcp_broken_peer_syn_rxmit_thres)
			tp->t_flags &= ~(TF_REQ_SCALE|TF_REQ_TSTMP|TF_REQ_CC);

		/*
		 * If losing, let the lower level know and try for
		 * a better route.  Also, if we backed off this far,
		 * our srtt estimate is probably bogus.  Clobber it
		 * so we'll take the next rtt measurement as our srtt;
		 * move the current srtt into rttvar to keep the current
		 * retransmit times until then.
		 */
		if (tp->t_rxtshift > TCP_MAXRXTSHIFT / 4) {
#if INET6
			if (isipv6)
				in6_losing(tp->t_inpcb);
			else
#endif /* INET6 */
			in_losing(tp->t_inpcb);
			tp->t_rttvar += (tp->t_srtt >> TCP_RTT_SHIFT);
			tp->t_srtt = 0;
		}
		tp->snd_nxt = tp->snd_una;
		/*
		 * Note:  We overload snd_recover to function also as the
		 * snd_last variable described in RFC 2582
		 */
		tp->snd_recover = tp->snd_max;
		/*
		 * Force a segment to be sent.
		 */
		tp->t_flags |= TF_ACKNOW;

		/* If timing a segment in this window, stop the timer */
		tp->t_rtttime = 0;

		if (!IN_FASTRECOVERY(tp) && tp->t_rxtshift == 1)
			tcpstat.tcps_tailloss_rto++;


		/*
		 * RFC 5681 says: when a TCP sender detects segment loss
		 * using retransmit timer and the given segment has already
		 * been retransmitted by way of the retransmission timer at
		 * least once, the value of ssthresh is held constant
		 */
		if (tp->t_rxtshift == 1 &&
		    CC_ALGO(tp)->after_timeout != NULL) {
			CC_ALGO(tp)->after_timeout(tp);
			/*
			 * CWR notifications are to be sent on new data
			 * right after Fast Retransmits and ECE
			 * notification receipts.
			 */
			if (TCP_ECN_ENABLED(tp))
				tp->ecn_flags |= TE_SENDCWR;
		}

		EXIT_FASTRECOVERY(tp);

		/* Exit cwnd non validated phase */
		tp->t_flagsext &= ~TF_CWND_NONVALIDATED;


fc_output:
		tcp_ccdbg_trace(tp, NULL, TCP_CC_REXMT_TIMEOUT);

		(void) tcp_output(tp);
		break;

	/*
	 * Persistance timer into zero window.
	 * Force a byte to be output, if possible.
	 */
	case TCPT_PERSIST:
		tcpstat.tcps_persisttimeo++;
		/*
		 * Hack: if the peer is dead/unreachable, we do not
		 * time out if the window is closed.  After a full
		 * backoff, drop the connection if the idle time
		 * (no responses to probes) reaches the maximum
		 * backoff that we would use if retransmitting.
		 *
		 * Drop the connection if we reached the maximum allowed time for
		 * Zero Window Probes without a non-zero update from the peer.
		 * See rdar://5805356
		 */
		if ((tp->t_rxtshift == TCP_MAXRXTSHIFT &&
		    (idle_time >= tcp_maxpersistidle ||
		    idle_time >= TCP_REXMTVAL(tp) * tcp_totbackoff)) ||
		    ((tp->t_persist_stop != 0) &&
			TSTMP_LEQ(tp->t_persist_stop, tcp_now))) {
			tcpstat.tcps_persistdrop++;
			postevent(so, 0, EV_TIMEOUT);
			soevent(so,
			    (SO_FILT_HINT_LOCKED|SO_FILT_HINT_TIMEOUT));
			tp = tcp_drop(tp, ETIMEDOUT);
			break;
		}
		tcp_setpersist(tp);
		tp->t_flagsext |= TF_FORCE;
		(void) tcp_output(tp);
		tp->t_flagsext &= ~TF_FORCE;
		break;

	/*
	 * Keep-alive timer went off; send something
	 * or drop connection if idle for too long.
	 */
	case TCPT_KEEP:
		tcpstat.tcps_keeptimeo++;
#if MPTCP
		/*
		 * Regular TCP connections do not send keepalives after closing
		 * MPTCP must not also, after sending Data FINs.
		 */
		struct mptcb *mp_tp = tptomptp(tp);
		if ((tp->t_mpflags & TMPF_MPTCP_TRUE) &&
		    (tp->t_state > TCPS_ESTABLISHED)) {
			goto dropit;
		} else if (mp_tp != NULL) {
			if ((mptcp_ok_to_keepalive(mp_tp) == 0))
				goto dropit;
		}
#endif /* MPTCP */
		if (tp->t_state < TCPS_ESTABLISHED)
			goto dropit;
		if ((always_keepalive ||
		    (tp->t_inpcb->inp_socket->so_options & SO_KEEPALIVE) ||
		    (tp->t_flagsext & TF_DETECT_READSTALL) ||
		    (tp->t_tfo_probe_state == TFO_PROBE_PROBING)) &&
		    (tp->t_state <= TCPS_CLOSING || tp->t_state == TCPS_FIN_WAIT_2)) {
			if (idle_time >= TCP_CONN_KEEPIDLE(tp) + TCP_CONN_MAXIDLE(tp))
				goto dropit;
			/*
			 * Send a packet designed to force a response
			 * if the peer is up and reachable:
			 * either an ACK if the connection is still alive,
			 * or an RST if the peer has closed the connection
			 * due to timeout or reboot.
			 * Using sequence number tp->snd_una-1
			 * causes the transmitted zero-length segment
			 * to lie outside the receive window;
			 * by the protocol spec, this requires the
			 * correspondent TCP to respond.
			 */
			tcpstat.tcps_keepprobe++;
			t_template = tcp_maketemplate(tp);
			if (t_template) {
				struct inpcb *inp = tp->t_inpcb;
				struct tcp_respond_args tra;

				bzero(&tra, sizeof(tra));
				tra.nocell = INP_NO_CELLULAR(inp);
				tra.noexpensive = INP_NO_EXPENSIVE(inp);
				tra.awdl_unrestricted = INP_AWDL_UNRESTRICTED(inp);
				tra.intcoproc_allowed = INP_INTCOPROC_ALLOWED(inp);
				if (tp->t_inpcb->inp_flags & INP_BOUND_IF)
					tra.ifscope = tp->t_inpcb->inp_boundifp->if_index;
				else
					tra.ifscope = IFSCOPE_NONE;
				tcp_respond(tp, t_template->tt_ipgen,
				    &t_template->tt_t, (struct mbuf *)NULL,
				    tp->rcv_nxt, tp->snd_una - 1, 0, &tra);
				(void) m_free(dtom(t_template));
				if (tp->t_flagsext & TF_DETECT_READSTALL)
					tp->t_rtimo_probes++;
			}
			tp->t_timer[TCPT_KEEP] = OFFSET_FROM_START(tp,
			    TCP_CONN_KEEPINTVL(tp));
		} else {
			tp->t_timer[TCPT_KEEP] = OFFSET_FROM_START(tp,
			    TCP_CONN_KEEPIDLE(tp));
		}
		if (tp->t_flagsext & TF_DETECT_READSTALL) {
			struct ifnet *outifp = tp->t_inpcb->inp_last_outifp;
			bool reenable_probe = false;
			/*
			 * The keep alive packets sent to detect a read
			 * stall did not get a response from the
			 * peer. Generate more keep-alives to confirm this.
			 * If the number of probes sent reaches the limit,
			 * generate an event.
			 */
			if (tp->t_adaptive_rtimo > 0) {
				if (tp->t_rtimo_probes > tp->t_adaptive_rtimo) {
					/* Generate an event */
					soevent(so,
					    (SO_FILT_HINT_LOCKED |
					    SO_FILT_HINT_ADAPTIVE_RTIMO));
					tcp_keepalive_reset(tp);
				} else {
					reenable_probe = true;
				}
			} else if (outifp != NULL &&
			    (outifp->if_eflags & IFEF_PROBE_CONNECTIVITY) &&
			    tp->t_rtimo_probes <= TCP_CONNECTIVITY_PROBES_MAX) {
				reenable_probe = true;
			} else {
				tp->t_flagsext &= ~TF_DETECT_READSTALL;
			}
			if (reenable_probe) {
				int ind = min(tp->t_rtimo_probes,
				    TCP_MAXRXTSHIFT);
				tp->t_timer[TCPT_KEEP] = OFFSET_FROM_START(
				    tp, tcp_backoff[ind] * TCP_REXMTVAL(tp));
			}
		}
		if (tp->t_tfo_probe_state == TFO_PROBE_PROBING) {
			int ind;

			tp->t_tfo_probes++;
			ind = min(tp->t_tfo_probes, TCP_MAXRXTSHIFT);

			/*
			 * We take the minimum among the time set by true
			 * keepalive (see above) and the backoff'd RTO. That
			 * way we backoff in case of packet-loss but will never
			 * timeout slower than regular keepalive due to the
			 * backing off.
			 */
			tp->t_timer[TCPT_KEEP] = min(OFFSET_FROM_START(
			    tp, tcp_backoff[ind] * TCP_REXMTVAL(tp)),
			    tp->t_timer[TCPT_KEEP]);
		} else if (!(tp->t_tfo_flags & TFO_F_HEURISTIC_DONE) &&
			   tp->t_tfo_probe_state == TFO_PROBE_WAIT_DATA) {
			/* Still no data! Let's assume a TFO-error and err out... */
			tcp_heuristic_tfo_middlebox(tp);

			so->so_error = ENODATA;
			sorwakeup(so);
			tp->t_tfo_stats |= TFO_S_RECV_BLACKHOLE;
			tcpstat.tcps_tfo_blackhole++;
		}
		break;
	case TCPT_DELACK:
		if (tcp_delack_enabled && (tp->t_flags & TF_DELACK)) {
			tp->t_flags &= ~TF_DELACK;
			tp->t_timer[TCPT_DELACK] = 0;
			tp->t_flags |= TF_ACKNOW;

			/*
			 * If delayed ack timer fired while stretching
			 * acks, count the number of times the streaming
			 * detection was not correct. If this exceeds a
			 * threshold, disable strech ack on this
			 * connection
			 *
			 * Also, go back to acking every other packet.
			 */
			if ((tp->t_flags & TF_STRETCHACK)) {
				if (tp->t_unacksegs > 1 &&
				    tp->t_unacksegs < maxseg_unacked)
					tp->t_stretchack_delayed++;

				if (tp->t_stretchack_delayed >
					TCP_STRETCHACK_DELAY_THRESHOLD) {
					tp->t_flagsext |= TF_DISABLE_STRETCHACK;
					/*
					 * Note the time at which stretch
					 * ack was disabled automatically
					 */
					tp->rcv_nostrack_ts = tcp_now;
					tcpstat.tcps_nostretchack++;
					tp->t_stretchack_delayed = 0;
					tp->rcv_nostrack_pkts = 0;
				}
				tcp_reset_stretch_ack(tp);
			}

			/*
			 * If we are measuring inter packet arrival jitter
			 * for throttling a connection, this delayed ack
			 * might be the reason for accumulating some
			 * jitter. So let's restart the measurement.
			 */
			CLEAR_IAJ_STATE(tp);

			tcpstat.tcps_delack++;
			(void) tcp_output(tp);
		}
		break;

#if MPTCP
	case TCPT_JACK_RXMT:
		if ((tp->t_state == TCPS_ESTABLISHED) &&
		    (tp->t_mpflags & TMPF_PREESTABLISHED) &&
		    (tp->t_mpflags & TMPF_JOINED_FLOW)) {
			if (++tp->t_mprxtshift > TCP_MAXRXTSHIFT) {
				tcpstat.tcps_timeoutdrop++;
				postevent(so, 0, EV_TIMEOUT);
				soevent(so,
				    (SO_FILT_HINT_LOCKED|
				    SO_FILT_HINT_TIMEOUT));
				tp = tcp_drop(tp, tp->t_softerror ?
				    tp->t_softerror : ETIMEDOUT);
				break;
			}
			tcpstat.tcps_join_rxmts++;
			tp->t_mpflags |= TMPF_SND_JACK;
			tp->t_flags |= TF_ACKNOW;

			/*
			 * No backoff is implemented for simplicity for this
			 * corner case.
			 */
			(void) tcp_output(tp);
		}
		break;
#endif /* MPTCP */

	case TCPT_PTO:
	{
		int32_t snd_len;
		tp->t_flagsext &= ~(TF_SENT_TLPROBE);

		/*
		 * Check if the connection is in the right state to
		 * send a probe
		 */
		if (tp->t_state != TCPS_ESTABLISHED ||
		    (tp->t_rxtshift > 0 && !(tp->t_flagsext & TF_PROBING)) ||
		    tp->snd_max == tp->snd_una ||
		    !SACK_ENABLED(tp) ||
		    !TAILQ_EMPTY(&tp->snd_holes) ||
		    IN_FASTRECOVERY(tp))
			break;

		/*
		 * If there is no new data to send or if the
		 * connection is limited by receive window then
		 * retransmit the last segment, otherwise send
		 * new data.
		 */
		snd_len = min(so->so_snd.sb_cc, tp->snd_wnd)
		    - (tp->snd_max - tp->snd_una);
		if (snd_len > 0) {
			tp->snd_nxt = tp->snd_max;
		} else {
			snd_len = min((tp->snd_max - tp->snd_una),
			    tp->t_maxseg);
			tp->snd_nxt = tp->snd_max - snd_len;
		}

		tcpstat.tcps_pto++;
		if (tp->t_flagsext & TF_PROBING)
			tcpstat.tcps_probe_if++;

		/* If timing a segment in this window, stop the timer */
		tp->t_rtttime = 0;
		/* Note that tail loss probe is being sent */
		tp->t_flagsext |= TF_SENT_TLPROBE;
		tp->t_tlpstart = tcp_now;

		tp->snd_cwnd += tp->t_maxseg;

		/*
		 * When tail-loss-probe fires, we reset the RTO timer, because
		 * a probe just got sent, so we are good to push out the timer.
		 *
		 * Set to 0 to ensure that tcp_output() will reschedule it
		 */
		tp->t_timer[TCPT_REXMT] = 0;

		(void )tcp_output(tp);
		tp->snd_cwnd -= tp->t_maxseg;

		tp->t_tlphighrxt = tp->snd_nxt;
		break;
	}
	case TCPT_DELAYFR:
		tp->t_flagsext &= ~TF_DELAY_RECOVERY;

		/*
		 * Don't do anything if one of the following is true:
		 * - the connection is already in recovery
		 * - sequence until snd_recover has been acknowledged.
		 * - retransmit timeout has fired
		 */
		if (IN_FASTRECOVERY(tp) ||
		    SEQ_GEQ(tp->snd_una, tp->snd_recover) ||
		    tp->t_rxtshift > 0)
			break;

		VERIFY(SACK_ENABLED(tp));
		tcp_rexmt_save_state(tp);
		if (CC_ALGO(tp)->pre_fr != NULL) {
			CC_ALGO(tp)->pre_fr(tp);
			if (TCP_ECN_ENABLED(tp))
				tp->ecn_flags |= TE_SENDCWR;
		}
		ENTER_FASTRECOVERY(tp);

		tp->t_timer[TCPT_REXMT] = 0;
		tcpstat.tcps_sack_recovery_episode++;
		tp->t_sack_recovery_episode++;
		tp->sack_newdata = tp->snd_nxt;
		tp->snd_cwnd = tp->t_maxseg;
		tcp_ccdbg_trace(tp, NULL, TCP_CC_ENTER_FASTRECOVERY);
		(void) tcp_output(tp);
		break;
	dropit:
		tcpstat.tcps_keepdrops++;
		postevent(so, 0, EV_TIMEOUT);
		soevent(so,
		    (SO_FILT_HINT_LOCKED|SO_FILT_HINT_TIMEOUT));
		tp = tcp_drop(tp, ETIMEDOUT);
		break;
	}
#if TCPDEBUG
	if (tp->t_inpcb->inp_socket->so_options & SO_DEBUG)
		tcp_trace(TA_USER, ostate, tp, (void *)0, (struct tcphdr *)0,
			  PRU_SLOWTIMO);
#endif
	return (tp);
}