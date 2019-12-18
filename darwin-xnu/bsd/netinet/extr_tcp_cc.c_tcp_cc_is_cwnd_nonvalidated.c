#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct tcpcb {int t_pipeack; int t_flagsext; int snd_cwnd; TYPE_2__* t_inpcb; } ;
struct TYPE_3__ {scalar_t__ sb_cc; } ;
struct socket {TYPE_1__ so_snd; } ;
struct TYPE_4__ {struct socket* inp_socket; } ;

/* Variables and functions */
 int TF_CWND_NONVALIDATED ; 
 scalar_t__ tcp_check_cwnd_nonvalidated ; 

inline uint32_t
tcp_cc_is_cwnd_nonvalidated(struct tcpcb *tp)
{
	struct socket *so = tp->t_inpcb->inp_socket;
	if (tp->t_pipeack == 0 || tcp_check_cwnd_nonvalidated == 0) {
		tp->t_flagsext &= ~TF_CWND_NONVALIDATED;
		return (0);
	}

	/*
	 * The congestion window is validated if the number of bytes acked
	 * is more than half of the current window or if there is more
	 * data to send in the send socket buffer
	 */
	if (tp->t_pipeack >= (tp->snd_cwnd >> 1) ||
	    (so != NULL && so->so_snd.sb_cc > tp->snd_cwnd))
		tp->t_flagsext &= ~TF_CWND_NONVALIDATED;
	else
		tp->t_flagsext |= TF_CWND_NONVALIDATED;
	return (tp->t_flagsext & TF_CWND_NONVALIDATED);
}