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
struct lpphy_tx_gain_table_entry {int dummy; } ;
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpphy_rev0_1_write_gain_table (struct b43_wldev*,int,struct lpphy_tx_gain_table_entry) ; 
 int /*<<< orphan*/  lpphy_rev2plus_write_gain_table (struct b43_wldev*,int,struct lpphy_tx_gain_table_entry) ; 

void lpphy_write_gain_table(struct b43_wldev *dev, int offset,
			    struct lpphy_tx_gain_table_entry data)
{
	if (dev->phy.rev >= 2)
		lpphy_rev2plus_write_gain_table(dev, offset, data);
	else
		lpphy_rev0_1_write_gain_table(dev, offset, data);
}