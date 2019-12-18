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
struct TYPE_6__ {int /*<<< orphan*/ * slave_list; } ;
struct TYPE_7__ {TYPE_2__ res_tracker; } ;
struct TYPE_8__ {TYPE_3__ master; } ;
struct mlx4_priv {TYPE_4__ mfunc; } ;
struct TYPE_5__ {int function; } ;
struct mlx4_dev {int num_slaves; TYPE_1__ caps; } ;
typedef  enum mlx4_res_tracker_free_type { ____Placeholder_mlx4_res_tracker_free_type } mlx4_res_tracker_free_type ;

/* Variables and functions */
 int RES_TR_FREE_ALL ; 
 int RES_TR_FREE_SLAVES_ONLY ; 
 int RES_TR_FREE_STRUCTS_ONLY ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_delete_all_resources_for_slave (struct mlx4_dev*,int) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

void mlx4_free_resource_tracker(struct mlx4_dev *dev,
				enum mlx4_res_tracker_free_type type)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int i;

	if (priv->mfunc.master.res_tracker.slave_list) {
		if (type != RES_TR_FREE_STRUCTS_ONLY)
			for (i = 0 ; i < dev->num_slaves; i++)
				if (type == RES_TR_FREE_ALL ||
				    dev->caps.function != i)
					mlx4_delete_all_resources_for_slave(dev, i);

		if (type != RES_TR_FREE_SLAVES_ONLY) {
			kfree(priv->mfunc.master.res_tracker.slave_list);
			priv->mfunc.master.res_tracker.slave_list = NULL;
		}
	}
}