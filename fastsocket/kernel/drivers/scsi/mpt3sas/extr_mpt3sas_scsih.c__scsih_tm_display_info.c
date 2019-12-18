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
struct scsi_target {struct MPT3SAS_TARGET* hostdata; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct _sas_device {unsigned long long volume_handle; unsigned long long slot; scalar_t__ enclosure_logical_id; int /*<<< orphan*/  phy; scalar_t__ sas_address; int /*<<< orphan*/  handle; scalar_t__ volume_wwid; } ;
struct MPT3SAS_TARGET {int flags; scalar_t__ sas_address; int /*<<< orphan*/  handle; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  sas_device_lock; } ;
struct TYPE_2__ {struct scsi_target* sdev_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int MPT_TARGET_FLAGS_RAID_COMPONENT ; 
 int MPT_TARGET_FLAGS_VOLUME ; 
 struct _sas_device* mpt3sas_scsih_sas_device_find_by_sas_address (struct MPT3SAS_ADAPTER*,scalar_t__) ; 
 int /*<<< orphan*/  scsi_print_command (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  starget_printk (int /*<<< orphan*/ ,struct scsi_target*,char*,...) ; 

__attribute__((used)) static void
_scsih_tm_display_info(struct MPT3SAS_ADAPTER *ioc, struct scsi_cmnd *scmd)
{
	struct scsi_target *starget = scmd->device->sdev_target;
	struct MPT3SAS_TARGET *priv_target = starget->hostdata;
	struct _sas_device *sas_device = NULL;
	unsigned long flags;
	char *device_str = NULL;

	if (!priv_target)
		return;
	device_str = "volume";

	scsi_print_command(scmd);
	if (priv_target->flags & MPT_TARGET_FLAGS_VOLUME) {
		starget_printk(KERN_INFO, starget,
			"%s handle(0x%04x), %s wwid(0x%016llx)\n",
			device_str, priv_target->handle,
		    device_str, (unsigned long long)priv_target->sas_address);
	} else {
		spin_lock_irqsave(&ioc->sas_device_lock, flags);
		sas_device = mpt3sas_scsih_sas_device_find_by_sas_address(ioc,
		    priv_target->sas_address);
		if (sas_device) {
			if (priv_target->flags &
			    MPT_TARGET_FLAGS_RAID_COMPONENT) {
				starget_printk(KERN_INFO, starget,
				    "volume handle(0x%04x), "
				    "volume wwid(0x%016llx)\n",
				    sas_device->volume_handle,
				   (unsigned long long)sas_device->volume_wwid);
			}
			starget_printk(KERN_INFO, starget,
			    "handle(0x%04x), sas_address(0x%016llx), phy(%d)\n",
			    sas_device->handle,
			    (unsigned long long)sas_device->sas_address,
			    sas_device->phy);
			starget_printk(KERN_INFO, starget,
			    "enclosure_logical_id(0x%016llx), slot(%d)\n",
			   (unsigned long long)sas_device->enclosure_logical_id,
			    sas_device->slot);
		}
		spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	}
}