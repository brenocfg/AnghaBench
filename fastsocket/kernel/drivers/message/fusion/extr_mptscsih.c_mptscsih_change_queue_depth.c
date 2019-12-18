#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct scsi_target {TYPE_2__* hostdata; } ;
struct scsi_device {scalar_t__ type; int queue_depth; int /*<<< orphan*/  tagged_supported; int /*<<< orphan*/  host; } ;
struct TYPE_7__ {int tflags; scalar_t__ minSyncFactor; } ;
typedef  TYPE_2__ VirtTarget ;
struct TYPE_9__ {scalar_t__ bus_type; TYPE_1__* sh; } ;
struct TYPE_8__ {TYPE_4__* ioc; } ;
struct TYPE_6__ {int can_queue; } ;
typedef  TYPE_3__ MPT_SCSI_HOST ;
typedef  TYPE_4__ MPT_ADAPTER ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MPT_SCSI_CMD_PER_DEV_HIGH ; 
 int MPT_SCSI_CMD_PER_DEV_LOW ; 
 int MPT_TARGET_FLAGS_Q_YES ; 
 scalar_t__ MPT_ULTRA160 ; 
 int MSG_SIMPLE_TAG ; 
 int SCSI_QDEPTH_DEFAULT ; 
 scalar_t__ SPI ; 
 scalar_t__ TYPE_DISK ; 
 int /*<<< orphan*/  scsi_adjust_queue_depth (struct scsi_device*,int,int) ; 
 struct scsi_target* scsi_target (struct scsi_device*) ; 
 TYPE_3__* shost_priv (int /*<<< orphan*/ ) ; 

int
mptscsih_change_queue_depth(struct scsi_device *sdev, int qdepth, int reason)
{
	MPT_SCSI_HOST		*hd = shost_priv(sdev->host);
	VirtTarget 		*vtarget;
	struct scsi_target 	*starget;
	int			max_depth;
	int			tagged;
	MPT_ADAPTER		*ioc = hd->ioc;

	starget = scsi_target(sdev);
	vtarget = starget->hostdata;

	if (reason != SCSI_QDEPTH_DEFAULT)
		return -EOPNOTSUPP;

	if (ioc->bus_type == SPI) {
		if (!(vtarget->tflags & MPT_TARGET_FLAGS_Q_YES))
			max_depth = 1;
		else if (sdev->type == TYPE_DISK &&
			 vtarget->minSyncFactor <= MPT_ULTRA160)
			max_depth = MPT_SCSI_CMD_PER_DEV_HIGH;
		else
			max_depth = MPT_SCSI_CMD_PER_DEV_LOW;
	} else
		 max_depth = ioc->sh->can_queue;

	if (!sdev->tagged_supported)
		max_depth = 1;

	if (qdepth > max_depth)
		qdepth = max_depth;
	if (qdepth == 1)
		tagged = 0;
	else
		tagged = MSG_SIMPLE_TAG;

	scsi_adjust_queue_depth(sdev, tagged, qdepth);
	return sdev->queue_depth;
}