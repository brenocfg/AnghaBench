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
struct mlx4_srq {int /*<<< orphan*/  srqn; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int mlx4_ARM_SRQ (struct mlx4_dev*,int /*<<< orphan*/ ,int) ; 

int mlx4_srq_arm(struct mlx4_dev *dev, struct mlx4_srq *srq, int limit_watermark)
{
	return mlx4_ARM_SRQ(dev, srq->srqn, limit_watermark);
}