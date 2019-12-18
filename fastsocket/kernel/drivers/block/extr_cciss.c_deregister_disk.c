#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct gendisk {int flags; struct request_queue* queue; } ;
struct TYPE_6__ {int usage_count; scalar_t__ heads; } ;
typedef  TYPE_1__ drive_info_struct ;
struct TYPE_7__ {size_t highest_lun; TYPE_1__** drv; int /*<<< orphan*/  num_luns; struct gendisk** gendisk; } ;
typedef  TYPE_2__ ctlr_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int CISS_MAX_LUN ; 
 int EBUSY ; 
 int EPERM ; 
 int GENHD_FL_UP ; 
 int /*<<< orphan*/  blk_cleanup_queue (struct request_queue*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cciss_clear_drive_info (TYPE_1__*) ; 
 int /*<<< orphan*/  cciss_destroy_ld_sysfs_entry (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_gendisk (struct gendisk*) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int deregister_disk(ctlr_info_t *h, int drv_index,
			   int clear_all, int via_ioctl)
{
	int i;
	struct gendisk *disk;
	drive_info_struct *drv;
	int recalculate_highest_lun;

	if (!capable(CAP_SYS_RAWIO))
		return -EPERM;

	drv = h->drv[drv_index];
	disk = h->gendisk[drv_index];

	/* make sure logical volume is NOT is use */
	if (clear_all || (h->gendisk[0] == disk)) {
		if (drv->usage_count > via_ioctl)
			return -EBUSY;
	} else if (drv->usage_count > 0)
		return -EBUSY;

	recalculate_highest_lun = (drv == h->drv[h->highest_lun]);

	/* invalidate the devices and deregister the disk.  If it is disk
	 * zero do not deregister it but just zero out it's values.  This
	 * allows us to delete disk zero but keep the controller registered.
	 */
	if (h->gendisk[0] != disk) {
		struct request_queue *q = disk->queue;
		if (disk->flags & GENHD_FL_UP) {
			cciss_destroy_ld_sysfs_entry(h, drv_index, 0);
			del_gendisk(disk);
		}
		if (q)
			blk_cleanup_queue(q);
		/* If clear_all is set then we are deleting the logical
		 * drive, not just refreshing its info.  For drives
		 * other than disk 0 we will call put_disk.  We do not
		 * do this for disk 0 as we need it to be able to
		 * configure the controller.
		 */
		if (clear_all){
			/* This isn't pretty, but we need to find the
			 * disk in our array and NULL our the pointer.
			 * This is so that we will call alloc_disk if
			 * this index is used again later.
			 */
			for (i=0; i < CISS_MAX_LUN; i++){
				if (h->gendisk[i] == disk) {
					h->gendisk[i] = NULL;
					break;
				}
			}
			put_disk(disk);
		}
	} else {
		set_capacity(disk, 0);
		cciss_clear_drive_info(drv);
	}

	--h->num_luns;

	/* if it was the last disk, find the new hightest lun */
	if (clear_all && recalculate_highest_lun) {
		int i, newhighest = -1;
		for (i = 0; i <= h->highest_lun; i++) {
			/* if the disk has size > 0, it is available */
			if (h->drv[i] && h->drv[i]->heads)
				newhighest = i;
		}
		h->highest_lun = newhighest;
	}
	return 0;
}