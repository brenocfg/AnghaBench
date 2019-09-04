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
struct tcpcb {scalar_t__ t_lossflightsize; scalar_t__ t_pipeack_ind; int /*<<< orphan*/  t_pipeack_sample; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 

inline void
tcp_clear_pipeack_state(struct tcpcb *tp)
{
	bzero(tp->t_pipeack_sample, sizeof(tp->t_pipeack_sample));
	tp->t_pipeack_ind = 0;
	tp->t_lossflightsize = 0;
}