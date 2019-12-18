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
typedef  int /*<<< orphan*/  u16 ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct mlx4_ib_cq {int /*<<< orphan*/  mcq; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int mlx4_cq_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_ib_cq* to_mcq (struct ib_cq*) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

int mlx4_ib_modify_cq(struct ib_cq *cq, u16 cq_count, u16 cq_period)
{
	struct mlx4_ib_cq *mcq = to_mcq(cq);
	struct mlx4_ib_dev *dev = to_mdev(cq->device);

	return mlx4_cq_modify(dev->dev, &mcq->mcq, cq_count, cq_period);
}