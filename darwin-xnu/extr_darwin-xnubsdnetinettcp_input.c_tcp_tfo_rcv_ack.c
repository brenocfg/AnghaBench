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
struct tcphdr {scalar_t__ th_seq; } ;
struct tcpcb {scalar_t__ t_tfo_probe_state; scalar_t__ t_tfo_probes; scalar_t__ rcv_nxt; int /*<<< orphan*/ * t_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFFSET_FROM_START (struct tcpcb*,int /*<<< orphan*/ ) ; 
 scalar_t__ SEQ_GT (scalar_t__,scalar_t__) ; 
 size_t TCPT_KEEP ; 
 int /*<<< orphan*/  TCP_REXMTVAL (struct tcpcb*) ; 
 scalar_t__ TFO_PROBE_NONE ; 
 scalar_t__ TFO_PROBE_PROBING ; 
 scalar_t__ TFO_PROBE_WAIT_DATA ; 

__attribute__((used)) static void
tcp_tfo_rcv_ack(struct tcpcb *tp, struct tcphdr *th)
{
	if (tp->t_tfo_probe_state == TFO_PROBE_PROBING &&
	    tp->t_tfo_probes > 0) {
		if (th->th_seq == tp->rcv_nxt) {
			/* No hole, so stop probing */
			tp->t_tfo_probe_state = TFO_PROBE_NONE;
		} else if (SEQ_GT(th->th_seq, tp->rcv_nxt)) {
			/* There is a hole! Wait a bit for data... */
			tp->t_tfo_probe_state = TFO_PROBE_WAIT_DATA;
			tp->t_timer[TCPT_KEEP] = OFFSET_FROM_START(tp,
			    TCP_REXMTVAL(tp));
		}
	}
}