#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  interface_id; } ;
union ib_gid {TYPE_2__ global; } ;
struct TYPE_14__ {TYPE_9__* demux; int /*<<< orphan*/ * sqps; int /*<<< orphan*/  going_down_lock; scalar_t__ is_going_down; } ;
struct TYPE_16__ {int /*<<< orphan*/  node_guid; } ;
struct mlx4_ib_dev {int num_ports; TYPE_3__ sriov; TYPE_4__* dev; TYPE_8__ ib_dev; } ;
struct TYPE_17__ {int /*<<< orphan*/ * guid_cache; } ;
struct TYPE_12__ {int sqp_demux; } ;
struct TYPE_15__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int __mlx4_ib_query_gid (TYPE_8__*,int,int /*<<< orphan*/ ,union ib_gid*,int) ; 
 int alloc_pv_object (struct mlx4_ib_dev*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pv_object (struct mlx4_ib_dev*,int,int) ; 
 int mlx4_ib_alloc_demux_ctx (struct mlx4_ib_dev*,TYPE_9__*,int) ; 
 int /*<<< orphan*/  mlx4_ib_cm_paravirt_clean (struct mlx4_ib_dev*,int) ; 
 int /*<<< orphan*/  mlx4_ib_cm_paravirt_init (struct mlx4_ib_dev*) ; 
 int /*<<< orphan*/  mlx4_ib_destroy_alias_guid_service (struct mlx4_ib_dev*) ; 
 int mlx4_ib_device_register_sysfs (struct mlx4_ib_dev*) ; 
 int /*<<< orphan*/  mlx4_ib_device_unregister_sysfs (struct mlx4_ib_dev*) ; 
 int /*<<< orphan*/  mlx4_ib_free_demux_ctx (TYPE_9__*) ; 
 int /*<<< orphan*/  mlx4_ib_gen_node_guid () ; 
 int mlx4_ib_init_alias_guid_service (struct mlx4_ib_dev*) ; 
 int /*<<< orphan*/  mlx4_ib_master_tunnels (struct mlx4_ib_dev*,int) ; 
 int /*<<< orphan*/  mlx4_ib_warn (TYPE_8__*,char*,...) ; 
 int /*<<< orphan*/  mlx4_is_mfunc (TYPE_4__*) ; 
 scalar_t__ mlx4_is_slave (TYPE_4__*) ; 
 int mlx4_master_func_num (TYPE_4__*) ; 
 int /*<<< orphan*/  mlx4_put_slave_node_guid (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mlx4_ib_init_sriov(struct mlx4_ib_dev *dev)
{
	int i = 0;
	int err;

	if (!mlx4_is_mfunc(dev->dev))
		return 0;

	dev->sriov.is_going_down = 0;
	spin_lock_init(&dev->sriov.going_down_lock);
	mlx4_ib_cm_paravirt_init(dev);

	mlx4_ib_warn(&dev->ib_dev, "multi-function enabled\n");

	if (mlx4_is_slave(dev->dev)) {
		mlx4_ib_warn(&dev->ib_dev, "operating in qp1 tunnel mode\n");
		return 0;
	}

	for (i = 0; i < dev->dev->caps.sqp_demux; i++) {
		if (i == mlx4_master_func_num(dev->dev))
			mlx4_put_slave_node_guid(dev->dev, i, dev->ib_dev.node_guid);
		else
			mlx4_put_slave_node_guid(dev->dev, i, mlx4_ib_gen_node_guid());
	}

	err = mlx4_ib_init_alias_guid_service(dev);
	if (err) {
		mlx4_ib_warn(&dev->ib_dev, "Failed init alias guid process.\n");
		goto paravirt_err;
	}
	err = mlx4_ib_device_register_sysfs(dev);
	if (err) {
		mlx4_ib_warn(&dev->ib_dev, "Failed to register sysfs\n");
		goto sysfs_err;
	}

	mlx4_ib_warn(&dev->ib_dev, "initializing demux service for %d qp1 clients\n",
		     dev->dev->caps.sqp_demux);
	for (i = 0; i < dev->num_ports; i++) {
		union ib_gid gid;
		err = __mlx4_ib_query_gid(&dev->ib_dev, i + 1, 0, &gid, 1);
		if (err)
			goto demux_err;
		dev->sriov.demux[i].guid_cache[0] = gid.global.interface_id;
		err = alloc_pv_object(dev, mlx4_master_func_num(dev->dev), i + 1,
				      &dev->sriov.sqps[i]);
		if (err)
			goto demux_err;
		err = mlx4_ib_alloc_demux_ctx(dev, &dev->sriov.demux[i], i + 1);
		if (err)
			goto free_pv;
	}
	mlx4_ib_master_tunnels(dev, 1);
	return 0;

free_pv:
	free_pv_object(dev, mlx4_master_func_num(dev->dev), i + 1);
demux_err:
	while (--i >= 0) {
		free_pv_object(dev, mlx4_master_func_num(dev->dev), i + 1);
		mlx4_ib_free_demux_ctx(&dev->sriov.demux[i]);
	}
	mlx4_ib_device_unregister_sysfs(dev);

sysfs_err:
	mlx4_ib_destroy_alias_guid_service(dev);

paravirt_err:
	mlx4_ib_cm_paravirt_clean(dev, -1);

	return err;
}