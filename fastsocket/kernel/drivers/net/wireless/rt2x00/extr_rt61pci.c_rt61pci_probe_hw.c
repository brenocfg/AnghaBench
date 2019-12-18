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
struct rt2x00_dev {int /*<<< orphan*/  rssi_offset; int /*<<< orphan*/  cap_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPABILITY_CONTROL_FILTERS ; 
 int /*<<< orphan*/  CAPABILITY_HW_CRYPTO ; 
 int /*<<< orphan*/  CAPABILITY_LINK_TUNING ; 
 int /*<<< orphan*/  DEFAULT_RSSI_OFFSET ; 
 int /*<<< orphan*/  MAC_CSR13 ; 
 int /*<<< orphan*/  MAC_CSR13_DIR5 ; 
 int /*<<< orphan*/  REQUIRE_DMA ; 
 int /*<<< orphan*/  REQUIRE_FIRMWARE ; 
 int /*<<< orphan*/  SOFT_RESET_CSR ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  modparam_nohwcrypt ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int) ; 
 int rt61pci_init_eeprom (struct rt2x00_dev*) ; 
 int rt61pci_probe_hw_mode (struct rt2x00_dev*) ; 
 int rt61pci_validate_eeprom (struct rt2x00_dev*) ; 

__attribute__((used)) static int rt61pci_probe_hw(struct rt2x00_dev *rt2x00dev)
{
	int retval;
	u32 reg;

	/*
	 * Disable power saving.
	 */
	rt2x00mmio_register_write(rt2x00dev, SOFT_RESET_CSR, 0x00000007);

	/*
	 * Allocate eeprom data.
	 */
	retval = rt61pci_validate_eeprom(rt2x00dev);
	if (retval)
		return retval;

	retval = rt61pci_init_eeprom(rt2x00dev);
	if (retval)
		return retval;

	/*
	 * Enable rfkill polling by setting GPIO direction of the
	 * rfkill switch GPIO pin correctly.
	 */
	rt2x00mmio_register_read(rt2x00dev, MAC_CSR13, &reg);
	rt2x00_set_field32(&reg, MAC_CSR13_DIR5, 1);
	rt2x00mmio_register_write(rt2x00dev, MAC_CSR13, reg);

	/*
	 * Initialize hw specifications.
	 */
	retval = rt61pci_probe_hw_mode(rt2x00dev);
	if (retval)
		return retval;

	/*
	 * This device has multiple filters for control frames,
	 * but has no a separate filter for PS Poll frames.
	 */
	__set_bit(CAPABILITY_CONTROL_FILTERS, &rt2x00dev->cap_flags);

	/*
	 * This device requires firmware and DMA mapped skbs.
	 */
	__set_bit(REQUIRE_FIRMWARE, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_DMA, &rt2x00dev->cap_flags);
	if (!modparam_nohwcrypt)
		__set_bit(CAPABILITY_HW_CRYPTO, &rt2x00dev->cap_flags);
	__set_bit(CAPABILITY_LINK_TUNING, &rt2x00dev->cap_flags);

	/*
	 * Set the rssi offset.
	 */
	rt2x00dev->rssi_offset = DEFAULT_RSSI_OFFSET;

	return 0;
}