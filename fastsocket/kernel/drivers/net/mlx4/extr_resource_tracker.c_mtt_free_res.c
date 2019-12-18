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
 int /*<<< orphan*/  RES_MTT ; 
 int RES_OP_RESERVE_AND_MAP ; 
 int /*<<< orphan*/  __mlx4_free_mtt_range (struct mlx4_dev*,int,int) ; 
 int get_param_h (int /*<<< orphan*/ *) ; 
 int get_param_l (int /*<<< orphan*/ *) ; 
 int rem_res_range (struct mlx4_dev*,int,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mtt_free_res(struct mlx4_dev *dev, int slave, int op, int cmd,
			u64 in_param, u64 *out_param)
{
	int err = -EINVAL;
	int base;
	int order;

	if (op != RES_OP_RESERVE_AND_MAP)
		return err;

	base = get_param_l(&in_param);
	order = get_param_h(&in_param);
	err = rem_res_range(dev, slave, base, 1, RES_MTT, order);
	if (!err)
		__mlx4_free_mtt_range(dev, base, order);
	return err;
}