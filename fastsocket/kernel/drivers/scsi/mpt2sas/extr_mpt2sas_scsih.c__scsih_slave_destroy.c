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
struct scsi_target {int /*<<< orphan*/  dev; struct MPT2SAS_TARGET* hostdata; } ;
struct scsi_device {int /*<<< orphan*/ * hostdata; } ;
struct _sas_device {int /*<<< orphan*/ * starget; } ;
struct Scsi_Host {int dummy; } ;
struct MPT2SAS_TARGET {int flags; int /*<<< orphan*/  num_luns; int /*<<< orphan*/  sas_address; } ;
struct MPT2SAS_ADAPTER {int /*<<< orphan*/  sas_device_lock; } ;

/* Variables and functions */
 int MPT_TARGET_FLAGS_VOLUME ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct _sas_device* mpt2sas_scsih_sas_device_find_by_sas_address (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 struct scsi_target* scsi_target (struct scsi_device*) ; 
 struct MPT2SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
_scsih_slave_destroy(struct scsi_device *sdev)
{
	struct MPT2SAS_TARGET *sas_target_priv_data;
	struct scsi_target *starget;
	struct Scsi_Host *shost;
	struct MPT2SAS_ADAPTER *ioc;
	struct _sas_device *sas_device;
	unsigned long flags;

	if (!sdev->hostdata)
		return;

	starget = scsi_target(sdev);
	sas_target_priv_data = starget->hostdata;
	sas_target_priv_data->num_luns--;

	shost = dev_to_shost(&starget->dev);
	ioc = shost_priv(shost);

	if (!(sas_target_priv_data->flags & MPT_TARGET_FLAGS_VOLUME)) {
		spin_lock_irqsave(&ioc->sas_device_lock, flags);
		sas_device = mpt2sas_scsih_sas_device_find_by_sas_address(ioc,
		   sas_target_priv_data->sas_address);
		if (sas_device && !sas_target_priv_data->num_luns)
			sas_device->starget = NULL;
		spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	}

	kfree(sdev->hostdata);
	sdev->hostdata = NULL;
}