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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx4_dev {int /*<<< orphan*/  pdev; } ;
struct TYPE_3__ {scalar_t__ use_events; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;

/* Variables and functions */
 int EIO ; 
 int mlx4_cmd_poll (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int mlx4_cmd_wait (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ mlx4_is_master (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_is_mfunc (struct mlx4_dev*) ; 
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_slave_cmd (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ pci_channel_offline (int /*<<< orphan*/ ) ; 

int __mlx4_cmd(struct mlx4_dev *dev, u64 in_param, u64 *out_param,
	       int out_is_imm, u32 in_modifier, u8 op_modifier,
	       u16 op, unsigned long timeout, int native)
{
	if (pci_channel_offline(dev->pdev))
		return -EIO;

	if (!mlx4_is_mfunc(dev) || (native && mlx4_is_master(dev))) {
		if (mlx4_priv(dev)->cmd.use_events)
			return mlx4_cmd_wait(dev, in_param, out_param,
					     out_is_imm, in_modifier,
					     op_modifier, op, timeout);
		else
			return mlx4_cmd_poll(dev, in_param, out_param,
					     out_is_imm, in_modifier,
					     op_modifier, op, timeout);
	}
	return mlx4_slave_cmd(dev, in_param, out_param, out_is_imm,
			      in_modifier, op_modifier, op, timeout);
}