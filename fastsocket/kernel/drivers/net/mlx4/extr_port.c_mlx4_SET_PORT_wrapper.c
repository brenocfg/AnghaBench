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
struct mlx4_vhcr {int /*<<< orphan*/  op_modifier; int /*<<< orphan*/  in_modifier; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int dummy; } ;
struct mlx4_cmd_info {int dummy; } ;

/* Variables and functions */
 int mlx4_common_set_port (struct mlx4_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx4_cmd_mailbox*) ; 

int mlx4_SET_PORT_wrapper(struct mlx4_dev *dev, int slave,
			  struct mlx4_vhcr *vhcr,
			  struct mlx4_cmd_mailbox *inbox,
			  struct mlx4_cmd_mailbox *outbox,
			  struct mlx4_cmd_info *cmd)
{
	return mlx4_common_set_port(dev, slave, vhcr->in_modifier,
				    vhcr->op_modifier, inbox);
}