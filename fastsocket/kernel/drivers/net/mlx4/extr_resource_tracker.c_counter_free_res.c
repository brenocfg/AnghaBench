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
 int /*<<< orphan*/  RES_COUNTER ; 
 int RES_OP_RESERVE ; 
 int /*<<< orphan*/  __mlx4_counter_free (struct mlx4_dev*,int) ; 
 int get_param_l (int /*<<< orphan*/ *) ; 
 int rem_res_range (struct mlx4_dev*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int counter_free_res(struct mlx4_dev *dev, int slave, int op, int cmd,
			    u64 in_param, u64 *out_param)
{
	int index;
	int err;

	if (op != RES_OP_RESERVE)
		return -EINVAL;

	index = get_param_l(&in_param);
	err = rem_res_range(dev, slave, index, 1, RES_COUNTER, 0);
	if (err)
		return err;

	__mlx4_counter_free(dev, index);

	return err;
}