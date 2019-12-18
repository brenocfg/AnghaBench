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
struct block_device {int /*<<< orphan*/  bd_fsfreeze_mutex; int /*<<< orphan*/  bd_holder_list; int /*<<< orphan*/  bd_list; int /*<<< orphan*/  bd_inodes; int /*<<< orphan*/  bd_mutex; } ;
struct bdev_inode {int /*<<< orphan*/  vfs_inode; struct block_device bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct block_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_once(void *foo)
{
	struct bdev_inode *ei = (struct bdev_inode *) foo;
	struct block_device *bdev = &ei->bdev;

	memset(bdev, 0, sizeof(*bdev));
	mutex_init(&bdev->bd_mutex);
	INIT_LIST_HEAD(&bdev->bd_inodes);
	INIT_LIST_HEAD(&bdev->bd_list);
#ifdef CONFIG_SYSFS
	INIT_LIST_HEAD(&bdev->bd_holder_list);
#endif
	inode_init_once(&ei->vfs_inode);
	/* Initialize mutex for freeze. */
	mutex_init(&bdev->bd_fsfreeze_mutex);
}