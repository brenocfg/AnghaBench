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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct mlx4_qp {int dummy; } ;
struct TYPE_2__ {int steering_mode; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
typedef  enum mlx4_steer_type { ____Placeholder_mlx4_steer_type } mlx4_steer_type ;
typedef  enum mlx4_protocol { ____Placeholder_mlx4_protocol } mlx4_protocol ;

/* Variables and functions */
 int EINVAL ; 
#define  MLX4_STEERING_MODE_B0 129 
#define  MLX4_STEERING_MODE_DEVICE_MANAGED 128 
 int mlx4_qp_attach_common (struct mlx4_dev*,struct mlx4_qp*,int /*<<< orphan*/ *,int,int,int) ; 
 int mlx4_trans_to_dmfs_attach (struct mlx4_dev*,struct mlx4_qp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qp_attach(struct mlx4_dev *dev, struct mlx4_qp *qp, u8 gid[16],
		     int block_loopback, enum mlx4_protocol prot,
		     enum mlx4_steer_type type, u64 *reg_id)
{
	switch (dev->caps.steering_mode) {
	case MLX4_STEERING_MODE_DEVICE_MANAGED:
		return mlx4_trans_to_dmfs_attach(dev, qp, gid, gid[5],
						block_loopback, prot,
						reg_id);
	case MLX4_STEERING_MODE_B0:
		return mlx4_qp_attach_common(dev, qp, gid,
					    block_loopback, prot, type);
	default:
		return -EINVAL;
	}
}