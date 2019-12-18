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
typedef  scalar_t__ u32 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  FIRMWARE_IMAGE_BASE ; 
 int /*<<< orphan*/  MAC_CSR0 ; 
 int /*<<< orphan*/  REGISTER_TIMEOUT_FIRMWARE ; 
 int /*<<< orphan*/  USB_DEVICE_MODE ; 
 int /*<<< orphan*/  USB_MODE_FIRMWARE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 
 int /*<<< orphan*/  rt2x00usb_register_multiwrite (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t const) ; 
 int /*<<< orphan*/  rt2x00usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int rt2x00usb_vendor_request_sw (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt73usb_load_firmware(struct rt2x00_dev *rt2x00dev,
				 const u8 *data, const size_t len)
{
	unsigned int i;
	int status;
	u32 reg;

	/*
	 * Wait for stable hardware.
	 */
	for (i = 0; i < 100; i++) {
		rt2x00usb_register_read(rt2x00dev, MAC_CSR0, &reg);
		if (reg)
			break;
		msleep(1);
	}

	if (!reg) {
		rt2x00_err(rt2x00dev, "Unstable hardware\n");
		return -EBUSY;
	}

	/*
	 * Write firmware to device.
	 */
	rt2x00usb_register_multiwrite(rt2x00dev, FIRMWARE_IMAGE_BASE, data, len);

	/*
	 * Send firmware request to device to load firmware,
	 * we need to specify a long timeout time.
	 */
	status = rt2x00usb_vendor_request_sw(rt2x00dev, USB_DEVICE_MODE,
					     0, USB_MODE_FIRMWARE,
					     REGISTER_TIMEOUT_FIRMWARE);
	if (status < 0) {
		rt2x00_err(rt2x00dev, "Failed to write Firmware to device\n");
		return status;
	}

	return 0;
}