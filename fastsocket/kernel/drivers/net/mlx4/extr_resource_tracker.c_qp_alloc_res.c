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
 int /*<<< orphan*/  RES_QP_MAPPED ; 
 int __mlx4_qp_alloc_icm (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  __mlx4_qp_release_range (struct mlx4_dev*,int,int) ; 
 int __mlx4_qp_reserve_range (struct mlx4_dev*,int,int,int*) ; 
 int add_res_range (struct mlx4_dev*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_reserved (struct mlx4_dev*,int) ; 
 int get_param_h (int /*<<< orphan*/ *) ; 
 int get_param_l (int /*<<< orphan*/ *) ; 
 int qp_res_start_move_to (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  res_abort_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  res_end_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_param_l (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  valid_reserved (struct mlx4_dev*,int,int) ; 

__attribute__((used)) static int qp_alloc_res(struct mlx4_dev *dev, int slave, int op, int cmd,
			u64 in_param, u64 *out_param)
{
	int err;
	int count;
	int align;
	int base;
	int qpn;

	switch (op) {
	case RES_OP_RESERVE:
		count = get_param_l(&in_param);
		align = get_param_h(&in_param);
		err = __mlx4_qp_reserve_range(dev, count, align, &base);
		if (err)
			return err;

		err = add_res_range(dev, slave, base, count, RES_QP, 0);
		if (err) {
			__mlx4_qp_release_range(dev, base, count);
			return err;
		}
		set_param_l(out_param, base);
		break;
	case RES_OP_MAP_ICM:
		qpn = get_param_l(&in_param) & 0x7fffff;
		if (valid_reserved(dev, slave, qpn)) {
			err = add_res_range(dev, slave, qpn, 1, RES_QP, 0);
			if (err)
				return err;
		}

		err = qp_res_start_move_to(dev, slave, qpn, RES_QP_MAPPED,
					   NULL, 1);
		if (err)
			return err;

		if (!fw_reserved(dev, qpn)) {
			err = __mlx4_qp_alloc_icm(dev, qpn);
			if (err) {
				res_abort_move(dev, slave, RES_QP, qpn);
				return err;
			}
		}

		res_end_move(dev, slave, RES_QP, qpn);
		break;

	default:
		err = -EINVAL;
		break;
	}
	return err;
}