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
 int /*<<< orphan*/  RF_WriteReg (struct net_device*,int,int) ; 
 int /*<<< orphan*/  RTL8225z2_ANAPARAM2_OFF ; 
 int /*<<< orphan*/  RTL8225z2_ANAPARAM_OFF ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rtl8180_set_anaparam (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8185_set_anaparam2 (struct net_device*,int /*<<< orphan*/ ) ; 

void rtl8225z2_rf_close(struct net_device *dev)
{
	RF_WriteReg(dev, 0x4, 0x1f);

	force_pci_posting(dev);
	mdelay(1);

	rtl8180_set_anaparam(dev, RTL8225z2_ANAPARAM_OFF);
	rtl8185_set_anaparam2(dev, RTL8225z2_ANAPARAM2_OFF);
}