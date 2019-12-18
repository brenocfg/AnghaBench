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
struct fw_card {TYPE_1__* driver; } ;
struct TYPE_2__ {int (* update_phy_reg ) (struct fw_card*,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int PHY_BUS_RESET ; 
 int PHY_BUS_SHORT_RESET ; 
 int stub1 (struct fw_card*,int,int /*<<< orphan*/ ,int) ; 

int fw_core_initiate_bus_reset(struct fw_card *card, int short_reset)
{
	int reg = short_reset ? 5 : 1;
	int bit = short_reset ? PHY_BUS_SHORT_RESET : PHY_BUS_RESET;

	return card->driver->update_phy_reg(card, reg, 0, bit);
}