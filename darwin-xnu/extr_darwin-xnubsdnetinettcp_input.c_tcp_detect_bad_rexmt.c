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
typedef  scalar_t__ u_int32_t ;
struct tcpopt {int to_flags; scalar_t__ to_tsecr; } ;
struct tcphdr {int th_flags; } ;
struct tcpcb {int t_srtt; int t_rxtshift; int t_flagsext; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ TCP_ECN_ENABLED (struct tcpcb*) ; 
 int TCP_RTT_SHIFT ; 
 int TF_SENT_TLPROBE ; 
 int TH_ECE ; 
 int TOF_TS ; 
 scalar_t__ TSTMP_LT (scalar_t__,scalar_t__) ; 
 scalar_t__ TSTMP_SUPPORTED (struct tcpcb*) ; 
 scalar_t__ tcp_now ; 

int
tcp_detect_bad_rexmt(struct tcpcb *tp, struct tcphdr *th,
	struct tcpopt *to, u_int32_t rxtime)
{
	int32_t tdiff, bad_rexmt_win;
	bad_rexmt_win = (tp->t_srtt >> (TCP_RTT_SHIFT + 1));

	/* If the ack has ECN CE bit, then cwnd has to be adjusted */
	if (TCP_ECN_ENABLED(tp) && (th->th_flags & TH_ECE))
		return (0);
	if (TSTMP_SUPPORTED(tp)) {
		if (rxtime > 0 && (to->to_flags & TOF_TS)
		    && to->to_tsecr != 0
		    && TSTMP_LT(to->to_tsecr, rxtime))
		    return (1);
	} else {
		if ((tp->t_rxtshift == 1
		    || (tp->t_flagsext & TF_SENT_TLPROBE))
		    && rxtime > 0) {
			tdiff = (int32_t)(tcp_now - rxtime);
			if (tdiff < bad_rexmt_win)
				return(1);
		}
	}
	return(0);
}