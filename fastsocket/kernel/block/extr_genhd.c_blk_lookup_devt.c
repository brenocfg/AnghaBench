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
struct hd_struct {int dummy; } ;
struct gendisk {int minors; } ;
struct device {int /*<<< orphan*/  devt; } ;
struct class_dev_iter {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  block_class ; 
 int /*<<< orphan*/  class_dev_iter_exit (struct class_dev_iter*) ; 
 int /*<<< orphan*/  class_dev_iter_init (struct class_dev_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct device* class_dev_iter_next (struct class_dev_iter*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct gendisk* dev_to_disk (struct device*) ; 
 struct hd_struct* disk_get_part (struct gendisk*,int) ; 
 int /*<<< orphan*/  disk_put_part (struct hd_struct*) ; 
 int /*<<< orphan*/  disk_type ; 
 int /*<<< orphan*/  part_devt (struct hd_struct*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

dev_t blk_lookup_devt(const char *name, int partno)
{
	dev_t devt = MKDEV(0, 0);
	struct class_dev_iter iter;
	struct device *dev;

	class_dev_iter_init(&iter, &block_class, NULL, &disk_type);
	while ((dev = class_dev_iter_next(&iter))) {
		struct gendisk *disk = dev_to_disk(dev);
		struct hd_struct *part;

		if (strcmp(dev_name(dev), name))
			continue;

		if (partno < disk->minors) {
			/* We need to return the right devno, even
			 * if the partition doesn't exist yet.
			 */
			devt = MKDEV(MAJOR(dev->devt),
				     MINOR(dev->devt) + partno);
			break;
		}
		part = disk_get_part(disk, partno);
		if (part) {
			devt = part_devt(part);
			disk_put_part(part);
			break;
		}
		disk_put_part(part);
	}
	class_dev_iter_exit(&iter);
	return devt;
}