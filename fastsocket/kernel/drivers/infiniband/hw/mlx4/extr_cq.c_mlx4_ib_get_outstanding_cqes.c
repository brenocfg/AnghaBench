#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int cons_index; } ;
struct TYPE_3__ {int cqe; } ;
struct mlx4_ib_cq {TYPE_2__ mcq; TYPE_1__ ibcq; } ;

/* Variables and functions */
 scalar_t__ get_sw_cqe (struct mlx4_ib_cq*,int) ; 

__attribute__((used)) static int mlx4_ib_get_outstanding_cqes(struct mlx4_ib_cq *cq)
{
	u32 i;

	i = cq->mcq.cons_index;
	while (get_sw_cqe(cq, i & cq->ibcq.cqe))
		++i;

	return i - cq->mcq.cons_index;
}