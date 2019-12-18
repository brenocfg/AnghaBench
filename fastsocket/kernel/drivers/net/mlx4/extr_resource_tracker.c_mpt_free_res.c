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
struct res_mpt {int key; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RES_MPT ; 
 int /*<<< orphan*/  RES_MPT_RESERVED ; 
#define  RES_OP_MAP_ICM 129 
#define  RES_OP_RESERVE 128 
 int /*<<< orphan*/  __mlx4_mpt_free_icm (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  __mlx4_mpt_release (struct mlx4_dev*,int) ; 
 int get_param_l (int /*<<< orphan*/ *) ; 
 int get_res (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_mpt**) ; 
 int mpt_mask (struct mlx4_dev*) ; 
 int mr_res_start_move_to (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_mpt**) ; 
 int /*<<< orphan*/  put_res (struct mlx4_dev*,int,int,int /*<<< orphan*/ ) ; 
 int rem_res_range (struct mlx4_dev*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_end_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mpt_free_res(struct mlx4_dev *dev, int slave, int op, int cmd,
			u64 in_param)
{
	int err = -EINVAL;
	int index;
	int id;
	struct res_mpt *mpt;

	switch (op) {
	case RES_OP_RESERVE:
		index = get_param_l(&in_param);
		id = index & mpt_mask(dev);
		err = get_res(dev, slave, id, RES_MPT, &mpt);
		if (err)
			break;
		index = mpt->key;
		put_res(dev, slave, id, RES_MPT);

		err = rem_res_range(dev, slave, id, 1, RES_MPT, 0);
		if (err)
			break;
		__mlx4_mpt_release(dev, index);
		break;
	case RES_OP_MAP_ICM:
			index = get_param_l(&in_param);
			id = index & mpt_mask(dev);
			err = mr_res_start_move_to(dev, slave, id,
						   RES_MPT_RESERVED, &mpt);
			if (err)
				return err;

			__mlx4_mpt_free_icm(dev, mpt->key);
			res_end_move(dev, slave, RES_MPT, id);
			return err;
		break;
	default:
		err = -EINVAL;
		break;
	}
	return err;
}