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
typedef  int u8 ;
typedef  int u32 ;
struct mlx4_vhcr {int in_param; int in_modifier; scalar_t__ op_modifier; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int dummy; } ;
struct mlx4_cmd_info {int dummy; } ;
typedef  enum mlx4_steer_type { ____Placeholder_mlx4_steer_type } mlx4_steer_type ;

/* Variables and functions */
 int MLX4_UC_STEER ; 
 int add_promisc_qp (struct mlx4_dev*,int,int,int) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 
 int remove_promisc_qp (struct mlx4_dev*,int,int,int) ; 

int mlx4_PROMISC_wrapper(struct mlx4_dev *dev, int slave,
			 struct mlx4_vhcr *vhcr,
			 struct mlx4_cmd_mailbox *inbox,
			 struct mlx4_cmd_mailbox *outbox,
			 struct mlx4_cmd_info *cmd)
{
	u32 qpn = (u32) vhcr->in_param & 0xffffffff;
	u8 port = vhcr->in_param >> 62;
	enum mlx4_steer_type steer = vhcr->in_modifier;

	/* Promiscuous unicast is not allowed in mfunc */
	if (mlx4_is_mfunc(dev) && steer == MLX4_UC_STEER)
		return 0;

	if (vhcr->op_modifier)
		return add_promisc_qp(dev, port, steer, qpn);
	else
		return remove_promisc_qp(dev, port, steer, qpn);
}