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
struct tcpcb {int /*<<< orphan*/ * t_timer; int /*<<< orphan*/  t_tfo_probe_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFFSET_FROM_START (struct tcpcb*,int /*<<< orphan*/ ) ; 
 size_t TCPT_KEEP ; 
 int /*<<< orphan*/  TCP_REXMTVAL (struct tcpcb*) ; 
 int /*<<< orphan*/  TFO_PROBE_PROBING ; 

__attribute__((used)) static void
tcp_tfo_rcv_probe(struct tcpcb *tp, int tlen)
{
	if (tlen != 0)
		return;

	tp->t_tfo_probe_state = TFO_PROBE_PROBING;

	/*
	 * We send the probe out rather quickly (after one RTO). It does not
	 * really hurt that much, it's only one additional segment on the wire.
	 */
	tp->t_timer[TCPT_KEEP] = OFFSET_FROM_START(tp, (TCP_REXMTVAL(tp)));
}