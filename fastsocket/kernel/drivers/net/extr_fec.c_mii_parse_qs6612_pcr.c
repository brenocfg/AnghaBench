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
typedef  int uint ;
struct net_device {int dummy; } ;
struct fec_enet_private {int phy_status; } ;

/* Variables and functions */
 int PHY_STAT_100FDX ; 
 int PHY_STAT_100HDX ; 
 int PHY_STAT_10FDX ; 
 int PHY_STAT_10HDX ; 
 int volatile PHY_STAT_SPMASK ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mii_parse_qs6612_pcr(uint mii_reg, struct net_device *dev)
{
	struct fec_enet_private *fep = netdev_priv(dev);
	volatile uint *s = &(fep->phy_status);
	uint status;

	status = *s & ~(PHY_STAT_SPMASK);

	switch((mii_reg >> 2) & 7) {
	case 1: status |= PHY_STAT_10HDX; break;
	case 2: status |= PHY_STAT_100HDX; break;
	case 5: status |= PHY_STAT_10FDX; break;
	case 6: status |= PHY_STAT_100FDX; break;
}

	*s = status;
}