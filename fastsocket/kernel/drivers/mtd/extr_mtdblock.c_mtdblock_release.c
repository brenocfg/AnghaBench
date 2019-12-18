#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtdblk_dev {int /*<<< orphan*/  cache_data; TYPE_1__* mtd; int /*<<< orphan*/  count; int /*<<< orphan*/  cache_mutex; } ;
struct mtd_blktrans_dev {int devnum; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sync ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL1 ; 
 int /*<<< orphan*/  kfree (struct mtdblk_dev*) ; 
 struct mtdblk_dev** mtdblks ; 
 int /*<<< orphan*/  mtdblks_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cached_data (struct mtdblk_dev*) ; 

__attribute__((used)) static int mtdblock_release(struct mtd_blktrans_dev *mbd)
{
	int dev = mbd->devnum;
	struct mtdblk_dev *mtdblk = mtdblks[dev];

   	DEBUG(MTD_DEBUG_LEVEL1, "mtdblock_release\n");

	mutex_lock(&mtdblks_lock);

	mutex_lock(&mtdblk->cache_mutex);
	write_cached_data(mtdblk);
	mutex_unlock(&mtdblk->cache_mutex);

	if (!--mtdblk->count) {
		/* It was the last usage. Free the device */
		mtdblks[dev] = NULL;
		if (mtdblk->mtd->sync)
			mtdblk->mtd->sync(mtdblk->mtd);
		vfree(mtdblk->cache_data);
		kfree(mtdblk);
	}

	mutex_unlock(&mtdblks_lock);

	DEBUG(MTD_DEBUG_LEVEL1, "ok\n");

	return 0;
}