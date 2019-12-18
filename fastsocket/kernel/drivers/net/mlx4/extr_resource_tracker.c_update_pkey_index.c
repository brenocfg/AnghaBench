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
struct mlx4_priv {int*** virt2phys_pkey; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {scalar_t__ buf; } ;

/* Variables and functions */
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

__attribute__((used)) static void update_pkey_index(struct mlx4_dev *dev, int slave,
			      struct mlx4_cmd_mailbox *inbox)
{
	u8 sched = *(u8 *)(inbox->buf + 64);
	u8 orig_index = *(u8 *)(inbox->buf + 35);
	u8 new_index;
	struct mlx4_priv *priv = mlx4_priv(dev);
	int port;

	port = (sched >> 6 & 1) + 1;

	new_index = priv->virt2phys_pkey[slave][port - 1][orig_index];
	*(u8 *)(inbox->buf + 35) = new_index;
}