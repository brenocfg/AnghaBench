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
struct domain_device {int /*<<< orphan*/  rphy; } ;
struct asd_sas_phy {TYPE_1__* port; } ;
struct TYPE_2__ {struct domain_device* port_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ dev_is_sata (struct domain_device*) ; 
 int /*<<< orphan*/  sas_ata_schedule_reset (struct domain_device*) ; 
 int /*<<< orphan*/  sas_ata_wait_eh (struct domain_device*) ; 
 struct domain_device* sas_find_dev_by_rphy (int /*<<< orphan*/ ) ; 

int sas_try_ata_reset(struct asd_sas_phy *asd_phy)
{
	struct domain_device *dev = NULL;

	/* try to route user requested link resets through libata */
	if (asd_phy->port)
		dev = asd_phy->port->port_dev;

	/* validate that dev has been probed */
	if (dev)
		dev = sas_find_dev_by_rphy(dev->rphy);

	if (dev && dev_is_sata(dev)) {
		sas_ata_schedule_reset(dev);
		sas_ata_wait_eh(dev);
		return 0;
	}

	return -ENODEV;
}