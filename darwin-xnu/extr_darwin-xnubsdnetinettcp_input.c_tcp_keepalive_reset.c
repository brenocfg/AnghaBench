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
struct tcpcb {scalar_t__ t_rtimo_probes; int /*<<< orphan*/  t_flagsext; int /*<<< orphan*/ * t_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFFSET_FROM_START (struct tcpcb*,int /*<<< orphan*/ ) ; 
 size_t TCPT_KEEP ; 
 int /*<<< orphan*/  TCP_CONN_KEEPIDLE (struct tcpcb*) ; 
 int /*<<< orphan*/  TF_DETECT_READSTALL ; 

inline void
tcp_keepalive_reset(struct tcpcb *tp)
{
	tp->t_timer[TCPT_KEEP] = OFFSET_FROM_START(tp,
		TCP_CONN_KEEPIDLE(tp));
	tp->t_flagsext &= ~(TF_DETECT_READSTALL);
	tp->t_rtimo_probes = 0;
}