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
typedef  scalar_t__ uint32_t ;
struct tcphdr {int dummy; } ;
struct tcpcb {scalar_t__ t_maxseg; TYPE_1__* t_ccstate; int /*<<< orphan*/  snd_wnd; int /*<<< orphan*/  snd_cwnd; } ;
struct TYPE_2__ {scalar_t__ cub_tcp_win; scalar_t__ cub_tcp_bytes_acked; } ;

/* Variables and functions */
 scalar_t__ BYTES_ACKED (struct tcphdr*,struct tcpcb*) ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
tcp_cubic_tcpwin(struct tcpcb *tp, struct tcphdr *th)
{
	if (tp->t_ccstate->cub_tcp_win == 0) {
		tp->t_ccstate->cub_tcp_win = min(tp->snd_cwnd, tp->snd_wnd);
		tp->t_ccstate->cub_tcp_bytes_acked = 0;
	} else {
		tp->t_ccstate->cub_tcp_bytes_acked +=
		    BYTES_ACKED(th, tp);
		if (tp->t_ccstate->cub_tcp_bytes_acked >=
		    tp->t_ccstate->cub_tcp_win) {
			tp->t_ccstate->cub_tcp_bytes_acked -=
			    tp->t_ccstate->cub_tcp_win;
			tp->t_ccstate->cub_tcp_win += tp->t_maxseg;
		}
	}	
	return (tp->t_ccstate->cub_tcp_win);
}