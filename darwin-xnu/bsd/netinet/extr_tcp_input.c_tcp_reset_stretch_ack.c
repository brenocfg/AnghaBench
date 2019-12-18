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
struct tcpcb {int t_flags; scalar_t__ rcv_waitforss; int /*<<< orphan*/  t_flagsext; scalar_t__ rcv_unackwin; scalar_t__ rcv_by_unackwin; } ;

/* Variables and functions */
 int /*<<< orphan*/  TF_RCVUNACK_WAITSS ; 
 int TF_STREAMING_ON ; 
 int TF_STRETCHACK ; 
 scalar_t__ tcp_now ; 
 scalar_t__ tcp_rcvunackwin ; 

void
tcp_reset_stretch_ack(struct tcpcb *tp)
{
	tp->t_flags &= ~(TF_STRETCHACK|TF_STREAMING_ON);
	tp->rcv_by_unackwin = 0;
	tp->rcv_unackwin = tcp_now + tcp_rcvunackwin;

	/*
	 * When there is packet loss or packet re-ordering or CWR due to
	 * ECN, the sender's congestion window is reduced. In these states,
	 * generate an ack for every other packet for some time to allow
	 * the sender's congestion window to grow.
	 */
	tp->t_flagsext |= TF_RCVUNACK_WAITSS;
	tp->rcv_waitforss = 0;
}