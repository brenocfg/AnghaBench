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
#define  RES_OP_RESERVE_AND_MAP 128 
 int /*<<< orphan*/  __mlx4_unregister_mac (struct mlx4_dev*,int,int /*<<< orphan*/ ) ; 
 int get_param_l (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_del_from_slave (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mac_free_res(struct mlx4_dev *dev, int slave, int op, int cmd,
			    u64 in_param, u64 *out_param)
{
	int port;
	int err = 0;

	switch (op) {
	case RES_OP_RESERVE_AND_MAP:
		port = get_param_l(out_param);
		mac_del_from_slave(dev, slave, in_param, port);
		__mlx4_unregister_mac(dev, port, in_param);
		break;
	default:
		err = -EINVAL;
		break;
	}

	return err;

}