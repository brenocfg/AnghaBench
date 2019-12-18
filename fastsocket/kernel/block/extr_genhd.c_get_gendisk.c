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
struct kobject {int dummy; } ;
struct hd_struct {int partno; } ;
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 scalar_t__ BLOCK_EXT_MAJOR ; 
 scalar_t__ MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdev_map ; 
 int /*<<< orphan*/  blk_mangle_minor (int /*<<< orphan*/ ) ; 
 struct gendisk* dev_to_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext_devt_idr ; 
 int /*<<< orphan*/  ext_devt_mutex ; 
 scalar_t__ get_disk (struct gendisk*) ; 
 struct hd_struct* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct kobject* kobj_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kobj_to_dev (struct kobject*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct gendisk* part_to_disk (struct hd_struct*) ; 

struct gendisk *get_gendisk(dev_t devt, int *partno)
{
	struct gendisk *disk = NULL;

	if (MAJOR(devt) != BLOCK_EXT_MAJOR) {
		struct kobject *kobj;

		kobj = kobj_lookup(bdev_map, devt, partno);
		if (kobj)
			disk = dev_to_disk(kobj_to_dev(kobj));
	} else {
		struct hd_struct *part;

		mutex_lock(&ext_devt_mutex);
		part = idr_find(&ext_devt_idr, blk_mangle_minor(MINOR(devt)));
		if (part && get_disk(part_to_disk(part))) {
			*partno = part->partno;
			disk = part_to_disk(part);
		}
		mutex_unlock(&ext_devt_mutex);
	}

	return disk;
}