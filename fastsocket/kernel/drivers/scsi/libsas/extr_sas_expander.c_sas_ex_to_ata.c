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
struct sas_rphy {int dummy; } ;
struct ex_phy {TYPE_2__* port; } ;
struct TYPE_3__ {struct ex_phy* ex_phy; } ;
struct domain_device {TYPE_1__ ex_dev; } ;
struct TYPE_4__ {struct sas_rphy* rphy; } ;

/* Variables and functions */
 scalar_t__ dev_is_sata (struct domain_device*) ; 
 struct domain_device* sas_find_dev_by_rphy (struct sas_rphy*) ; 

struct domain_device *sas_ex_to_ata(struct domain_device *ex_dev, int phy_id)
{
	struct ex_phy *ex_phy = &ex_dev->ex_dev.ex_phy[phy_id];
	struct domain_device *dev;
	struct sas_rphy *rphy;

	if (!ex_phy->port)
		return NULL;

	rphy = ex_phy->port->rphy;
	if (!rphy)
		return NULL;

	dev = sas_find_dev_by_rphy(rphy);

	if (dev && dev_is_sata(dev))
		return dev;

	return NULL;
}