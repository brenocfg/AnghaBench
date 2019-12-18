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
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  RES_OP_MAP_ICM 129 
#define  RES_OP_RESERVE 128 
 int /*<<< orphan*/  RES_QP ; 
 int /*<<< orphan*/  RES_QP_RESERVED ; 
 int /*<<< orphan*/  __mlx4_qp_free_icm (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  __mlx4_qp_release_range (struct mlx4_dev*,int,int) ; 
 int /*<<< orphan*/  fw_reserved (struct mlx4_dev*,int) ; 
 int get_param_h (int /*<<< orphan*/ *) ; 
 int get_param_l (int /*<<< orphan*/ *) ; 
 int qp_res_start_move_to (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rem_res_range (struct mlx4_dev*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_end_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  valid_reserved (struct mlx4_dev*,int,int) ; 

__attribute__((used)) static int qp_free_res(struct mlx4_dev *dev, int slave, int op, int cmd,
		       u64 in_param)
{
	int err;
	int count;
	int base;
	int qpn;

	switch (op) {
	case RES_OP_RESERVE:
		base = get_param_l(&in_param) & 0x7fffff;
		count = get_param_h(&in_param);
		err = rem_res_range(dev, slave, base, count, RES_QP, 0);
		if (err)
			break;
		__mlx4_qp_release_range(dev, base, count);
		break;
	case RES_OP_MAP_ICM:
		qpn = get_param_l(&in_param) & 0x7fffff;
		err = qp_res_start_move_to(dev, slave, qpn, RES_QP_RESERVED,
					   NULL, 0);
		if (err)
			return err;

		if (!fw_reserved(dev, qpn))
			__mlx4_qp_free_icm(dev, qpn);

		res_end_move(dev, slave, RES_QP, qpn);

		if (valid_reserved(dev, slave, qpn))
			err = rem_res_range(dev, slave, qpn, 1, RES_QP, 0);
		break;
	default:
		err = -EINVAL;
		break;
	}
	return err;
}