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
struct tcpcb {TYPE_1__* t_ccstate; } ;
struct TYPE_2__ {scalar_t__ cub_target_win; scalar_t__ cub_epoch_period; scalar_t__ cub_tcp_bytes_acked; scalar_t__ cub_tcp_win; scalar_t__ cub_origin_point; scalar_t__ cub_epoch_start; scalar_t__ cub_last_max; } ;

/* Variables and functions */

__attribute__((used)) static inline void tcp_cubic_clear_state(struct tcpcb *tp)
{
	tp->t_ccstate->cub_last_max = 0;
	tp->t_ccstate->cub_epoch_start = 0;
	tp->t_ccstate->cub_origin_point = 0;
	tp->t_ccstate->cub_tcp_win = 0;
	tp->t_ccstate->cub_tcp_bytes_acked = 0;
	tp->t_ccstate->cub_epoch_period = 0;
	tp->t_ccstate->cub_target_win = 0;
}