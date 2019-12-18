#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct mlx4_vport_state {int default_vlan; int default_qos; } ;
struct TYPE_10__ {int /*<<< orphan*/  default_vlan; } ;
struct mlx4_vport_oper_state {TYPE_3__ state; } ;
struct TYPE_12__ {TYPE_4__* slave_state; TYPE_2__* vf_oper; TYPE_1__* vf_admin; } ;
struct TYPE_13__ {TYPE_5__ master; } ;
struct mlx4_priv {TYPE_6__ mfunc; } ;
struct TYPE_14__ {int flags2; } ;
struct mlx4_dev {TYPE_7__ caps; } ;
typedef  enum mlx4_vlan_transition { ____Placeholder_mlx4_vlan_transition } mlx4_vlan_transition ;
struct TYPE_11__ {scalar_t__ active; } ;
struct TYPE_9__ {struct mlx4_vport_oper_state* vport; } ;
struct TYPE_8__ {struct mlx4_vport_state* vport; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int MLX4_DEV_CAP_FLAG2_UPDATE_QP ; 
 int MLX4_DEV_CAP_FLAG2_VLAN_CONTROL ; 
 int MLX4_VGT ; 
 int MLX4_VLAN_TRANSITION_VST_VST ; 
 int calculate_transition (int /*<<< orphan*/ ,int) ; 
 int mlx4_get_slave_indx (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mlx4_info (struct mlx4_dev*,char*,int,int) ; 
 int /*<<< orphan*/  mlx4_is_master (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_master_immediate_activate_vlan_qos (struct mlx4_priv*,int,int) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_set_vf_vlan(struct mlx4_dev *dev, int port, int vf, u16 vlan, u8 qos)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_vport_oper_state *vf_oper;
	struct mlx4_vport_state *vf_admin;
	int slave;
	enum mlx4_vlan_transition vlan_trans;

	if ((!mlx4_is_master(dev)) ||
	    !(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_VLAN_CONTROL))
		return -EPROTONOSUPPORT;

	if ((vlan > 4095) || (qos > 7))
		return -EINVAL;

	slave = mlx4_get_slave_indx(dev, vf);
	if (slave < 0)
		return -EINVAL;

	vf_admin = &priv->mfunc.master.vf_admin[slave].vport[port];
	vf_oper = &priv->mfunc.master.vf_oper[slave].vport[port];

	if ((0 == vlan) && (0 == qos))
		vf_admin->default_vlan = MLX4_VGT;
	else
		vf_admin->default_vlan = vlan;
	vf_admin->default_qos = qos;

	vlan_trans = calculate_transition(vf_oper->state.default_vlan,
					  vf_admin->default_vlan);

	if (priv->mfunc.master.slave_state[slave].active &&
	    dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_UPDATE_QP &&
	    vlan_trans == MLX4_VLAN_TRANSITION_VST_VST) {
		mlx4_info(dev, "updating vf %d port %d config params immediately\n",
			  vf, port);
		mlx4_master_immediate_activate_vlan_qos(priv, slave, port);
	}
	return 0;
}