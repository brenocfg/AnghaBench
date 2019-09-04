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
typedef  int /*<<< orphan*/  tcp_seq ;
struct tcpcb {scalar_t__ t_rxtshift; int t_flagsext; int t_srtt; void* t_reorderwin; int /*<<< orphan*/  t_inpcb; int /*<<< orphan*/  t_reordered_pkts; } ;
struct sackhole {scalar_t__ rxmit_start; int /*<<< orphan*/  rxmit; int /*<<< orphan*/  end; } ;
typedef  int int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  tcps_ecn_fallback_reorder; int /*<<< orphan*/  tcps_reordered_pkts; int /*<<< orphan*/  tcps_detect_reordering; int /*<<< orphan*/  tcps_avoid_rxmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INP_INC_IFNET_STAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQ_GEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SEQ_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SEQ_LT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TCP_ECN_ENABLED (struct tcpcb*) ; 
 int TCP_RTT_SHIFT ; 
 int TF_PKTS_REORDERED ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecn_fallback_reorder ; 
 void* max (void*,int) ; 
 void* min (void*,int) ; 
 int tcp_detect_reordering ; 
 int /*<<< orphan*/  tcp_heuristic_ecn_aggressive (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_now ; 
 TYPE_1__ tcpstat ; 
 int timer_diff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcp_sack_detect_reordering(struct tcpcb *tp, struct sackhole *s,
    tcp_seq sacked_seq, tcp_seq snd_fack)
{
	int32_t rext = 0, reordered = 0;

	/*
	 * If the SACK hole is past snd_fack, this is from new SACK
	 * information, so we can ignore it.
	 */
	if (SEQ_GT(s->end, snd_fack))
		return;
	/*
	 * If there has been a retransmit timeout, then the timestamp on 
	 * the SACK segment will be newer. This might lead to a
	 * false-positive. Avoid re-ordering detection in this case.
	 */
	if (tp->t_rxtshift > 0)
		return;

	/*
	 * Detect reordering from SACK information by checking
	 * if recently sacked data was never retransmitted from this hole.
	 */
	if (SEQ_LT(s->rxmit, sacked_seq)) {
		reordered = 1;
		tcpstat.tcps_avoid_rxmt++;
	}

	if (reordered) {
		if (tcp_detect_reordering == 1 &&
		    !(tp->t_flagsext & TF_PKTS_REORDERED)) {
			tp->t_flagsext |= TF_PKTS_REORDERED;
			tcpstat.tcps_detect_reordering++;
		}

		tcpstat.tcps_reordered_pkts++;
		tp->t_reordered_pkts++;

		/*
		 * If reordering is seen on a connection wth ECN enabled,
		 * increment the heuristic
		 */
		if (TCP_ECN_ENABLED(tp)) {
			INP_INC_IFNET_STAT(tp->t_inpcb, ecn_fallback_reorder);
			tcpstat.tcps_ecn_fallback_reorder++;
			tcp_heuristic_ecn_aggressive(tp);
		}

		VERIFY(SEQ_GEQ(snd_fack, s->rxmit));

		if (s->rxmit_start > 0) {
			rext = timer_diff(tcp_now, 0, s->rxmit_start, 0);
			if (rext < 0)
				return;

			/*
			 * We take the maximum reorder window to schedule
			 * DELAYFR timer as that will take care of jitter
			 * on the network path.
			 *
			 * Computing average and standard deviation seems
			 * to cause unnecessary retransmissions when there
			 * is high jitter.
			 *
			 * We set a maximum of SRTT/2 and a minimum of
			 * 10 ms on the reorder window.
			 */
			tp->t_reorderwin = max(tp->t_reorderwin, rext);
			tp->t_reorderwin = min(tp->t_reorderwin,
			    (tp->t_srtt >> (TCP_RTT_SHIFT - 1)));
			tp->t_reorderwin = max(tp->t_reorderwin, 10);
		}
	}
}