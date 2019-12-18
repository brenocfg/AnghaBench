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
struct scsi_device {int inquiry_len; int queue_depth; int* inquiry; int /*<<< orphan*/  scsi_level; int /*<<< orphan*/  ordered_tags; int /*<<< orphan*/  simple_tags; int /*<<< orphan*/  tagged_supported; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SCSI_QDEPTH_DEFAULT ; 
 int SCSI_QDEPTH_QFULL ; 
 int SCSI_QDEPTH_RAMP_UP ; 
 int /*<<< orphan*/  _scsih_adjust_queue_depth (struct scsi_device*,int) ; 
 int /*<<< orphan*/  scsi_track_queue_full (struct scsi_device*,int) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
_scsih_change_queue_depth(struct scsi_device *sdev, int qdepth, int reason)
{
	if (reason == SCSI_QDEPTH_DEFAULT || reason == SCSI_QDEPTH_RAMP_UP)
		_scsih_adjust_queue_depth(sdev, qdepth);
	else if (reason == SCSI_QDEPTH_QFULL)
		scsi_track_queue_full(sdev, qdepth);
	else
		return -EOPNOTSUPP;

	if (sdev->inquiry_len > 7)
		sdev_printk(KERN_INFO, sdev, "qdepth(%d), tagged(%d), " \
		"simple(%d), ordered(%d), scsi_level(%d), cmd_que(%d)\n",
		sdev->queue_depth, sdev->tagged_supported, sdev->simple_tags,
		sdev->ordered_tags, sdev->scsi_level,
		(sdev->inquiry[7] & 2) >> 1);

	return sdev->queue_depth;
}