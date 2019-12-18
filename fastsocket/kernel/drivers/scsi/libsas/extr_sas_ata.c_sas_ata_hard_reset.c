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
struct sas_phy {int dummy; } ;
struct sas_internal {TYPE_1__* dft; } ;
struct TYPE_4__ {int command_set; } ;
struct domain_device {TYPE_2__ sata_dev; } ;
struct ata_port {int /*<<< orphan*/  cbl; struct domain_device* private_data; } ;
struct ata_link {struct ata_port* ap; } ;
struct TYPE_3__ {int (* lldd_I_T_nexus_reset ) (struct domain_device*) ;} ;

/* Variables and functions */
#define  ATAPI_COMMAND_SET 129 
 int /*<<< orphan*/  ATA_CBL_SATA ; 
#define  ATA_COMMAND_SET 128 
 unsigned int ATA_DEV_ATA ; 
 unsigned int ATA_DEV_ATAPI ; 
 int EAGAIN ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int TMF_RESP_FUNC_COMPLETE ; 
 int ata_wait_after_reset (struct ata_link*,unsigned long,int (*) (struct ata_link*)) ; 
 struct sas_internal* dev_to_sas_internal (struct domain_device*) ; 
 int local_ata_check_ready (struct ata_link*) ; 
 int /*<<< orphan*/  sas_ata_printk (int /*<<< orphan*/ ,struct domain_device*,char*,...) ; 
 struct sas_phy* sas_get_local_phy (struct domain_device*) ; 
 int /*<<< orphan*/  sas_put_local_phy (struct sas_phy*) ; 
 scalar_t__ scsi_is_sas_phy_local (struct sas_phy*) ; 
 int smp_ata_check_ready (struct ata_link*) ; 
 int stub1 (struct domain_device*) ; 

__attribute__((used)) static int sas_ata_hard_reset(struct ata_link *link, unsigned int *class,
			      unsigned long deadline)
{
	int ret = 0, res;
	struct sas_phy *phy;
	struct ata_port *ap = link->ap;
	int (*check_ready)(struct ata_link *link);
	struct domain_device *dev = ap->private_data;
	struct sas_internal *i = dev_to_sas_internal(dev);

	res = i->dft->lldd_I_T_nexus_reset(dev);
	if (res == -ENODEV)
		return res;

	if (res != TMF_RESP_FUNC_COMPLETE)
		sas_ata_printk(KERN_DEBUG, dev, "Unable to reset ata device?\n");

	phy = sas_get_local_phy(dev);
	if (scsi_is_sas_phy_local(phy))
		check_ready = local_ata_check_ready;
	else
		check_ready = smp_ata_check_ready;
	sas_put_local_phy(phy);

	ret = ata_wait_after_reset(link, deadline, check_ready);	 
	if (ret && ret != -EAGAIN)
		sas_ata_printk(KERN_ERR, dev, "reset failed (errno=%d)\n", ret);
	
	/* XXX: if the class changes during the reset the upper layer
	 * should be informed, if the device has gone away we assume
	 * libsas will eventually delete it
	 */
	switch (dev->sata_dev.command_set) {
	case ATA_COMMAND_SET:
		*class = ATA_DEV_ATA;
		break;
	case ATAPI_COMMAND_SET:
		*class = ATA_DEV_ATAPI;
		break;
	}

	ap->cbl = ATA_CBL_SATA;
	return ret;
}