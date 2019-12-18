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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int /*<<< orphan*/  rssi_offset; int /*<<< orphan*/  cap_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPABILITY_CONTROL_FILTERS ; 
 int /*<<< orphan*/  CAPABILITY_CONTROL_FILTER_PSPOLL ; 
 int /*<<< orphan*/  CAPABILITY_HW_CRYPTO ; 
 int /*<<< orphan*/  CAPABILITY_LINK_TUNING ; 
 int /*<<< orphan*/  CAPABILITY_PRE_TBTT_INTERRUPT ; 
 int /*<<< orphan*/  DEFAULT_RSSI_OFFSET ; 
 int /*<<< orphan*/  GPIO_CTRL ; 
 int /*<<< orphan*/  GPIO_CTRL_DIR2 ; 
 int /*<<< orphan*/  REQUIRE_DMA ; 
 int /*<<< orphan*/  REQUIRE_FIRMWARE ; 
 int /*<<< orphan*/  REQUIRE_HT_TX_DESC ; 
 int /*<<< orphan*/  REQUIRE_L2PAD ; 
 int /*<<< orphan*/  REQUIRE_PS_AUTOWAKE ; 
 int /*<<< orphan*/  REQUIRE_TASKLET_CONTEXT ; 
 int /*<<< orphan*/  REQUIRE_TXSTATUS_FIFO ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_hwcrypt_disabled (struct rt2x00_dev*) ; 
 int rt2800_init_eeprom (struct rt2x00_dev*) ; 
 int rt2800_probe_hw_mode (struct rt2x00_dev*) ; 
 int rt2800_probe_rt (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt2800_validate_eeprom (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_is_soc (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_is_usb (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int rt2800_probe_hw(struct rt2x00_dev *rt2x00dev)
{
	int retval;
	u32 reg;

	retval = rt2800_probe_rt(rt2x00dev);
	if (retval)
		return retval;

	/*
	 * Allocate eeprom data.
	 */
	retval = rt2800_validate_eeprom(rt2x00dev);
	if (retval)
		return retval;

	retval = rt2800_init_eeprom(rt2x00dev);
	if (retval)
		return retval;

	/*
	 * Enable rfkill polling by setting GPIO direction of the
	 * rfkill switch GPIO pin correctly.
	 */
	rt2800_register_read(rt2x00dev, GPIO_CTRL, &reg);
	rt2x00_set_field32(&reg, GPIO_CTRL_DIR2, 1);
	rt2800_register_write(rt2x00dev, GPIO_CTRL, reg);

	/*
	 * Initialize hw specifications.
	 */
	retval = rt2800_probe_hw_mode(rt2x00dev);
	if (retval)
		return retval;

	/*
	 * Set device capabilities.
	 */
	__set_bit(CAPABILITY_CONTROL_FILTERS, &rt2x00dev->cap_flags);
	__set_bit(CAPABILITY_CONTROL_FILTER_PSPOLL, &rt2x00dev->cap_flags);
	if (!rt2x00_is_usb(rt2x00dev))
		__set_bit(CAPABILITY_PRE_TBTT_INTERRUPT, &rt2x00dev->cap_flags);

	/*
	 * Set device requirements.
	 */
	if (!rt2x00_is_soc(rt2x00dev))
		__set_bit(REQUIRE_FIRMWARE, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_L2PAD, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_TXSTATUS_FIFO, &rt2x00dev->cap_flags);
	if (!rt2800_hwcrypt_disabled(rt2x00dev))
		__set_bit(CAPABILITY_HW_CRYPTO, &rt2x00dev->cap_flags);
	__set_bit(CAPABILITY_LINK_TUNING, &rt2x00dev->cap_flags);
	__set_bit(REQUIRE_HT_TX_DESC, &rt2x00dev->cap_flags);
	if (rt2x00_is_usb(rt2x00dev))
		__set_bit(REQUIRE_PS_AUTOWAKE, &rt2x00dev->cap_flags);
	else {
		__set_bit(REQUIRE_DMA, &rt2x00dev->cap_flags);
		__set_bit(REQUIRE_TASKLET_CONTEXT, &rt2x00dev->cap_flags);
	}

	/*
	 * Set the rssi offset.
	 */
	rt2x00dev->rssi_offset = DEFAULT_RSSI_OFFSET;

	return 0;
}