#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mtdblk_dev {int count; int /*<<< orphan*/ * cache_data; struct mtd_info* mtd; scalar_t__ cache_size; int /*<<< orphan*/  cache_state; int /*<<< orphan*/  cache_mutex; } ;
struct mtd_info {int flags; scalar_t__ erasesize; } ;
struct mtd_blktrans_dev {int devnum; struct mtd_info* mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL1 ; 
 int MTD_NO_ERASE ; 
 int /*<<< orphan*/  STATE_EMPTY ; 
 struct mtdblk_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct mtdblk_dev** mtdblks ; 
 int /*<<< orphan*/  mtdblks_lock ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtdblock_open(struct mtd_blktrans_dev *mbd)
{
	struct mtdblk_dev *mtdblk;
	struct mtd_info *mtd = mbd->mtd;
	int dev = mbd->devnum;

	DEBUG(MTD_DEBUG_LEVEL1,"mtdblock_open\n");

	mutex_lock(&mtdblks_lock);
	if (mtdblks[dev]) {
		mtdblks[dev]->count++;
		mutex_unlock(&mtdblks_lock);
		return 0;
	}

	/* OK, it's not open. Create cache info for it */
	mtdblk = kzalloc(sizeof(struct mtdblk_dev), GFP_KERNEL);
	if (!mtdblk) {
		mutex_unlock(&mtdblks_lock);
		return -ENOMEM;
	}

	mtdblk->count = 1;
	mtdblk->mtd = mtd;

	mutex_init(&mtdblk->cache_mutex);
	mtdblk->cache_state = STATE_EMPTY;
	if ( !(mtdblk->mtd->flags & MTD_NO_ERASE) && mtdblk->mtd->erasesize) {
		mtdblk->cache_size = mtdblk->mtd->erasesize;
		mtdblk->cache_data = NULL;
	}

	mtdblks[dev] = mtdblk;
	mutex_unlock(&mtdblks_lock);

	DEBUG(MTD_DEBUG_LEVEL1, "ok\n");

	return 0;
}