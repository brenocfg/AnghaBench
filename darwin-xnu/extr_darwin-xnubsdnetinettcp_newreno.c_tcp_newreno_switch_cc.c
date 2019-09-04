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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct tcpcb {int t_maxseg; scalar_t__ t_bytes_acked; int /*<<< orphan*/  snd_cwnd; int /*<<< orphan*/  snd_ssthresh; int /*<<< orphan*/  snd_wnd; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_sockets; } ;
typedef  int /*<<< orphan*/  SInt32 ;

/* Variables and functions */
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/  volatile*) ; 
 int /*<<< orphan*/  TCP_CC_CWND_INIT_BYTES ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ tcp_cc_newreno ; 

void
tcp_newreno_switch_cc(struct tcpcb *tp, uint16_t old_index) {
#pragma unused(old_index)

	uint32_t cwnd = min(tp->snd_wnd, tp->snd_cwnd);
	if (tp->snd_cwnd >= tp->snd_ssthresh) {
		cwnd = cwnd / tp->t_maxseg;
	} else { 
		cwnd = cwnd / 2 / tp->t_maxseg;
	}
	tp->snd_cwnd = max(TCP_CC_CWND_INIT_BYTES, cwnd * tp->t_maxseg);

	/* Start counting bytes for RFC 3465 again */
	tp->t_bytes_acked = 0;

	OSIncrementAtomic((volatile SInt32 *)&tcp_cc_newreno.num_sockets);
}