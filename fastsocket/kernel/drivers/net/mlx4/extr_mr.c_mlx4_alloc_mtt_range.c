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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_ALLOC_RES ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 int /*<<< orphan*/  RES_MTT ; 
 int /*<<< orphan*/  RES_OP_RESERVE_AND_MAP ; 
 int __mlx4_alloc_mtt_range (struct mlx4_dev*,int) ; 
 int get_param_l (int /*<<< orphan*/ *) ; 
 int mlx4_cmd_imm (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 
 int /*<<< orphan*/  set_param_l (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u32 mlx4_alloc_mtt_range(struct mlx4_dev *dev, int order)
{
	u64 in_param = 0;
	u64 out_param;
	int err;

	if (mlx4_is_mfunc(dev)) {
		set_param_l(&in_param, order);
		err = mlx4_cmd_imm(dev, in_param, &out_param, RES_MTT,
						       RES_OP_RESERVE_AND_MAP,
						       MLX4_CMD_ALLOC_RES,
						       MLX4_CMD_TIME_CLASS_A,
						       MLX4_CMD_WRAPPED);
		if (err)
			return -1;
		return get_param_l(&out_param);
	}
	return __mlx4_alloc_mtt_range(dev, order);
}