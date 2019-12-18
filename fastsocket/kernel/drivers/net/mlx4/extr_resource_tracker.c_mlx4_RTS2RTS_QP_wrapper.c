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
typedef  int /*<<< orphan*/  u8 ;
struct mlx4_vhcr {int dummy; } ;
struct mlx4_qp_context {int dummy; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {struct mlx4_qp_context* buf; } ;
struct mlx4_cmd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QP_TRANS_RTS2RTS ; 
 int /*<<< orphan*/  adjust_proxy_tun_qkey (struct mlx4_dev*,struct mlx4_vhcr*,struct mlx4_qp_context*) ; 
 int mlx4_GEN_QP_wrapper (struct mlx4_dev*,int,struct mlx4_vhcr*,struct mlx4_cmd_mailbox*,struct mlx4_cmd_mailbox*,struct mlx4_cmd_info*) ; 
 int /*<<< orphan*/  update_gid (struct mlx4_dev*,struct mlx4_cmd_mailbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_pkey_index (struct mlx4_dev*,int,struct mlx4_cmd_mailbox*) ; 
 int verify_qp_parameters (struct mlx4_dev*,struct mlx4_cmd_mailbox*,int /*<<< orphan*/ ,int) ; 

int mlx4_RTS2RTS_QP_wrapper(struct mlx4_dev *dev, int slave,
			    struct mlx4_vhcr *vhcr,
			    struct mlx4_cmd_mailbox *inbox,
			    struct mlx4_cmd_mailbox *outbox,
			    struct mlx4_cmd_info *cmd)
{
	int err;
	struct mlx4_qp_context *context = inbox->buf + 8;

	err = verify_qp_parameters(dev, inbox, QP_TRANS_RTS2RTS, slave);
	if (err)
		return err;

	update_pkey_index(dev, slave, inbox);
	update_gid(dev, inbox, (u8)slave);
	adjust_proxy_tun_qkey(dev, vhcr, context);
	return mlx4_GEN_QP_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
}