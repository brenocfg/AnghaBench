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
typedef  int /*<<< orphan*/  u8 ;
struct expander_device {int num_phys; struct ex_phy* ex_phy; } ;
struct ex_phy {scalar_t__ phy_state; scalar_t__ attached_dev_type; scalar_t__ routing_attr; int /*<<< orphan*/  attached_sas_addr; } ;
struct domain_device {struct expander_device ex_dev; } ;

/* Variables and functions */
 scalar_t__ EDGE_DEV ; 
 scalar_t__ FANOUT_DEV ; 
 scalar_t__ PHY_NOT_PRESENT ; 
 scalar_t__ PHY_VACANT ; 
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 scalar_t__ SUBTRACTIVE_ROUTING ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sas_find_sub_addr(struct domain_device *dev, u8 *sub_addr)
{
	struct expander_device *ex = &dev->ex_dev;
	int i;

	for (i = 0; i < ex->num_phys; i++) {
		struct ex_phy *phy = &ex->ex_phy[i];

		if (phy->phy_state == PHY_VACANT ||
		    phy->phy_state == PHY_NOT_PRESENT)
			continue;

		if ((phy->attached_dev_type == EDGE_DEV ||
		     phy->attached_dev_type == FANOUT_DEV) &&
		    phy->routing_attr == SUBTRACTIVE_ROUTING) {

			memcpy(sub_addr, phy->attached_sas_addr,SAS_ADDR_SIZE);

			return 1;
		}
	}
	return 0;
}