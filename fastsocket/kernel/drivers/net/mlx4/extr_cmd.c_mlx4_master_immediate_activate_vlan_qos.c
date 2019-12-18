#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mlx4_vport_state {scalar_t__ default_vlan; scalar_t__ default_qos; } ;
struct TYPE_8__ {scalar_t__ default_vlan; scalar_t__ default_qos; } ;
struct mlx4_vport_oper_state {int vlan_idx; TYPE_3__ state; } ;
struct mlx4_vf_immed_vlan_work {int flags; scalar_t__ orig_vlan_id; int orig_vlan_ix; int port; int slave; scalar_t__ qos; scalar_t__ vlan_id; int vlan_ix; int /*<<< orphan*/  work; struct mlx4_priv* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  comm_wq; TYPE_2__* vf_admin; TYPE_1__* vf_oper; } ;
struct TYPE_10__ {TYPE_4__ master; } ;
struct mlx4_priv {TYPE_5__ mfunc; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {struct mlx4_vport_state* vport; } ;
struct TYPE_6__ {struct mlx4_vport_oper_state* vport; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX4_VF_IMMED_VLAN_FLAG_QOS ; 
 int MLX4_VF_IMMED_VLAN_FLAG_VLAN ; 
 int NO_INDX ; 
 int __mlx4_register_vlan (int /*<<< orphan*/ *,int,scalar_t__,int*) ; 
 int /*<<< orphan*/  kfree (struct mlx4_vf_immed_vlan_work*) ; 
 struct mlx4_vf_immed_vlan_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_dbg (int /*<<< orphan*/ *,char*,int,int,int,int) ; 
 int /*<<< orphan*/  mlx4_vf_immed_vlan_work_handler ; 
 int /*<<< orphan*/  mlx4_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mlx4_master_immediate_activate_vlan_qos(struct mlx4_priv *priv,
					    int slave, int port)
{
	struct mlx4_vport_oper_state *vp_oper;
	struct mlx4_vport_state *vp_admin;
	struct mlx4_vf_immed_vlan_work *work;
	int err;
	int admin_vlan_ix = NO_INDX;

	vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
	vp_admin = &priv->mfunc.master.vf_admin[slave].vport[port];

	if (vp_oper->state.default_vlan == vp_admin->default_vlan &&
	    vp_oper->state.default_qos == vp_admin->default_qos)
		return 0;

	work = kzalloc(sizeof(*work), GFP_KERNEL);
	if (!work)
		return -ENOMEM;

	if (vp_oper->state.default_vlan != vp_admin->default_vlan) {
		err = __mlx4_register_vlan(&priv->dev, port,
					   vp_admin->default_vlan,
					   &admin_vlan_ix);
		if (err) {
			kfree(work);
			mlx4_warn((&priv->dev),
				  "No vlan resources slave %d, port %d\n",
				  slave, port);
			return err;
		}
		work->flags |= MLX4_VF_IMMED_VLAN_FLAG_VLAN;
		mlx4_dbg((&(priv->dev)),
			 "alloc vlan %d idx  %d slave %d port %d\n",
			 (int)(vp_admin->default_vlan),
			 admin_vlan_ix, slave, port);
	}

	/* save original vlan ix and vlan id */
	work->orig_vlan_id = vp_oper->state.default_vlan;
	work->orig_vlan_ix = vp_oper->vlan_idx;

	/* handle new qos */
	if (vp_oper->state.default_qos != vp_admin->default_qos)
		work->flags |= MLX4_VF_IMMED_VLAN_FLAG_QOS;

	if (work->flags & MLX4_VF_IMMED_VLAN_FLAG_VLAN)
		vp_oper->vlan_idx = admin_vlan_ix;

	vp_oper->state.default_vlan = vp_admin->default_vlan;
	vp_oper->state.default_qos = vp_admin->default_qos;

	/* iterate over QPs owned by this slave, using UPDATE_QP */
	work->port = port;
	work->slave = slave;
	work->qos = vp_oper->state.default_qos;
	work->vlan_id = vp_oper->state.default_vlan;
	work->vlan_ix = vp_oper->vlan_idx;
	work->priv = priv;
	INIT_WORK(&work->work, mlx4_vf_immed_vlan_work_handler);
	queue_work(priv->mfunc.master.comm_wq, &work->work);

	return 0;
}