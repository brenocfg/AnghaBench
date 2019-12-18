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

/* Variables and functions */
 int MDCLKH ; 
 int /*<<< orphan*/  outl (int,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void phy_write_1bit(unsigned long ioaddr, u32 phy_data)
{
	outl(phy_data, ioaddr);			/* MII Clock Low */
	udelay(1);
	outl(phy_data | MDCLKH, ioaddr);	/* MII Clock High */
	udelay(1);
	outl(phy_data, ioaddr);			/* MII Clock Low */
	udelay(1);
}