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
typedef  scalar_t__ u_int32_t ;
struct tcpcb {scalar_t__ snd_max; int t_flags; } ;
struct TYPE_2__ {int sb_flags; scalar_t__ sb_cc; } ;
struct socket {TYPE_1__ so_snd; } ;
struct inpcb {int dummy; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int SB_SNDBYTE_CNT ; 
 int TF_SENTFIN ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 

inline int32_t
inp_get_sndbytes_allunsent(struct socket *so, u_int32_t th_ack)
{
	struct inpcb *inp = sotoinpcb(so);
	struct tcpcb *tp = intotcpcb(inp);

	if ((so->so_snd.sb_flags & SB_SNDBYTE_CNT) &&
	    so->so_snd.sb_cc > 0) {
		int32_t unsent, sent;
		sent = tp->snd_max - th_ack;
		if (tp->t_flags & TF_SENTFIN)
			sent--;
		unsent = so->so_snd.sb_cc - sent;
		return (unsent);
	}
	return (0);
}