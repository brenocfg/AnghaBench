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
typedef  scalar_t__ u_int32_t ;
struct tcpcb {scalar_t__* t_pipeack_sample; } ;

/* Variables and functions */

inline u_int32_t
tcp_get_max_pipeack(struct tcpcb *tp)
{
	u_int32_t max_pipeack = 0;
	max_pipeack = (tp->t_pipeack_sample[0] > tp->t_pipeack_sample[1]) ?
	    tp->t_pipeack_sample[0] : tp->t_pipeack_sample[1];
	max_pipeack = (tp->t_pipeack_sample[2] > max_pipeack) ?
	    tp->t_pipeack_sample[2] : max_pipeack;

	return (max_pipeack);
}