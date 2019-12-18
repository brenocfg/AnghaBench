#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_8__ {scalar_t__ from_state; } ;
struct res_eq {TYPE_2__ com; } ;
struct mlx4_slave_event_eq_info {int eqn; int /*<<< orphan*/  token; } ;
struct TYPE_11__ {int /*<<< orphan*/ * gen_eqe_mutex; TYPE_1__* slave_state; } ;
struct TYPE_12__ {TYPE_5__ master; } ;
struct mlx4_priv {TYPE_6__ mfunc; } ;
struct TYPE_9__ {int /*<<< orphan*/  token; } ;
struct TYPE_10__ {TYPE_3__ cmd; } ;
struct mlx4_eqe {size_t type; TYPE_4__ event; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; int /*<<< orphan*/  buf; } ;
struct TYPE_7__ {struct mlx4_slave_event_eq_info* event_eq; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_CMD_GEN_EQE ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_B ; 
 size_t MLX4_EVENT_TYPE_CMD ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  RES_EQ ; 
 scalar_t__ RES_EQ_HW ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int get_res (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_eq**) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd (struct mlx4_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_res (struct mlx4_dev*,int,int,int /*<<< orphan*/ ) ; 

int mlx4_GEN_EQE(struct mlx4_dev *dev, int slave, struct mlx4_eqe *eqe)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_slave_event_eq_info *event_eq;
	struct mlx4_cmd_mailbox *mailbox;
	u32 in_modifier = 0;
	int err;
	int res_id;
	struct res_eq *req;

	if (!priv->mfunc.master.slave_state)
		return -EINVAL;

	event_eq = &priv->mfunc.master.slave_state[slave].event_eq[eqe->type];

	/* Create the event only if the slave is registered */
	if (event_eq->eqn < 0)
		return 0;

	mutex_lock(&priv->mfunc.master.gen_eqe_mutex[slave]);
	res_id = (slave << 8) | event_eq->eqn;
	err = get_res(dev, slave, res_id, RES_EQ, &req);
	if (err)
		goto unlock;

	if (req->com.from_state != RES_EQ_HW) {
		err = -EINVAL;
		goto put;
	}

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox)) {
		err = PTR_ERR(mailbox);
		goto put;
	}

	if (eqe->type == MLX4_EVENT_TYPE_CMD) {
		++event_eq->token;
		eqe->event.cmd.token = cpu_to_be16(event_eq->token);
	}

	memcpy(mailbox->buf, (u8 *) eqe, 28);

	in_modifier = (slave & 0xff) | ((event_eq->eqn & 0xff) << 16);

	err = mlx4_cmd(dev, mailbox->dma, in_modifier, 0,
		       MLX4_CMD_GEN_EQE, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_NATIVE);

	put_res(dev, slave, res_id, RES_EQ);
	mutex_unlock(&priv->mfunc.master.gen_eqe_mutex[slave]);
	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;

put:
	put_res(dev, slave, res_id, RES_EQ);

unlock:
	mutex_unlock(&priv->mfunc.master.gen_eqe_mutex[slave]);
	return err;
}