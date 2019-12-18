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
struct mlx4_vport_state {scalar_t__ default_vlan; } ;
struct mlx4_vport_oper_state {int /*<<< orphan*/  vlan_idx; struct mlx4_vport_state state; } ;
struct TYPE_7__ {TYPE_2__* vf_admin; TYPE_1__* vf_oper; } ;
struct TYPE_8__ {TYPE_3__ master; } ;
struct mlx4_priv {int /*<<< orphan*/  dev; TYPE_4__ mfunc; } ;
struct TYPE_6__ {struct mlx4_vport_state* vport; } ;
struct TYPE_5__ {struct mlx4_vport_oper_state* vport; } ;

/* Variables and functions */
 int MLX4_MAX_PORTS ; 
 scalar_t__ MLX4_VGT ; 
 int /*<<< orphan*/  NO_INDX ; 
 int __mlx4_register_vlan (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mlx4_warn (int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static int mlx4_master_activate_admin_state(struct mlx4_priv *priv, int slave)
{
	int port, err;
	struct mlx4_vport_state *vp_admin;
	struct mlx4_vport_oper_state *vp_oper;

	for (port = 1; port <= MLX4_MAX_PORTS; port++) {
		vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
		vp_admin = &priv->mfunc.master.vf_admin[slave].vport[port];
		vp_oper->state = *vp_admin;
		if (MLX4_VGT != vp_admin->default_vlan) {
			err = __mlx4_register_vlan(&priv->dev, port,
						   vp_admin->default_vlan, &(vp_oper->vlan_idx));
			if (err) {
				vp_oper->vlan_idx = NO_INDX;
				mlx4_warn((&priv->dev),
					  "No vlan resorces slave %d, port %d\n",
					  slave, port);
				return err;
			}
			mlx4_dbg((&(priv->dev)), "alloc vlan %d idx  %d slave %d port %d\n",
				 (int)(vp_oper->state.default_vlan),
				 vp_oper->vlan_idx, slave, port);
		}
	}
	return 0;
}