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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int CMD_RST_SHIFT ; 
 int /*<<< orphan*/  DMESG (char*) ; 
 int /*<<< orphan*/  DMESGW (char*) ; 
 int /*<<< orphan*/  EPROM_CMD_LOAD ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8180_irq_disable (struct net_device*) ; 
 int /*<<< orphan*/  rtl8180_set_mode (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

void rtl8180_reset(struct net_device *dev)
{
	u8 cr;

	rtl8180_irq_disable(dev);

	cr=read_nic_byte(dev,CMD);
	cr = cr & 2;
	cr = cr | (1<<CMD_RST_SHIFT);
	write_nic_byte(dev,CMD,cr);

	force_pci_posting(dev);

	mdelay(200);

	if(read_nic_byte(dev,CMD) & (1<<CMD_RST_SHIFT))
		DMESGW("Card reset timeout!");
	else
		DMESG("Card successfully reset");

	rtl8180_set_mode(dev,EPROM_CMD_LOAD);
	force_pci_posting(dev);
	mdelay(200);
}