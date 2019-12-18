#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  res_id; } ;
struct res_mtt {TYPE_2__ com; int /*<<< orphan*/  ref_count; } ;
struct res_eq {struct res_mtt* mtt; } ;
struct mlx4_vhcr {int in_modifier; } ;
struct mlx4_eq_context {int dummy; } ;
struct TYPE_3__ {int mtt_entry_sz; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {struct mlx4_eq_context* buf; } ;
struct mlx4_cmd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RES_EQ ; 
 int /*<<< orphan*/  RES_EQ_HW ; 
 int /*<<< orphan*/  RES_MTT ; 
 int add_res_range (struct mlx4_dev*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int check_mtt_range (struct mlx4_dev*,int,int,int,struct res_mtt*) ; 
 int eq_get_mtt_addr (struct mlx4_eq_context*) ; 
 int eq_get_mtt_size (struct mlx4_eq_context*) ; 
 int eq_res_start_move_to (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_eq**) ; 
 int get_res (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_mtt**) ; 
 int mlx4_DMA_wrapper (struct mlx4_dev*,int,struct mlx4_vhcr*,struct mlx4_cmd_mailbox*,struct mlx4_cmd_mailbox*,struct mlx4_cmd_info*) ; 
 int /*<<< orphan*/  put_res (struct mlx4_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rem_res_range (struct mlx4_dev*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_abort_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  res_end_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 

int mlx4_SW2HW_EQ_wrapper(struct mlx4_dev *dev, int slave,
			  struct mlx4_vhcr *vhcr,
			  struct mlx4_cmd_mailbox *inbox,
			  struct mlx4_cmd_mailbox *outbox,
			  struct mlx4_cmd_info *cmd)
{
	int err;
	int eqn = vhcr->in_modifier;
	int res_id = (slave << 8) | eqn;
	struct mlx4_eq_context *eqc = inbox->buf;
	int mtt_base = eq_get_mtt_addr(eqc) / dev->caps.mtt_entry_sz;
	int mtt_size = eq_get_mtt_size(eqc);
	struct res_eq *eq;
	struct res_mtt *mtt;

	err = add_res_range(dev, slave, res_id, 1, RES_EQ, 0);
	if (err)
		return err;
	err = eq_res_start_move_to(dev, slave, res_id, RES_EQ_HW, &eq);
	if (err)
		goto out_add;

	err = get_res(dev, slave, mtt_base, RES_MTT, &mtt);
	if (err)
		goto out_move;

	err = check_mtt_range(dev, slave, mtt_base, mtt_size, mtt);
	if (err)
		goto out_put;

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	if (err)
		goto out_put;

	atomic_inc(&mtt->ref_count);
	eq->mtt = mtt;
	put_res(dev, slave, mtt->com.res_id, RES_MTT);
	res_end_move(dev, slave, RES_EQ, res_id);
	return 0;

out_put:
	put_res(dev, slave, mtt->com.res_id, RES_MTT);
out_move:
	res_abort_move(dev, slave, RES_EQ, res_id);
out_add:
	rem_res_range(dev, slave, res_id, 1, RES_EQ, 0);
	return err;
}