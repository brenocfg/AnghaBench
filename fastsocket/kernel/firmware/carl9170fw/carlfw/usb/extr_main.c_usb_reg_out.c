#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {TYPE_1__ reserved; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_USB_REG_EP4_BYTE_COUNT_HIGH ; 
 int /*<<< orphan*/  AR9170_USB_REG_EP4_BYTE_COUNT_LOW ; 
 int /*<<< orphan*/  AR9170_USB_REG_EP4_DATA ; 
 TYPE_2__ dma_mem ; 
 int /*<<< orphan*/  get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_int_buf () ; 
 int getb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_cmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_reset_out () ; 
 int /*<<< orphan*/  usb_trigger_in () ; 

__attribute__((used)) static void usb_reg_out(void)
{
	uint32_t *regaddr = (uint32_t *) &dma_mem.reserved.cmd;
	uint16_t usbfifolen, i;

	usb_reset_out();

	usbfifolen = getb(AR9170_USB_REG_EP4_BYTE_COUNT_LOW) |
		     getb(AR9170_USB_REG_EP4_BYTE_COUNT_HIGH) << 8;

	if (usbfifolen & 0x3)
		usbfifolen = (usbfifolen >> 2) + 1;
	else
		usbfifolen = usbfifolen >> 2;

	for (i = 0; i < usbfifolen; i++)
		*regaddr++ = get(AR9170_USB_REG_EP4_DATA);

	handle_cmd(get_int_buf());

	usb_trigger_in();
}