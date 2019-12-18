#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct res_common {int owner; int /*<<< orphan*/  list; int /*<<< orphan*/  node; } ;
struct mlx4_resource_tracker {int /*<<< orphan*/ * res_tree; } ;
struct TYPE_3__ {struct mlx4_resource_tracker res_tracker; } ;
struct TYPE_4__ {TYPE_1__ master; } ;
struct mlx4_priv {TYPE_2__ mfunc; } ;
struct mlx4_dev {int dummy; } ;
typedef  enum mlx4_resource { ____Placeholder_mlx4_resource } mlx4_resource ;

/* Variables and functions */
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  kfree (struct res_common*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_tlock (struct mlx4_dev*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int remove_ok (struct res_common*,int,int) ; 
 struct res_common* res_tracker_lookup (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rem_res_range(struct mlx4_dev *dev, int slave, u64 base, int count,
			 enum mlx4_resource type, int extra)
{
	u64 i;
	int err;
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	struct res_common *r;

	spin_lock_irq(mlx4_tlock(dev));
	for (i = base; i < base + count; ++i) {
		r = res_tracker_lookup(&tracker->res_tree[type], i);
		if (!r) {
			err = -ENOENT;
			goto out;
		}
		if (r->owner != slave) {
			err = -EPERM;
			goto out;
		}
		err = remove_ok(r, type, extra);
		if (err)
			goto out;
	}

	for (i = base; i < base + count; ++i) {
		r = res_tracker_lookup(&tracker->res_tree[type], i);
		rb_erase(&r->node, &tracker->res_tree[type]);
		list_del(&r->list);
		kfree(r);
	}
	err = 0;

out:
	spin_unlock_irq(mlx4_tlock(dev));

	return err;
}