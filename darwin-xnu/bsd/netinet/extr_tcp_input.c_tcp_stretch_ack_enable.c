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
struct tcpcb {int rcv_by_unackwin; int t_maxseg; int t_flags; int t_flagsext; scalar_t__ rcv_nostrack_pkts; scalar_t__ rcv_waitforss; scalar_t__ rcv_nostrack_ts; scalar_t__ rcv_unackwin; } ;

/* Variables and functions */
 scalar_t__ TCP_STRETCHACK_ENABLE_PKTCNT ; 
 int TF_DISABLE_STRETCHACK ; 
 int TF_NOSTRETCHACK ; 
 int TF_RCVUNACK_WAITSS ; 
 int TF_STREAMING_ON ; 
 int TH_ACK ; 
 scalar_t__ TSTMP_GEQ (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TSTMP_GT (int /*<<< orphan*/ ,scalar_t__) ; 
 int maxseg_unacked ; 
 scalar_t__ tcp_maxrcvidle ; 
 int /*<<< orphan*/  tcp_now ; 
 scalar_t__ tcp_rcvsspktcnt ; 

__attribute__((used)) static inline int
tcp_stretch_ack_enable(struct tcpcb *tp, int thflags)
{
	if (tp->rcv_by_unackwin >= (maxseg_unacked * tp->t_maxseg) &&
	    TSTMP_GEQ(tp->rcv_unackwin, tcp_now))
		tp->t_flags |= TF_STREAMING_ON;
	else
		tp->t_flags &= ~TF_STREAMING_ON;

	/* If there has been an idle time, reset streaming detection */
	if (TSTMP_GT(tcp_now, tp->rcv_unackwin + tcp_maxrcvidle))
		tp->t_flags &= ~TF_STREAMING_ON;

	/*
	 * If there are flags other than TH_ACK set, reset streaming
	 * detection
	 */
	if (thflags & ~TH_ACK)
		tp->t_flags &= ~TF_STREAMING_ON;

	if (tp->t_flagsext & TF_DISABLE_STRETCHACK) {
		if (tp->rcv_nostrack_pkts >= TCP_STRETCHACK_ENABLE_PKTCNT) {
			tp->t_flagsext &= ~TF_DISABLE_STRETCHACK;
			tp->rcv_nostrack_pkts = 0;
			tp->rcv_nostrack_ts = 0;
		} else {
			tp->rcv_nostrack_pkts++;
		}
	}

 	if (!(tp->t_flagsext & (TF_NOSTRETCHACK|TF_DISABLE_STRETCHACK)) &&
	    (tp->t_flags & TF_STREAMING_ON) &&
	    (!(tp->t_flagsext & TF_RCVUNACK_WAITSS) ||
	    (tp->rcv_waitforss >= tcp_rcvsspktcnt))) {
		return(1);
	}

	return(0);
}