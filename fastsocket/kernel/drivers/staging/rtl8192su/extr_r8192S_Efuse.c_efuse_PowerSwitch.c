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
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFUSE_CLK ; 
 scalar_t__ EFUSE_TEST ; 
 scalar_t__ TRUE ; 
 scalar_t__ read_nic_byte (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,scalar_t__,int) ; 

__attribute__((used)) static	void
efuse_PowerSwitch(struct net_device* dev, u8 PwrState)
{
	u8	tempval;
	if (PwrState == TRUE)
	{
		// Enable LDO 2.5V for write action
		tempval = read_nic_byte(dev, EFUSE_TEST+3);
		write_nic_byte(dev, EFUSE_TEST+3, (tempval | 0x80));

		// Change Efuse Clock for write action to 40MHZ
		write_nic_byte(dev, EFUSE_CLK, 0x03);
	}
	else
	{
		// Enable LDO 2.5V for write action
		tempval = read_nic_byte(dev, EFUSE_TEST+3);
		write_nic_byte(dev, EFUSE_TEST+3, (tempval & 0x7F));

		// Change Efuse Clock for write action to 500K
		write_nic_byte(dev, EFUSE_CLK, 0x02);
	}

}