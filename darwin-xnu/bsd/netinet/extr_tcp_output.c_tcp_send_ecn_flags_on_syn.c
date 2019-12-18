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
struct tcpcb {int ecn_flags; int t_flagsext; } ;
struct socket {int so_flags; } ;

/* Variables and functions */
 int SOF_MP_SUBFLOW ; 
 int TE_SETUPSENT ; 
 int TF_FASTOPEN ; 

__attribute__((used)) static inline bool
tcp_send_ecn_flags_on_syn(struct tcpcb *tp, struct socket *so)
{
	return(!((tp->ecn_flags & TE_SETUPSENT) ||
	    (so->so_flags & SOF_MP_SUBFLOW) ||
	    (tp->t_flagsext & TF_FASTOPEN)));
}