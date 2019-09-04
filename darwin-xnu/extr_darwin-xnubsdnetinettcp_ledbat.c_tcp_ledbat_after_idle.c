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
struct tcpcb {int snd_cwnd; int t_maxseg; } ;

/* Variables and functions */
 int bg_ss_fltsz ; 

void
tcp_ledbat_after_idle(struct tcpcb *tp) {
	
	/* Reset the congestion window */
	tp->snd_cwnd = tp->t_maxseg * bg_ss_fltsz;
}