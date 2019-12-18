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
typedef  int /*<<< orphan*/  u8 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int FW_BAD_CRC ; 
 int FW_BAD_LENGTH ; 
 int FW_BAD_VERSION ; 
 int FW_OK ; 
 int /*<<< orphan*/  RT2860 ; 
 int /*<<< orphan*/  RT2872 ; 
 int /*<<< orphan*/  RT3070 ; 
 int /*<<< orphan*/  RT3290 ; 
 int /*<<< orphan*/  rt2800_check_firmware_crc (int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ rt2x00_is_usb (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

int rt2800_check_firmware(struct rt2x00_dev *rt2x00dev,
			  const u8 *data, const size_t len)
{
	size_t offset = 0;
	size_t fw_len;
	bool multiple;

	/*
	 * PCI(e) & SOC devices require firmware with a length
	 * of 8kb. USB devices require firmware files with a length
	 * of 4kb. Certain USB chipsets however require different firmware,
	 * which Ralink only provides attached to the original firmware
	 * file. Thus for USB devices, firmware files have a length
	 * which is a multiple of 4kb. The firmware for rt3290 chip also
	 * have a length which is a multiple of 4kb.
	 */
	if (rt2x00_is_usb(rt2x00dev) || rt2x00_rt(rt2x00dev, RT3290))
		fw_len = 4096;
	else
		fw_len = 8192;

	multiple = true;
	/*
	 * Validate the firmware length
	 */
	if (len != fw_len && (!multiple || (len % fw_len) != 0))
		return FW_BAD_LENGTH;

	/*
	 * Check if the chipset requires one of the upper parts
	 * of the firmware.
	 */
	if (rt2x00_is_usb(rt2x00dev) &&
	    !rt2x00_rt(rt2x00dev, RT2860) &&
	    !rt2x00_rt(rt2x00dev, RT2872) &&
	    !rt2x00_rt(rt2x00dev, RT3070) &&
	    ((len / fw_len) == 1))
		return FW_BAD_VERSION;

	/*
	 * 8kb firmware files must be checked as if it were
	 * 2 separate firmware files.
	 */
	while (offset < len) {
		if (!rt2800_check_firmware_crc(data + offset, fw_len))
			return FW_BAD_CRC;

		offset += fw_len;
	}

	return FW_OK;
}