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
struct scsi_device {TYPE_1__* host; } ;
struct TYPE_2__ {int can_queue; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int SCSI_QDEPTH_DEFAULT ; 
 int /*<<< orphan*/  scsi_adjust_queue_depth (struct scsi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_get_tag_type (struct scsi_device*) ; 

__attribute__((used)) static int megasas_change_queue_depth(struct scsi_device *sdev,
				      int queue_depth, int reason)
{
	if (reason != SCSI_QDEPTH_DEFAULT)
		return -EOPNOTSUPP;

	if (queue_depth > sdev->host->can_queue)
		queue_depth = sdev->host->can_queue;
	scsi_adjust_queue_depth(sdev, scsi_get_tag_type(sdev),
				queue_depth);

	return queue_depth;
}