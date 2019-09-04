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
struct tcpcb {scalar_t__ t_tfo_probe_state; } ;

/* Variables and functions */
 scalar_t__ TFO_PROBE_NONE ; 
 scalar_t__ TFO_PROBE_PROBING ; 

__attribute__((used)) static void
tcp_tfo_rcv_data(struct tcpcb *tp)
{
	/* Transition from PROBING to NONE as data has been received */
	if (tp->t_tfo_probe_state >= TFO_PROBE_PROBING)
		tp->t_tfo_probe_state = TFO_PROBE_NONE;
}