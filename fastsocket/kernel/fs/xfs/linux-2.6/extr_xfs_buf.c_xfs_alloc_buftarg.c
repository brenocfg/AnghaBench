#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  seeks; int /*<<< orphan*/  shrink; } ;
struct TYPE_8__ {TYPE_5__ bt_shrinker; int /*<<< orphan*/  bt_lru_lock; int /*<<< orphan*/  bt_lru; int /*<<< orphan*/  bt_bdi; struct block_device* bt_bdev; int /*<<< orphan*/  bt_dev; struct xfs_mount* bt_mount; } ;
typedef  TYPE_1__ xfs_buftarg_t ;
struct xfs_mount {int dummy; } ;
struct block_device {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SEEKS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  blk_get_backing_dev_info (struct block_device*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_shrinker (TYPE_5__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ xfs_alloc_delwrite_queue (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  xfs_buftarg_shrink ; 
 scalar_t__ xfs_setsize_buftarg_early (TYPE_1__*,struct block_device*) ; 

xfs_buftarg_t *
xfs_alloc_buftarg(
	struct xfs_mount	*mp,
	struct block_device	*bdev,
	int			external,
	const char		*fsname)
{
	xfs_buftarg_t		*btp;

	btp = kmem_zalloc(sizeof(*btp), KM_SLEEP);

	btp->bt_mount = mp;
	btp->bt_dev =  bdev->bd_dev;
	btp->bt_bdev = bdev;
	btp->bt_bdi = blk_get_backing_dev_info(bdev);
	if (!btp->bt_bdi)
		goto error;

	INIT_LIST_HEAD(&btp->bt_lru);
	spin_lock_init(&btp->bt_lru_lock);
	if (xfs_setsize_buftarg_early(btp, bdev))
		goto error;
	if (xfs_alloc_delwrite_queue(btp, fsname))
		goto error;
	btp->bt_shrinker.shrink = xfs_buftarg_shrink;
	btp->bt_shrinker.seeks = DEFAULT_SEEKS;
	register_shrinker(&btp->bt_shrinker);
	return btp;

error:
	kmem_free(btp);
	return NULL;
}