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
struct scsi_device {scalar_t__ id; TYPE_1__* host; } ;
struct TYPE_2__ {scalar_t__ this_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __scsi_remove_device (struct scsi_device*) ; 

void scsi_free_host_dev(struct scsi_device *sdev)
{
	BUG_ON(sdev->id != sdev->host->this_id);

	__scsi_remove_device(sdev);
}