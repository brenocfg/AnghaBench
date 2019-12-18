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
struct res_qp {int /*<<< orphan*/  qpn; int /*<<< orphan*/  ref_count; } ;
struct res_fs_rule {int /*<<< orphan*/  qpn; int /*<<< orphan*/  ref_count; } ;
struct mlx4_vhcr {int /*<<< orphan*/  in_param; } ;
struct TYPE_2__ {scalar_t__ steering_mode; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {int dummy; } ;
struct mlx4_cmd_info {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_QP_FLOW_STEERING_DETACH ; 
 scalar_t__ MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 int /*<<< orphan*/  RES_FS_RULE ; 
 int /*<<< orphan*/  RES_QP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int get_res (struct mlx4_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct res_qp**) ; 
 int mlx4_cmd (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*) ; 
 int /*<<< orphan*/  put_res (struct mlx4_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rem_res_range (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx4_QP_FLOW_STEERING_DETACH_wrapper(struct mlx4_dev *dev, int slave,
					 struct mlx4_vhcr *vhcr,
					 struct mlx4_cmd_mailbox *inbox,
					 struct mlx4_cmd_mailbox *outbox,
					 struct mlx4_cmd_info *cmd)
{
	int err;
	struct res_qp *rqp;
	struct res_fs_rule *rrule;

	if (dev->caps.steering_mode !=
	    MLX4_STEERING_MODE_DEVICE_MANAGED)
		return -EOPNOTSUPP;

	err = get_res(dev, slave, vhcr->in_param, RES_FS_RULE, &rrule);
	if (err)
		return err;
	/* Release the rule form busy state before removal */
	put_res(dev, slave, vhcr->in_param, RES_FS_RULE);
	err = get_res(dev, slave, rrule->qpn, RES_QP, &rqp);
	if (err)
		return err;

	err = rem_res_range(dev, slave, vhcr->in_param, 1, RES_FS_RULE, 0);
	if (err) {
		mlx4_err(dev, "Fail to remove flow steering resources.\n ");
		goto out;
	}

	err = mlx4_cmd(dev, vhcr->in_param, 0, 0,
		       MLX4_QP_FLOW_STEERING_DETACH, MLX4_CMD_TIME_CLASS_A,
		       MLX4_CMD_NATIVE);
	if (!err)
		atomic_dec(&rqp->ref_count);
out:
	put_res(dev, slave, rrule->qpn, RES_QP);
	return err;
}