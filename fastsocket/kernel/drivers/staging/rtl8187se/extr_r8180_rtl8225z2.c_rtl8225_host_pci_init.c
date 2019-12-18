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
 int /*<<< orphan*/  GP_ENABLE ; 
 int /*<<< orphan*/  RFPinsOutput ; 
 int /*<<< orphan*/  RFPinsSelect ; 
 int SW_CONTROL_GPIO ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rtl8185_rf_pins_enable (struct net_device*) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8225_host_pci_init(struct net_device *dev)
{
	write_nic_word(dev, RFPinsOutput, 0x480);

	rtl8185_rf_pins_enable(dev);

	write_nic_word(dev, RFPinsSelect, 0x88 | SW_CONTROL_GPIO);

	write_nic_byte(dev, GP_ENABLE, 0);

	force_pci_posting(dev);
	mdelay(200);

	/* bit 6 is for RF on/off detection */
	write_nic_word(dev, GP_ENABLE, 0xff & (~(1 << 6)));
}