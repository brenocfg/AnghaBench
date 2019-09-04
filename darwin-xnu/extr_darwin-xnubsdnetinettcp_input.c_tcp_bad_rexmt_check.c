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
struct tcpopt {int to_flags; scalar_t__ to_tsecr; } ;
struct tcphdr {int /*<<< orphan*/  th_ack; } ;
struct tcpcb {scalar_t__ t_rxtshift; int t_flagsext; scalar_t__ t_tlphighrxt; int t_flags; scalar_t__ t_pmtud_start_ts; scalar_t__ t_tlpstart; scalar_t__ t_rxtstart; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcps_dsack_badrexmt; int /*<<< orphan*/  tcps_tlp_recoverlastpkt; int /*<<< orphan*/  tcps_sndrexmitbad; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FASTRECOVERY (struct tcpcb*) ; 
 int /*<<< orphan*/  IN_FASTRECOVERY (struct tcpcb*) ; 
 scalar_t__ SEQ_GEQ (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TCP_CC_BAD_REXMT_RECOVERY ; 
 int /*<<< orphan*/  TCP_CC_DSACK_BAD_REXMT ; 
 int /*<<< orphan*/  TCP_CC_TLP_RECOVER_LASTPACKET ; 
 int TF_BLACKHOLE ; 
 int TF_SENT_TLPROBE ; 
 int TOF_TS ; 
 scalar_t__ TSTMP_LT (scalar_t__,scalar_t__) ; 
 scalar_t__ TSTMP_SUPPORTED (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_bad_rexmt_restore_state (struct tcpcb*,struct tcphdr*) ; 
 int /*<<< orphan*/  tcp_ccdbg_trace (struct tcpcb*,struct tcphdr*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_detect_bad_rexmt (struct tcpcb*,struct tcphdr*,struct tcpopt*,scalar_t__) ; 
 int /*<<< orphan*/  tcp_pmtud_revert_segment_size (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_reduce_congestion_window (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_rxtseg_clean (struct tcpcb*) ; 
 scalar_t__ tcp_rxtseg_detect_bad_rexmt (struct tcpcb*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_rxtseg_dsack_for_tlp (struct tcpcb*) ; 
 TYPE_1__ tcpstat ; 

__attribute__((used)) static void
tcp_bad_rexmt_check(struct tcpcb *tp, struct tcphdr *th, struct tcpopt *to)
{
	if (tp->t_rxtshift > 0 &&
	    tcp_detect_bad_rexmt(tp, th, to, tp->t_rxtstart)) {
		++tcpstat.tcps_sndrexmitbad;
		tcp_bad_rexmt_restore_state(tp, th);
		tcp_ccdbg_trace(tp, th, TCP_CC_BAD_REXMT_RECOVERY);
	} else if ((tp->t_flagsext & TF_SENT_TLPROBE)
	    && tp->t_tlphighrxt > 0
	    && SEQ_GEQ(th->th_ack, tp->t_tlphighrxt)
	    && !tcp_detect_bad_rexmt(tp, th, to, tp->t_tlpstart)) {
		/*
		 * check DSACK information also to make sure that
		 * the TLP was indeed needed
		 */
		if (tcp_rxtseg_dsack_for_tlp(tp)) {
			/*
			 * received a DSACK to indicate that TLP was
			 * not needed
			 */
			tcp_rxtseg_clean(tp);
			goto out;
		}

		/*
		 * The tail loss probe recovered the last packet and
		 * we need to adjust the congestion window to take
		 * this loss into account.
		 */
		++tcpstat.tcps_tlp_recoverlastpkt;
		if (!IN_FASTRECOVERY(tp)) {
			tcp_reduce_congestion_window(tp);
			EXIT_FASTRECOVERY(tp);
		}
		tcp_ccdbg_trace(tp, th, TCP_CC_TLP_RECOVER_LASTPACKET);
	} else if (tcp_rxtseg_detect_bad_rexmt(tp, th->th_ack)) {
		/*
		 * All of the retransmitted segments were duplicated, this
		 * can be an indication of bad fast retransmit.
		 */
		tcpstat.tcps_dsack_badrexmt++;
		tcp_bad_rexmt_restore_state(tp, th);
		tcp_ccdbg_trace(tp, th, TCP_CC_DSACK_BAD_REXMT);
		tcp_rxtseg_clean(tp);
	}
out:
	tp->t_flagsext &= ~(TF_SENT_TLPROBE);
	tp->t_tlphighrxt = 0;
	tp->t_tlpstart = 0;

	/*
	 * check if the latest ack was for a segment sent during PMTU
	 * blackhole detection. If the timestamp on the ack is before
	 * PMTU blackhole detection, then revert the size of the max
	 * segment to previous size.
	 */
	if (tp->t_rxtshift > 0 && (tp->t_flags & TF_BLACKHOLE) &&
	    tp->t_pmtud_start_ts > 0 && TSTMP_SUPPORTED(tp)) {
		if ((to->to_flags & TOF_TS) && to->to_tsecr != 0
		    && TSTMP_LT(to->to_tsecr, tp->t_pmtud_start_ts)) {
			tcp_pmtud_revert_segment_size(tp);
		}
	}
	if (tp->t_pmtud_start_ts > 0)
		tp->t_pmtud_start_ts = 0;
}