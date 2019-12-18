#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  key; } ;
struct ib_mw {int /*<<< orphan*/  rkey; } ;
struct mlx4_ib_mw {TYPE_2__ mmw; struct ib_mw ibmw; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
typedef  enum ib_mw_type { ____Placeholder_ib_mw_type } ib_mw_type ;
struct TYPE_5__ {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_mw* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlx4_ib_mw*) ; 
 struct mlx4_ib_mw* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mlx4_mw_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int mlx4_mw_enable (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  mlx4_mw_free (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mlx4_type (int) ; 
 TYPE_1__* to_mpd (struct ib_pd*) ; 

struct ib_mw *mlx4_ib_alloc_mw(struct ib_pd *pd, enum ib_mw_type type)
{
	struct mlx4_ib_dev *dev = to_mdev(pd->device);
	struct mlx4_ib_mw *mw;
	int err;

	mw = kmalloc(sizeof(*mw), GFP_KERNEL);
	if (!mw)
		return ERR_PTR(-ENOMEM);

	err = mlx4_mw_alloc(dev->dev, to_mpd(pd)->pdn,
			    to_mlx4_type(type), &mw->mmw);
	if (err)
		goto err_free;

	err = mlx4_mw_enable(dev->dev, &mw->mmw);
	if (err)
		goto err_mw;

	mw->ibmw.rkey = mw->mmw.key;

	return &mw->ibmw;

err_mw:
	mlx4_mw_free(dev->dev, &mw->mmw);

err_free:
	kfree(mw);

	return ERR_PTR(err);
}