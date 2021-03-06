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
struct tcphdr {int th_flags; } ;
struct tcpcb {int t_flags; int t_unacksegs; } ;

/* Variables and functions */
 int TF_RXWIN0SENT ; 
 int TF_STRETCHACK ; 
 int TH_PUSH ; 
 int maxseg_unacked ; 
 int tcp_delack_enabled ; 

int
tcp_cc_delay_ack(struct tcpcb *tp, struct tcphdr *th)
{
	switch (tcp_delack_enabled) {
	    case 1:
	    case 2:
		if ((tp->t_flags & TF_RXWIN0SENT) == 0 &&
		    (th->th_flags & TH_PUSH) == 0 &&
		    (tp->t_unacksegs == 1))
			return(1);
		break;  
	    case 3:
		if ((tp->t_flags & TF_RXWIN0SENT) == 0 &&
		    (th->th_flags & TH_PUSH) == 0 &&
		    ((tp->t_unacksegs == 1) ||
		    ((tp->t_flags & TF_STRETCHACK) != 0 &&
			tp->t_unacksegs < (maxseg_unacked))))
			return(1);
		break;
	}
	return(0);
}