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
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct scsi_target {scalar_t__ channel; scalar_t__ id; struct MPT2SAS_TARGET* hostdata; TYPE_2__ dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  sas_address; } ;
struct sas_rphy {TYPE_1__ identify; } ;
struct _sas_device {scalar_t__ id; scalar_t__ channel; struct scsi_target* starget; } ;
struct _raid_device {int /*<<< orphan*/ * sdev; int /*<<< orphan*/ * starget; } ;
struct Scsi_Host {int dummy; } ;
struct MPT2SAS_TARGET {int dummy; } ;
struct MPT2SAS_ADAPTER {int /*<<< orphan*/  sas_device_lock; int /*<<< orphan*/  raid_device_lock; } ;

/* Variables and functions */
 scalar_t__ RAID_CHANNEL ; 
 struct _raid_device* _scsih_raid_device_find_by_id (struct MPT2SAS_ADAPTER*,scalar_t__,scalar_t__) ; 
 struct sas_rphy* dev_to_rphy (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* dev_to_shost (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct MPT2SAS_TARGET*) ; 
 struct _sas_device* mpt2sas_scsih_sas_device_find_by_sas_address (struct MPT2SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 struct MPT2SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
_scsih_target_destroy(struct scsi_target *starget)
{
	struct Scsi_Host *shost = dev_to_shost(&starget->dev);
	struct MPT2SAS_ADAPTER *ioc = shost_priv(shost);
	struct MPT2SAS_TARGET *sas_target_priv_data;
	struct _sas_device *sas_device;
	struct _raid_device *raid_device;
	unsigned long flags;
	struct sas_rphy *rphy;

	sas_target_priv_data = starget->hostdata;
	if (!sas_target_priv_data)
		return;

	if (starget->channel == RAID_CHANNEL) {
		spin_lock_irqsave(&ioc->raid_device_lock, flags);
		raid_device = _scsih_raid_device_find_by_id(ioc, starget->id,
		    starget->channel);
		if (raid_device) {
			raid_device->starget = NULL;
			raid_device->sdev = NULL;
		}
		spin_unlock_irqrestore(&ioc->raid_device_lock, flags);
		goto out;
	}

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	rphy = dev_to_rphy(starget->dev.parent);
	sas_device = mpt2sas_scsih_sas_device_find_by_sas_address(ioc,
	   rphy->identify.sas_address);
	if (sas_device && (sas_device->starget == starget) &&
	    (sas_device->id == starget->id) &&
	    (sas_device->channel == starget->channel))
		sas_device->starget = NULL;

	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);

 out:
	kfree(sas_target_priv_data);
	starget->hostdata = NULL;
}