#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* viocd_disk; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_run_queue (int /*<<< orphan*/ ) ; 
 TYPE_2__* viocd_diskinfo ; 
 int viocd_numdev ; 

__attribute__((used)) static void restart_all_queues(int first_index)
{
	int i;

	for (i = first_index + 1; i < viocd_numdev; i++)
		if (viocd_diskinfo[i].viocd_disk)
			blk_run_queue(viocd_diskinfo[i].viocd_disk->queue);
	for (i = 0; i <= first_index; i++)
		if (viocd_diskinfo[i].viocd_disk)
			blk_run_queue(viocd_diskinfo[i].viocd_disk->queue);
}