#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  max_order; } ;
struct mlx4_mr_table {int /*<<< orphan*/  mpt_bitmap; TYPE_2__ mtt_buddy; } ;
struct mlx4_priv {scalar_t__ reserved_mtts; struct mlx4_mr_table mr_table; } ;
struct TYPE_4__ {scalar_t__ reserved_mtts; scalar_t__ num_mtts; int /*<<< orphan*/  reserved_mrws; int /*<<< orphan*/  num_mpts; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  fls (scalar_t__) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  is_power_of_2 (int /*<<< orphan*/ ) ; 
 int log_mtts_per_seg ; 
 scalar_t__ mlx4_alloc_mtt_range (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_bitmap_cleanup (int /*<<< orphan*/ *) ; 
 int mlx4_bitmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_buddy_cleanup (TYPE_2__*) ; 
 int mlx4_buddy_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int /*<<< orphan*/ ) ; 

int mlx4_init_mr_table(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_mr_table *mr_table = &priv->mr_table;
	int err;

	if (!is_power_of_2(dev->caps.num_mpts))
		return -EINVAL;

	/* Nothing to do for slaves - all MR handling is forwarded
	* to the master */
	if (mlx4_is_slave(dev))
		return 0;

	err = mlx4_bitmap_init(&mr_table->mpt_bitmap, dev->caps.num_mpts,
			       ~0, dev->caps.reserved_mrws, 0);
	if (err)
		return err;

	err = mlx4_buddy_init(&mr_table->mtt_buddy,
			      ilog2((u32)dev->caps.num_mtts /
			      (1 << log_mtts_per_seg)));
	if (err)
		goto err_buddy;

	if (dev->caps.reserved_mtts) {
		priv->reserved_mtts =
			mlx4_alloc_mtt_range(dev,
					     fls(dev->caps.reserved_mtts - 1));
		if (priv->reserved_mtts < 0) {
			mlx4_warn(dev, "MTT table of order %u is too small.\n",
				  mr_table->mtt_buddy.max_order);
			err = -ENOMEM;
			goto err_reserve_mtts;
		}
	}

	return 0;

err_reserve_mtts:
	mlx4_buddy_cleanup(&mr_table->mtt_buddy);

err_buddy:
	mlx4_bitmap_cleanup(&mr_table->mpt_bitmap);

	return err;
}