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
struct mv643xx_eth_private {int port_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_ADDR ; 
 int rdl (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrl (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void phy_addr_set(struct mv643xx_eth_private *mp, int phy_addr)
{
	int addr_shift = 5 * mp->port_num;
	u32 data;

	data = rdl(mp, PHY_ADDR);
	data &= ~(0x1f << addr_shift);
	data |= (phy_addr & 0x1f) << addr_shift;
	wrl(mp, PHY_ADDR, data);
}