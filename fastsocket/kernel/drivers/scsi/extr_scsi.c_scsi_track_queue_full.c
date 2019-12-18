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
struct scsi_device {int last_queue_full_time; int last_queue_full_depth; int last_queue_full_count; scalar_t__ ordered_tags; TYPE_1__* host; } ;
struct TYPE_2__ {int cmd_per_lun; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ORDERED_TAG ; 
 int /*<<< orphan*/  MSG_SIMPLE_TAG ; 
 int jiffies ; 
 int /*<<< orphan*/  scsi_adjust_queue_depth (struct scsi_device*,int /*<<< orphan*/ ,int) ; 

int scsi_track_queue_full(struct scsi_device *sdev, int depth)
{

	/*
	 * Don't let QUEUE_FULLs on the same
	 * jiffies count, they could all be from
	 * same event.
	 */
	if ((jiffies >> 4) == (sdev->last_queue_full_time >> 4))
		return 0;

	sdev->last_queue_full_time = jiffies;
	if (sdev->last_queue_full_depth != depth) {
		sdev->last_queue_full_count = 1;
		sdev->last_queue_full_depth = depth;
	} else {
		sdev->last_queue_full_count++;
	}

	if (sdev->last_queue_full_count <= 10)
		return 0;
	if (sdev->last_queue_full_depth < 8) {
		/* Drop back to untagged */
		scsi_adjust_queue_depth(sdev, 0, sdev->host->cmd_per_lun);
		return -1;
	}
	
	if (sdev->ordered_tags)
		scsi_adjust_queue_depth(sdev, MSG_ORDERED_TAG, depth);
	else
		scsi_adjust_queue_depth(sdev, MSG_SIMPLE_TAG, depth);
	return depth;
}