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
struct scsi_device {int queue_depth; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SCSI_QDEPTH_DEFAULT 130 
#define  SCSI_QDEPTH_QFULL 129 
#define  SCSI_QDEPTH_RAMP_UP 128 
 int /*<<< orphan*/  scsi_adjust_queue_depth (struct scsi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_get_tag_type (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_track_queue_full (struct scsi_device*,int) ; 

__attribute__((used)) static int zfcp_scsi_change_queue_depth(struct scsi_device *sdev, int depth,
					int reason)
{
	switch (reason) {
	case SCSI_QDEPTH_DEFAULT:
		scsi_adjust_queue_depth(sdev, scsi_get_tag_type(sdev), depth);
		break;
	case SCSI_QDEPTH_QFULL:
		scsi_track_queue_full(sdev, depth);
		break;
	case SCSI_QDEPTH_RAMP_UP:
		scsi_adjust_queue_depth(sdev, scsi_get_tag_type(sdev), depth);
		break;
	default:
		return -EOPNOTSUPP;
	}
	return sdev->queue_depth;
}