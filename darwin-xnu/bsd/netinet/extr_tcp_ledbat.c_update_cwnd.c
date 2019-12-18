#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct tcpcb {scalar_t__ t_rttcur; int snd_cwnd; int bg_ssthresh; int t_maxseg; scalar_t__ snd_max; scalar_t__ snd_una; } ;

/* Variables and functions */
 scalar_t__ allowed_increase ; 
 int bg_ss_fltsz ; 
 scalar_t__ get_base_rtt (struct tcpcb*) ; 
 int min (int,scalar_t__) ; 
 scalar_t__ target_qdelay ; 
 scalar_t__ tether_shift ; 

__attribute__((used)) static void update_cwnd(struct tcpcb *tp, uint32_t incr) {
	uint32_t max_allowed_cwnd = 0, flight_size = 0;
	uint32_t base_rtt;

	base_rtt = get_base_rtt(tp);

	/* If we do not have a good RTT measurement yet, increment
	 * congestion window by the default value.  
	 */
	if (base_rtt == 0 || tp->t_rttcur == 0) {
		tp->snd_cwnd += incr;
		goto check_max;
	}

	if (tp->t_rttcur <= (base_rtt + target_qdelay)) {
		/*
		 * Delay decreased or remained the same, we can increase
		 * the congestion window according to RFC 3465.
		 *
		 * Move background slow-start threshold to current
		 * congestion window so that the next time (after some idle
		 * period), we can attempt to do slow-start till here if there 
		 * is no increase in rtt
		 */
		if (tp->bg_ssthresh < tp->snd_cwnd)
			tp->bg_ssthresh = tp->snd_cwnd;
		tp->snd_cwnd += incr;	

	} else {
		/* In response to an increase in rtt, reduce the congestion 
		 * window by one-eighth. This will help to yield immediately 
		 * to a competing stream.
		 */
		uint32_t redwin;

		redwin = tp->snd_cwnd >> 3;  
		tp->snd_cwnd -= redwin;
		if (tp->snd_cwnd < bg_ss_fltsz * tp->t_maxseg)
			tp->snd_cwnd = bg_ss_fltsz * tp->t_maxseg;

		/* Lower background slow-start threshold so that the connection 
		 * will go into congestion avoidance phase
		 */
		if (tp->bg_ssthresh > tp->snd_cwnd)
			tp->bg_ssthresh = tp->snd_cwnd;
	}
check_max:
	/* Calculate the outstanding flight size and restrict the
	 * congestion window to a factor of flight size.
	 */
	flight_size = tp->snd_max - tp->snd_una;

	max_allowed_cwnd = (allowed_increase * tp->t_maxseg) 
		+ (flight_size << tether_shift);
	tp->snd_cwnd = min(tp->snd_cwnd, max_allowed_cwnd);
	return;
}