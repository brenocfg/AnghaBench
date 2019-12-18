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
struct request_queue {int /*<<< orphan*/  kobj; int /*<<< orphan*/  request_fn; } ;
struct gendisk {struct request_queue* queue; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  KOBJ_REMOVE ; 
 scalar_t__ WARN_ON (int) ; 
 int blk_trace_init_sysfs (struct device*) ; 
 int /*<<< orphan*/  blk_trace_remove_sysfs (struct device*) ; 
 struct device* disk_to_dev (struct gendisk*) ; 
 int elv_register_queue (struct request_queue*) ; 
 int kobject_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int blk_register_queue(struct gendisk *disk)
{
	int ret;
	struct device *dev = disk_to_dev(disk);

	struct request_queue *q = disk->queue;

	if (WARN_ON(!q))
		return -ENXIO;

	ret = blk_trace_init_sysfs(dev);
	if (ret)
		return ret;

	ret = kobject_add(&q->kobj, kobject_get(&dev->kobj), "%s", "queue");
	if (ret < 0)
		return ret;

	kobject_uevent(&q->kobj, KOBJ_ADD);

	if (!q->request_fn)
		return 0;

	ret = elv_register_queue(q);
	if (ret) {
		kobject_uevent(&q->kobj, KOBJ_REMOVE);
		kobject_del(&q->kobj);
		blk_trace_remove_sysfs(disk_to_dev(disk));
		return ret;
	}

	return 0;
}