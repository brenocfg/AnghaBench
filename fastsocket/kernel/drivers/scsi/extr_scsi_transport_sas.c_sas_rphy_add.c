#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct sas_identify {scalar_t__ device_type; int target_port_protocols; } ;
struct sas_rphy {int scsi_target_id; TYPE_2__ dev; int /*<<< orphan*/  list; struct sas_identify identify; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct sas_port {struct sas_rphy* rphy; TYPE_1__ dev; } ;
struct sas_host_attrs {int /*<<< orphan*/  lock; int /*<<< orphan*/  next_target_id; int /*<<< orphan*/  rphy_list; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ SAS_END_DEVICE ; 
 int SAS_PROTOCOL_SATA ; 
 int SAS_PROTOCOL_SSP ; 
 int SAS_PROTOCOL_STP ; 
 int SCAN_WILD_CARD ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 struct sas_port* dev_to_sas_port (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sas_bsg_initialize (struct Scsi_Host*,struct sas_rphy*) ; 
 int /*<<< orphan*/  scsi_scan_target (TYPE_2__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct sas_host_attrs* to_sas_host_attrs (struct Scsi_Host*) ; 
 int /*<<< orphan*/  transport_add_device (TYPE_2__*) ; 
 int /*<<< orphan*/  transport_configure_device (TYPE_2__*) ; 

int sas_rphy_add(struct sas_rphy *rphy)
{
	struct sas_port *parent = dev_to_sas_port(rphy->dev.parent);
	struct Scsi_Host *shost = dev_to_shost(parent->dev.parent);
	struct sas_host_attrs *sas_host = to_sas_host_attrs(shost);
	struct sas_identify *identify = &rphy->identify;
	int error;

	if (parent->rphy)
		return -ENXIO;
	parent->rphy = rphy;

	error = device_add(&rphy->dev);
	if (error)
		return error;
	transport_add_device(&rphy->dev);
	transport_configure_device(&rphy->dev);
	if (sas_bsg_initialize(shost, rphy))
		printk("fail to a bsg device %s\n", dev_name(&rphy->dev));


	mutex_lock(&sas_host->lock);
	list_add_tail(&rphy->list, &sas_host->rphy_list);
	if (identify->device_type == SAS_END_DEVICE &&
	    (identify->target_port_protocols &
	     (SAS_PROTOCOL_SSP|SAS_PROTOCOL_STP|SAS_PROTOCOL_SATA)))
		rphy->scsi_target_id = sas_host->next_target_id++;
	else if (identify->device_type == SAS_END_DEVICE)
		rphy->scsi_target_id = -1;
	mutex_unlock(&sas_host->lock);

	if (identify->device_type == SAS_END_DEVICE &&
	    rphy->scsi_target_id != -1) {
		int lun;

		if (identify->target_port_protocols & SAS_PROTOCOL_SSP)
			lun = SCAN_WILD_CARD;
		else
			lun = 0;

		scsi_scan_target(&rphy->dev, 0, rphy->scsi_target_id, lun, 0);
	}

	return 0;
}