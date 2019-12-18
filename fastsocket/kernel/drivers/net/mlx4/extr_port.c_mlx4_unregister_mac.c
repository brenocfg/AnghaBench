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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_FREE_RES ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 int /*<<< orphan*/  RES_MAC ; 
 int /*<<< orphan*/  RES_OP_RESERVE_AND_MAP ; 
 int /*<<< orphan*/  __mlx4_unregister_mac (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_cmd_imm (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 
 int /*<<< orphan*/  set_param_l (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mlx4_unregister_mac(struct mlx4_dev *dev, u8 port, u64 mac)
{
	u64 out_param = 0;

	if (mlx4_is_mfunc(dev)) {
		set_param_l(&out_param, port);
		(void) mlx4_cmd_imm(dev, mac, &out_param, RES_MAC,
				    RES_OP_RESERVE_AND_MAP, MLX4_CMD_FREE_RES,
				    MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		return;
	}
	__mlx4_unregister_mac(dev, port, mac);
	return;
}