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
struct net_device {int dummy; } ;
struct ioc3_private {struct ioc3* regs; } ;
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int MICR_BUSY ; 
 int MICR_PHYADDR_SHIFT ; 
 int MICR_READTRIG ; 
 int MIDR_DATA_MASK ; 
 int ioc3_r_micr () ; 
 int ioc3_r_midr_r () ; 
 int /*<<< orphan*/  ioc3_w_micr (int) ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ioc3_mdio_read(struct net_device *dev, int phy, int reg)
{
	struct ioc3_private *ip = netdev_priv(dev);
	struct ioc3 *ioc3 = ip->regs;

	while (ioc3_r_micr() & MICR_BUSY);
	ioc3_w_micr((phy << MICR_PHYADDR_SHIFT) | reg | MICR_READTRIG);
	while (ioc3_r_micr() & MICR_BUSY);

	return ioc3_r_midr_r() & MIDR_DATA_MASK;
}