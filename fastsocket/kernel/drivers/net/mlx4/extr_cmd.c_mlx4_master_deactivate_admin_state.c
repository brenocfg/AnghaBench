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
struct mlx4_vport_oper_state {scalar_t__ vlan_idx; } ;
struct TYPE_5__ {TYPE_1__* vf_oper; } ;
struct TYPE_6__ {TYPE_2__ master; } ;
struct mlx4_priv {int /*<<< orphan*/  dev; TYPE_3__ mfunc; } ;
struct TYPE_4__ {struct mlx4_vport_oper_state* vport; } ;

/* Variables and functions */
 int MLX4_MAX_PORTS ; 
 scalar_t__ NO_INDX ; 
 int /*<<< orphan*/  __mlx4_unregister_vlan (int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static void mlx4_master_deactivate_admin_state(struct mlx4_priv *priv, int slave)
{
	int port;
	struct mlx4_vport_oper_state *vp_oper;

	for (port = 1; port <= MLX4_MAX_PORTS; port++) {
		vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
		if (NO_INDX != vp_oper->vlan_idx) {
			__mlx4_unregister_vlan(&priv->dev,
					       port, vp_oper->vlan_idx);
			vp_oper->vlan_idx = NO_INDX;
		}
	}
	return;
}