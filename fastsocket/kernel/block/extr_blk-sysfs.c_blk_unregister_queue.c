#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int /*<<< orphan*/  kobj; scalar_t__ request_fn; } ;
struct gendisk {struct request_queue* queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_REMOVE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  blk_trace_remove_sysfs (TYPE_1__*) ; 
 TYPE_1__* disk_to_dev (struct gendisk*) ; 
 int /*<<< orphan*/  elv_unregister_queue (struct request_queue*) ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void blk_unregister_queue(struct gendisk *disk)
{
	struct request_queue *q = disk->queue;

	if (WARN_ON(!q))
		return;

	if (q->request_fn)
		elv_unregister_queue(q);

	kobject_uevent(&q->kobj, KOBJ_REMOVE);
	kobject_del(&q->kobj);
	blk_trace_remove_sysfs(disk_to_dev(disk));
	kobject_put(&disk_to_dev(disk)->kobj);
}