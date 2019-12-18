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
 int ETH_P_8021Q ; 
 scalar_t__ MAC_CONTROL ; 
 int MAC_CORE_INIT ; 
 scalar_t__ MAC_VLAN1 ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mac100_core_init(unsigned long ioaddr)
{
	u32 value = readl(ioaddr + MAC_CONTROL);

	writel((value | MAC_CORE_INIT), ioaddr + MAC_CONTROL);

#ifdef STMMAC_VLAN_TAG_USED
	writel(ETH_P_8021Q, ioaddr + MAC_VLAN1);
#endif
	return;
}