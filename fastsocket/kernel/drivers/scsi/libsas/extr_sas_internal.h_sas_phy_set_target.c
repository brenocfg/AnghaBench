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
struct TYPE_2__ {scalar_t__ target_port_protocols; int /*<<< orphan*/  device_type; } ;
struct sas_phy {TYPE_1__ identify; } ;
struct domain_device {scalar_t__ tproto; int /*<<< orphan*/  dev_type; } ;
struct asd_sas_phy {struct sas_phy* phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_END_DEVICE ; 
 int /*<<< orphan*/  SAS_PHY_UNUSED ; 
 scalar_t__ dev_is_sata (struct domain_device*) ; 

__attribute__((used)) static inline void sas_phy_set_target(struct asd_sas_phy *p, struct domain_device *dev)
{
	struct sas_phy *phy = p->phy;

	if (dev) {
		if (dev_is_sata(dev))
			phy->identify.device_type = SAS_END_DEVICE;
		else
			phy->identify.device_type = dev->dev_type;
		phy->identify.target_port_protocols = dev->tproto;
	} else {
		phy->identify.device_type = SAS_PHY_UNUSED;
		phy->identify.target_port_protocols = 0;
	}
}