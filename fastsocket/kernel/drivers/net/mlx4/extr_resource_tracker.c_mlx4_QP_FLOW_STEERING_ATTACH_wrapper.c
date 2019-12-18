#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct res_qp {int /*<<< orphan*/  ref_count; } ;
struct mlx4_vhcr {int in_modifier; int /*<<< orphan*/  out_param; } ;
struct mlx4_resource_tracker {TYPE_3__* slave_list; } ;
struct TYPE_5__ {struct mlx4_resource_tracker res_tracker; } ;
struct TYPE_6__ {TYPE_1__ master; } ;
struct mlx4_priv {TYPE_2__ mfunc; } ;
struct mlx4_net_trans_rule_hw_eth {int dummy; } ;
struct mlx4_net_trans_rule_hw_ctrl {int /*<<< orphan*/  qpn; } ;
struct TYPE_8__ {scalar_t__ steering_mode; } ;
struct mlx4_dev {TYPE_4__ caps; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; scalar_t__ buf; } ;
struct mlx4_cmd_info {int dummy; } ;
struct list_head {int dummy; } ;
struct _rule_hw {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {struct list_head* res_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
#define  MLX4_NET_TRANS_RULE_ID_ETH 132 
#define  MLX4_NET_TRANS_RULE_ID_IB 131 
#define  MLX4_NET_TRANS_RULE_ID_IPV4 130 
#define  MLX4_NET_TRANS_RULE_ID_TCP 129 
#define  MLX4_NET_TRANS_RULE_ID_UDP 128 
 int /*<<< orphan*/  MLX4_QP_FLOW_STEERING_ATTACH ; 
 int /*<<< orphan*/  MLX4_QP_FLOW_STEERING_DETACH ; 
 scalar_t__ MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 int /*<<< orphan*/  RES_FS_RULE ; 
 size_t RES_MAC ; 
 int /*<<< orphan*/  RES_QP ; 
 int /*<<< orphan*/  add_eth_header (struct mlx4_dev*,int,struct mlx4_cmd_mailbox*,struct list_head*,int) ; 
 int add_res_range (struct mlx4_dev*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int get_res (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_qp**) ; 
 int map_hw_to_sw_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_cmd (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_cmd_imm (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  put_res (struct mlx4_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_eth_header_mac (int,struct _rule_hw*,struct list_head*) ; 

int mlx4_QP_FLOW_STEERING_ATTACH_wrapper(struct mlx4_dev *dev, int slave,
					 struct mlx4_vhcr *vhcr,
					 struct mlx4_cmd_mailbox *inbox,
					 struct mlx4_cmd_mailbox *outbox,
					 struct mlx4_cmd_info *cmd)
{

	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	struct list_head *rlist = &tracker->slave_list[slave].res_list[RES_MAC];
	int err;
	int qpn;
	struct res_qp *rqp;
	struct mlx4_net_trans_rule_hw_ctrl *ctrl;
	struct _rule_hw  *rule_header;
	int header_id;

	if (dev->caps.steering_mode !=
	    MLX4_STEERING_MODE_DEVICE_MANAGED)
		return -EOPNOTSUPP;

	ctrl = (struct mlx4_net_trans_rule_hw_ctrl *)inbox->buf;
	qpn = be32_to_cpu(ctrl->qpn) & 0xffffff;
	err = get_res(dev, slave, qpn, RES_QP, &rqp);
	if (err) {
		pr_err("Steering rule with qpn 0x%x rejected.\n", qpn);
		return err;
	}
	rule_header = (struct _rule_hw *)(ctrl + 1);
	header_id = map_hw_to_sw_id(be16_to_cpu(rule_header->id));

	switch (header_id) {
	case MLX4_NET_TRANS_RULE_ID_ETH:
		if (validate_eth_header_mac(slave, rule_header, rlist)) {
			err = -EINVAL;
			goto err_put;
		}
		break;
	case MLX4_NET_TRANS_RULE_ID_IB:
		break;
	case MLX4_NET_TRANS_RULE_ID_IPV4:
	case MLX4_NET_TRANS_RULE_ID_TCP:
	case MLX4_NET_TRANS_RULE_ID_UDP:
		pr_warn("Can't attach FS rule without L2 headers, adding L2 header.\n");
		if (add_eth_header(dev, slave, inbox, rlist, header_id)) {
			err = -EINVAL;
			goto err_put;
		}
		vhcr->in_modifier +=
			sizeof(struct mlx4_net_trans_rule_hw_eth) >> 2;
		break;
	default:
		pr_err("Corrupted mailbox.\n");
		err = -EINVAL;
		goto err_put;
	}

	err = mlx4_cmd_imm(dev, inbox->dma, &vhcr->out_param,
			   vhcr->in_modifier, 0,
			   MLX4_QP_FLOW_STEERING_ATTACH, MLX4_CMD_TIME_CLASS_A,
			   MLX4_CMD_NATIVE);
	if (err)
		goto err_put;

	err = add_res_range(dev, slave, vhcr->out_param, 1, RES_FS_RULE, qpn);
	if (err) {
		mlx4_err(dev, "Fail to add flow steering resources.\n ");
		/* detach rule*/
		mlx4_cmd(dev, vhcr->out_param, 0, 0,
			 MLX4_QP_FLOW_STEERING_DETACH, MLX4_CMD_TIME_CLASS_A,
			 MLX4_CMD_NATIVE);
		goto err_put;
	}
	atomic_inc(&rqp->ref_count);
err_put:
	put_res(dev, slave, qpn, RES_QP);
	return err;
}