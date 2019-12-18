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
typedef  int u8 ;
typedef  int u32 ;
struct smsc9420_pdata {int dummy; } ;
struct net_device {int* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRH ; 
 int /*<<< orphan*/  ADDRL ; 
 struct smsc9420_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void smsc9420_set_mac_address(struct net_device *dev)
{
	struct smsc9420_pdata *pd = netdev_priv(dev);
	u8 *dev_addr = dev->dev_addr;
	u32 mac_high16 = (dev_addr[5] << 8) | dev_addr[4];
	u32 mac_low32 = (dev_addr[3] << 24) | (dev_addr[2] << 16) |
	    (dev_addr[1] << 8) | dev_addr[0];

	smsc9420_reg_write(pd, ADDRH, mac_high16);
	smsc9420_reg_write(pd, ADDRL, mac_low32);
}