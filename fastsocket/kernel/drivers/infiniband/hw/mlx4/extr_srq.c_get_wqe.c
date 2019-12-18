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
struct TYPE_2__ {int wqe_shift; } ;
struct mlx4_ib_srq {TYPE_1__ msrq; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 void* mlx4_buf_offset (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void *get_wqe(struct mlx4_ib_srq *srq, int n)
{
	return mlx4_buf_offset(&srq->buf, n << srq->msrq.wqe_shift);
}