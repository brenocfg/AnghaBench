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
struct ex_phy {int /*<<< orphan*/  phy_state; scalar_t__ port; int /*<<< orphan*/  phy; int /*<<< orphan*/  attached_sas_addr; } ;
struct TYPE_2__ {int num_phys; struct ex_phy* ex_phy; } ;
struct domain_device {TYPE_1__ ex_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_DEVICE_DISCOVERED ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_port_add_phy (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sas_ex_join_wide_port(struct domain_device *parent, int phy_id)
{
	struct ex_phy *phy = &parent->ex_dev.ex_phy[phy_id];
	int i;

	for (i = 0; i < parent->ex_dev.num_phys; i++) {
		struct ex_phy *ephy = &parent->ex_dev.ex_phy[i];

		if (ephy == phy)
			continue;

		if (!memcmp(phy->attached_sas_addr, ephy->attached_sas_addr,
			    SAS_ADDR_SIZE) && ephy->port) {
			sas_port_add_phy(ephy->port, phy->phy);
			phy->port = ephy->port;
			phy->phy_state = PHY_DEVICE_DISCOVERED;
			return true;
		}
	}

	return false;
}