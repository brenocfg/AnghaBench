#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mlx4_vhcr {int in_modifier; } ;
struct TYPE_9__ {int* init_port_ref; TYPE_3__* slave_state; TYPE_2__* qp0_state; } ;
struct TYPE_10__ {TYPE_4__ master; } ;
struct mlx4_priv {TYPE_5__ mfunc; } ;
struct TYPE_6__ {scalar_t__* port_mask; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {int dummy; } ;
struct mlx4_cmd_info {int dummy; } ;
struct TYPE_8__ {int init_port_mask; } ;
struct TYPE_7__ {scalar_t__ port_active; int /*<<< orphan*/  qp0_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_CLOSE_PORT ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 scalar_t__ MLX4_PORT_TYPE_IB ; 
 int mlx4_cmd (struct mlx4_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mlx4_master_func_num (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_CLOSE_PORT_wrapper(struct mlx4_dev *dev, int slave,
			    struct mlx4_vhcr *vhcr,
			    struct mlx4_cmd_mailbox *inbox,
			    struct mlx4_cmd_mailbox *outbox,
			    struct mlx4_cmd_info *cmd)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int port = vhcr->in_modifier;
	int err;

	if (!(priv->mfunc.master.slave_state[slave].init_port_mask &
	    (1 << port)))
		return 0;

	if (dev->caps.port_mask[port] != MLX4_PORT_TYPE_IB) {
		if (priv->mfunc.master.init_port_ref[port] == 1) {
			err = mlx4_cmd(dev, 0, port, 0, MLX4_CMD_CLOSE_PORT,
				       1000, MLX4_CMD_NATIVE);
			if (err)
				return err;
		}
		priv->mfunc.master.slave_state[slave].init_port_mask &= ~(1 << port);
	} else {
		/* infiniband port */
		if (slave == mlx4_master_func_num(dev)) {
			if (!priv->mfunc.master.qp0_state[port].qp0_active &&
			    priv->mfunc.master.qp0_state[port].port_active) {
				err = mlx4_cmd(dev, 0, port, 0, MLX4_CMD_CLOSE_PORT,
					       1000, MLX4_CMD_NATIVE);
				if (err)
					return err;
				priv->mfunc.master.slave_state[slave].init_port_mask &= ~(1 << port);
				priv->mfunc.master.qp0_state[port].port_active = 0;
			}
		} else
			priv->mfunc.master.slave_state[slave].init_port_mask &= ~(1 << port);
	}
	--priv->mfunc.master.init_port_ref[port];
	return 0;
}