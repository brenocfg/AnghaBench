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
struct sas_phy {size_t number; } ;
struct ex_phy {int attached_dev_type; int /*<<< orphan*/  attached_sata_dev; } ;
struct TYPE_2__ {struct ex_phy* ex_phy; } ;
struct domain_device {TYPE_1__ ex_dev; struct domain_device* parent; } ;
struct ata_port {struct domain_device* private_data; } ;
struct ata_link {struct ata_port* ap; } ;

/* Variables and functions */
 int ECOMM ; 
 int ENODEV ; 
#define  SAS_END_DEV 129 
#define  SATA_PENDING 128 
 int SMP_RESP_FUNC_ACC ; 
 int sas_ata_clear_pending (struct domain_device*,struct ex_phy*) ; 
 int sas_ex_phy_discover (struct domain_device*,size_t) ; 
 struct sas_phy* sas_get_local_phy (struct domain_device*) ; 
 int /*<<< orphan*/  sas_put_local_phy (struct sas_phy*) ; 

__attribute__((used)) static int smp_ata_check_ready(struct ata_link *link)
{
	int res;
	struct ata_port *ap = link->ap;
	struct domain_device *dev = ap->private_data;
	struct domain_device *ex_dev = dev->parent;
	struct sas_phy *phy = sas_get_local_phy(dev);
	struct ex_phy *ex_phy = &ex_dev->ex_dev.ex_phy[phy->number];

	res = sas_ex_phy_discover(ex_dev, phy->number);
	sas_put_local_phy(phy);

	/* break the wait early if the expander is unreachable,
	 * otherwise keep polling
	 */
	if (res == -ECOMM)
		return res;
	if (res != SMP_RESP_FUNC_ACC)
		return 0;

	switch (ex_phy->attached_dev_type) {
	case SATA_PENDING:
		return 0;
	case SAS_END_DEV:
		if (ex_phy->attached_sata_dev)
			return sas_ata_clear_pending(dev, ex_phy);
	default:
		return -ENODEV;
	}
}