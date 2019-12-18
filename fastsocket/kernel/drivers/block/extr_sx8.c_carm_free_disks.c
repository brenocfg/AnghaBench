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
struct request_queue {int dummy; } ;
struct gendisk {int flags; struct request_queue* queue; } ;
struct carm_host {TYPE_1__* port; } ;
struct TYPE_2__ {struct gendisk* disk; } ;

/* Variables and functions */
 unsigned int CARM_MAX_PORTS ; 
 int GENHD_FL_UP ; 
 int /*<<< orphan*/  blk_cleanup_queue (struct request_queue*) ; 
 int /*<<< orphan*/  del_gendisk (struct gendisk*) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 

__attribute__((used)) static void carm_free_disks(struct carm_host *host)
{
	unsigned int i;

	for (i = 0; i < CARM_MAX_PORTS; i++) {
		struct gendisk *disk = host->port[i].disk;
		if (disk) {
			struct request_queue *q = disk->queue;

			if (disk->flags & GENHD_FL_UP)
				del_gendisk(disk);
			if (q)
				blk_cleanup_queue(q);
			put_disk(disk);
		}
	}
}