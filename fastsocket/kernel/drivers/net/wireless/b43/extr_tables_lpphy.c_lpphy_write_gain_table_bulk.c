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
struct lpphy_tx_gain_table_entry {int dummy; } ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpphy_write_gain_table (struct b43_wldev*,int,struct lpphy_tx_gain_table_entry) ; 

void lpphy_write_gain_table_bulk(struct b43_wldev *dev, int offset, int count,
				 struct lpphy_tx_gain_table_entry *table)
{
	int i;

	for (i = offset; i < count; i++)
		lpphy_write_gain_table(dev, i, table[i]);
}