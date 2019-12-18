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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  REGISTER_TIMEOUT16 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  USB_EEPROM_READ ; 
 int /*<<< orphan*/  USB_VENDOR_REQUEST_IN ; 
 int rt2x00usb_vendor_request (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int rt2x00usb_eeprom_read(struct rt2x00_dev *rt2x00dev,
					__le16 *eeprom, const u16 length)
{
	return rt2x00usb_vendor_request(rt2x00dev, USB_EEPROM_READ,
					USB_VENDOR_REQUEST_IN, 0, 0,
					eeprom, length,
					REGISTER_TIMEOUT16(length));
}