#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct mlx4_vport_state {int /*<<< orphan*/  mac; } ;
struct TYPE_6__ {TYPE_1__* vf_admin; } ;
struct TYPE_5__ {TYPE_3__ master; } ;
struct mlx4_priv {TYPE_2__ mfunc; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_4__ {struct mlx4_vport_state* vport; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int mlx4_get_slave_indx (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mlx4_info (struct mlx4_dev*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_is_master (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_set_vf_mac(struct mlx4_dev *dev, int port, int vf, u64 mac)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_vport_state *s_info;
	int slave;

	if (!mlx4_is_master(dev))
		return -EPROTONOSUPPORT;

	slave = mlx4_get_slave_indx(dev, vf);
	if (slave < 0)
		return -EINVAL;

	s_info = &priv->mfunc.master.vf_admin[slave].vport[port];
	s_info->mac = mac;
	mlx4_info(dev, "default mac on vf %d port %d to %llX will take afect only after vf restart\n",
		  vf, port, s_info->mac);
	return 0;
}