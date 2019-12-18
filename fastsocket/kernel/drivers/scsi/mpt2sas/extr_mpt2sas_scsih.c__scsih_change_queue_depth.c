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
struct scsi_device {int inquiry_len; int queue_depth; int* inquiry; int /*<<< orphan*/  scsi_level; int /*<<< orphan*/  ordered_tags; int /*<<< orphan*/  simple_tags; int /*<<< orphan*/  tagged_supported; struct MPT2SAS_DEVICE* hostdata; struct Scsi_Host* host; } ;
struct _sas_device {int device_info; } ;
struct Scsi_Host {int can_queue; } ;
struct MPT2SAS_TARGET {int flags; int /*<<< orphan*/  sas_address; } ;
struct MPT2SAS_DEVICE {struct MPT2SAS_TARGET* sas_target; } ;
struct MPT2SAS_ADAPTER {int /*<<< orphan*/  sas_device_lock; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int MPI2_SAS_DEVICE_INFO_SATA_DEVICE ; 
 int MPT2SAS_SATA_QUEUE_DEPTH ; 
 int MPT_TARGET_FLAGS_VOLUME ; 
 int MSG_SIMPLE_TAG ; 
 int SCSI_QDEPTH_DEFAULT ; 
 struct _sas_device* mpt2sas_scsih_sas_device_find_by_sas_address (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_adjust_queue_depth (struct scsi_device*,int,int) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct MPT2SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
_scsih_change_queue_depth(struct scsi_device *sdev, int qdepth, int reason)
{
	struct Scsi_Host *shost = sdev->host;
	int max_depth;
	int tag_type;
	struct MPT2SAS_ADAPTER *ioc = shost_priv(shost);
	struct MPT2SAS_DEVICE *sas_device_priv_data;
	struct MPT2SAS_TARGET *sas_target_priv_data;
	struct _sas_device *sas_device;
	unsigned long flags;

	if (reason != SCSI_QDEPTH_DEFAULT)
		return -EOPNOTSUPP;

	max_depth = shost->can_queue;

	/* limit max device queue for SATA to 32 */
	sas_device_priv_data = sdev->hostdata;
	if (!sas_device_priv_data)
		goto not_sata;
	sas_target_priv_data = sas_device_priv_data->sas_target;
	if (!sas_target_priv_data)
		goto not_sata;
	if ((sas_target_priv_data->flags & MPT_TARGET_FLAGS_VOLUME))
		goto not_sata;
	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = mpt2sas_scsih_sas_device_find_by_sas_address(ioc,
	   sas_device_priv_data->sas_target->sas_address);
	if (sas_device && sas_device->device_info &
	    MPI2_SAS_DEVICE_INFO_SATA_DEVICE)
		max_depth = MPT2SAS_SATA_QUEUE_DEPTH;
	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

 not_sata:

	if (!sdev->tagged_supported)
		max_depth = 1;
	if (qdepth > max_depth)
		qdepth = max_depth;
	tag_type = (qdepth == 1) ? 0 : MSG_SIMPLE_TAG;
	scsi_adjust_queue_depth(sdev, tag_type, qdepth);

	if (sdev->inquiry_len > 7)
		sdev_printk(KERN_INFO, sdev, "qdepth(%d), tagged(%d), "
		"simple(%d), ordered(%d), scsi_level(%d), cmd_que(%d)\n",
		sdev->queue_depth, sdev->tagged_supported, sdev->simple_tags,
		sdev->ordered_tags, sdev->scsi_level,
		(sdev->inquiry[7] & 2) >> 1);

	return sdev->queue_depth;
}