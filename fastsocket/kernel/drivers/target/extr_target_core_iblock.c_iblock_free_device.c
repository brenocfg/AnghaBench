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
struct se_device {int dummy; } ;
struct iblock_dev {int /*<<< orphan*/ * ibd_bio_set; int /*<<< orphan*/ * ibd_bd; } ;

/* Variables and functions */
 int FMODE_EXCL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 struct iblock_dev* IBLOCK_DEV (struct se_device*) ; 
 int /*<<< orphan*/  bioset_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_bdev_exclusive (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct iblock_dev*) ; 

__attribute__((used)) static void iblock_free_device(struct se_device *dev)
{
	struct iblock_dev *ib_dev = IBLOCK_DEV(dev);

	if (ib_dev->ibd_bd != NULL)
		close_bdev_exclusive(ib_dev->ibd_bd, FMODE_WRITE|FMODE_READ|FMODE_EXCL);
	if (ib_dev->ibd_bio_set != NULL)
		bioset_free(ib_dev->ibd_bio_set);
	kfree(ib_dev);
}