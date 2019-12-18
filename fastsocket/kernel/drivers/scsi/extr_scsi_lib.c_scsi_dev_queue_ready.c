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
struct scsi_device {scalar_t__ device_busy; scalar_t__ device_blocked; } ;
struct request_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_LOG_MLQUEUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_plug_device (struct request_queue*) ; 
 scalar_t__ scsi_device_is_busy (struct scsi_device*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*) ; 

__attribute__((used)) static inline int scsi_dev_queue_ready(struct request_queue *q,
				  struct scsi_device *sdev)
{
	if (sdev->device_busy == 0 && sdev->device_blocked) {
		/*
		 * unblock after device_blocked iterates to zero
		 */
		if (--sdev->device_blocked == 0) {
			SCSI_LOG_MLQUEUE(3,
				   sdev_printk(KERN_INFO, sdev,
				   "unblocking device at zero depth\n"));
		} else {
			blk_plug_device(q);
			return 0;
		}
	}
	if (scsi_device_is_busy(sdev))
		return 0;

	return 1;
}