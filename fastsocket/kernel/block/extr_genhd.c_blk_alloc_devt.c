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
struct hd_struct {scalar_t__ partno; } ;
struct gendisk {scalar_t__ minors; scalar_t__ first_minor; int /*<<< orphan*/  major; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_EXT_MAJOR ; 
 int EAGAIN ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_EXT_DEVT ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ blk_mangle_minor (int) ; 
 int /*<<< orphan*/  ext_devt_idr ; 
 int /*<<< orphan*/  ext_devt_mutex ; 
 int idr_get_new (int /*<<< orphan*/ *,struct hd_struct*,int*) ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct gendisk* part_to_disk (struct hd_struct*) ; 

int blk_alloc_devt(struct hd_struct *part, dev_t *devt)
{
	struct gendisk *disk = part_to_disk(part);
	int idx, rc;

	/* in consecutive minor range? */
	if (part->partno < disk->minors) {
		*devt = MKDEV(disk->major, disk->first_minor + part->partno);
		return 0;
	}

	/* allocate ext devt */
	do {
		if (!idr_pre_get(&ext_devt_idr, GFP_KERNEL))
			return -ENOMEM;
		mutex_lock(&ext_devt_mutex);
		rc = idr_get_new(&ext_devt_idr, part, &idx);
		mutex_unlock(&ext_devt_mutex);
	} while (rc == -EAGAIN);

	if (rc)
		return rc;

	if (idx > MAX_EXT_DEVT) {
		mutex_lock(&ext_devt_mutex);
		idr_remove(&ext_devt_idr, idx);
		mutex_unlock(&ext_devt_mutex);
		return -EBUSY;
	}

	*devt = MKDEV(BLOCK_EXT_MAJOR, blk_mangle_minor(idx));
	return 0;
}