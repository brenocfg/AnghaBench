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
typedef  int u16 ;
struct s6gmac {scalar_t__ reg; } ;
struct mii_bus {struct s6gmac* priv; } ;

/* Variables and functions */
 int ETIME ; 
 scalar_t__ S6_GMAC_MACMIIADDR ; 
 int S6_GMAC_MACMIIADDR_PHY ; 
 int S6_GMAC_MACMIIADDR_REG ; 
 scalar_t__ S6_GMAC_MACMIICMD ; 
 int S6_GMAC_MACMIICMD_READ ; 
 scalar_t__ S6_GMAC_MACMIISTAT ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ s6mii_busy (struct s6gmac*,int) ; 
 int /*<<< orphan*/  s6mii_enable (struct s6gmac*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int s6mii_read(struct mii_bus *bus, int phy_addr, int regnum)
{
	struct s6gmac *pd = bus->priv;
	s6mii_enable(pd);
	if (s6mii_busy(pd, 256))
		return -ETIME;
	writel(phy_addr << S6_GMAC_MACMIIADDR_PHY |
		regnum << S6_GMAC_MACMIIADDR_REG,
		pd->reg + S6_GMAC_MACMIIADDR);
	writel(1 << S6_GMAC_MACMIICMD_READ, pd->reg + S6_GMAC_MACMIICMD);
	writel(0, pd->reg + S6_GMAC_MACMIICMD);
	if (s6mii_busy(pd, 256))
		return -ETIME;
	return (u16)readl(pd->reg + S6_GMAC_MACMIISTAT);
}