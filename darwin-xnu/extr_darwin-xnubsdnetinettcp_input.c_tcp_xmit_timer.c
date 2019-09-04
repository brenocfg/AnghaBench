#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ tcp_seq ;
struct tcpcb {scalar_t__ iss; int t_flagsext; int t_srtt; int t_rttvar; int t_rttbest; int t_rttcur; scalar_t__ t_softerror; int /*<<< orphan*/  t_rttmin; int /*<<< orphan*/  t_rxtcur; TYPE_3__* t_inpcb; int /*<<< orphan*/  t_rttupdated; int /*<<< orphan*/  t_rttvar_prev; int /*<<< orphan*/  t_srtt_prev; scalar_t__ t_badrexmt_time; int /*<<< orphan*/  snd_max; int /*<<< orphan*/  snd_una; } ;
struct TYPE_8__ {int /*<<< orphan*/  tcps_rttupdated; } ;
struct TYPE_6__ {int /*<<< orphan*/  ro_rt; } ;
struct TYPE_7__ {TYPE_2__ inp_route; TYPE_1__* inp_last_outifp; } ;
struct TYPE_5__ {int if_eflags; } ;

/* Variables and functions */
 int IFEF_AWDL ; 
 scalar_t__ SEQ_GT (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SEQ_LEQ (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPTV_REXMTMAX ; 
 int /*<<< orphan*/  TCPT_RANGESET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_ADD_REXMTSLOP (struct tcpcb*) ; 
 int TCP_DELTA_SHIFT ; 
 int /*<<< orphan*/  TCP_REXMTVAL (struct tcpcb*) ; 
 int TCP_RTTVAR_SHIFT ; 
 int TCP_RTT_SHIFT ; 
 int TF_RECOMPUTE_RTT ; 
 scalar_t__ TSTMP_GEQ (scalar_t__,scalar_t__) ; 
 void* max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nstat_route_rtt (int /*<<< orphan*/ ,int,int) ; 
 TYPE_4__ tcpstat ; 
 int /*<<< orphan*/  update_base_rtt (struct tcpcb*,int) ; 

__attribute__((used)) static void
tcp_xmit_timer(struct tcpcb *tp, int rtt,
	u_int32_t tsecr, tcp_seq th_ack)
{
	int delta;

	/*
	 * On AWDL interface, the initial RTT measurement on SYN
	 * can be wrong due to peer caching. Avoid the first RTT
	 * measurement as it might skew up the RTO.
	 * <rdar://problem/28739046>
	 */
	if (tp->t_inpcb->inp_last_outifp != NULL &&
	    (tp->t_inpcb->inp_last_outifp->if_eflags & IFEF_AWDL) &&
	    th_ack == tp->iss + 1)
		return;

	if (tp->t_flagsext & TF_RECOMPUTE_RTT) {
		if (SEQ_GT(th_ack, tp->snd_una) &&
		    SEQ_LEQ(th_ack, tp->snd_max) &&
		    (tsecr == 0 ||
		    TSTMP_GEQ(tsecr, tp->t_badrexmt_time))) {
			/*
			 * We received a new ACk after a
			 * spurious timeout. Adapt retransmission
			 * timer as described in rfc 4015.
			 */
			tp->t_flagsext &= ~(TF_RECOMPUTE_RTT);
			tp->t_badrexmt_time = 0;
			tp->t_srtt = max(tp->t_srtt_prev, rtt);
			tp->t_srtt = tp->t_srtt << TCP_RTT_SHIFT;
			tp->t_rttvar = max(tp->t_rttvar_prev, (rtt >> 1));
			tp->t_rttvar = tp->t_rttvar << TCP_RTTVAR_SHIFT;

			if (tp->t_rttbest > (tp->t_srtt + tp->t_rttvar))
				tp->t_rttbest = tp->t_srtt + tp->t_rttvar;

			goto compute_rto;
		} else {
			return;
		}
	}

	tcpstat.tcps_rttupdated++;
	tp->t_rttupdated++;

	if (rtt > 0) {
		tp->t_rttcur = rtt;
		update_base_rtt(tp, rtt);
	}

	if (tp->t_srtt != 0) {
		/*
		 * srtt is stored as fixed point with 5 bits after the
		 * binary point (i.e., scaled by 32).  The following magic
		 * is equivalent to the smoothing algorithm in rfc793 with
		 * an alpha of .875 (srtt = rtt/8 + srtt*7/8 in fixed
		 * point).
		 *
		 * Freebsd adjusts rtt to origin 0 by subtracting 1
		 * from the provided rtt value. This was required because
		 * of the way t_rtttime was initiailised to 1 before.
		 * Since we changed t_rtttime to be based on
		 * tcp_now, this extra adjustment is not needed.
		 */
		delta = (rtt << TCP_DELTA_SHIFT)
			- (tp->t_srtt >> (TCP_RTT_SHIFT - TCP_DELTA_SHIFT));

		if ((tp->t_srtt += delta) <= 0)
			tp->t_srtt = 1;

		/*
		 * We accumulate a smoothed rtt variance (actually, a
		 * smoothed mean difference), then set the retransmit
		 * timer to smoothed rtt + 4 times the smoothed variance.
		 * rttvar is stored as fixed point with 4 bits after the
		 * binary point (scaled by 16).  The following is
		 * equivalent to rfc793 smoothing with an alpha of .75
		 * (rttvar = rttvar*3/4 + |delta| / 4).  This replaces
		 * rfc793's wired-in beta.
		 */
		if (delta < 0)
			delta = -delta;
		delta -= tp->t_rttvar >> (TCP_RTTVAR_SHIFT - TCP_DELTA_SHIFT);
		if ((tp->t_rttvar += delta) <= 0)
			tp->t_rttvar = 1;
		if (tp->t_rttbest == 0  ||
			tp->t_rttbest > (tp->t_srtt + tp->t_rttvar))
			tp->t_rttbest = tp->t_srtt + tp->t_rttvar;
	} else {
		/*
		 * No rtt measurement yet - use the unsmoothed rtt.
		 * Set the variance to half the rtt (so our first
		 * retransmit happens at 3*rtt).
		 */
		tp->t_srtt = rtt << TCP_RTT_SHIFT;
		tp->t_rttvar = rtt << (TCP_RTTVAR_SHIFT - 1);
	}

compute_rto:
	nstat_route_rtt(tp->t_inpcb->inp_route.ro_rt, tp->t_srtt,
		tp->t_rttvar);

	/*
	 * the retransmit should happen at rtt + 4 * rttvar.
	 * Because of the way we do the smoothing, srtt and rttvar
	 * will each average +1/2 tick of bias.  When we compute
	 * the retransmit timer, we want 1/2 tick of rounding and
	 * 1 extra tick because of +-1/2 tick uncertainty in the
	 * firing of the timer.  The bias will give us exactly the
	 * 1.5 tick we need.  But, because the bias is
	 * statistical, we have to test that we don't drop below
	 * the minimum feasible timer (which is 2 ticks).
	 */
	TCPT_RANGESET(tp->t_rxtcur, TCP_REXMTVAL(tp),
		max(tp->t_rttmin, rtt + 2), TCPTV_REXMTMAX,
		TCP_ADD_REXMTSLOP(tp));

	/*
	 * We received an ack for a packet that wasn't retransmitted;
	 * it is probably safe to discard any error indications we've
	 * received recently.  This isn't quite right, but close enough
	 * for now (a route might have failed after we sent a segment,
	 * and the return path might not be symmetrical).
	 */
	tp->t_softerror = 0;
}