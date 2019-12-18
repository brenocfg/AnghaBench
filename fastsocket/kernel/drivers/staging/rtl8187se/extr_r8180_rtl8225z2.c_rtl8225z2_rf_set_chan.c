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

/* Variables and functions */
 int RF_ReadReg (struct net_device*,int) ; 
 int /*<<< orphan*/  RF_WriteReg (struct net_device*,int,int) ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int* rtl8225_chan ; 
 int /*<<< orphan*/  rtl8225z2_SetTXPowerLevel (struct net_device*,short) ; 

void rtl8225z2_rf_set_chan(struct net_device *dev, short ch)
{
	rtl8225z2_SetTXPowerLevel(dev, ch);

	RF_WriteReg(dev, 0x7, rtl8225_chan[ch]);

	if ((RF_ReadReg(dev, 0x7) & 0x0F80) != rtl8225_chan[ch])
		RF_WriteReg(dev, 0x7, rtl8225_chan[ch]);

	mdelay(1);

	force_pci_posting(dev);
	mdelay(10);
}