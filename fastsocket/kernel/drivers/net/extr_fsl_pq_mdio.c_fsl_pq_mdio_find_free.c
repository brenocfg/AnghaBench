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
typedef  int u32 ;
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int PHY_MAX_ADDR ; 
 scalar_t__ get_phy_id (struct mii_bus*,int,int*) ; 

__attribute__((used)) static int fsl_pq_mdio_find_free(struct mii_bus *new_bus)
{
	int i;

	for (i = PHY_MAX_ADDR; i > 0; i--) {
		u32 phy_id;

		if (get_phy_id(new_bus, i, &phy_id))
			return -1;

		if (phy_id == 0xffffffff)
			break;
	}

	return i;
}