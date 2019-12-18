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
struct usb_pcwd_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_READ_TEMP ; 
 int /*<<< orphan*/  usb_pcwd_send_command (struct usb_pcwd_private*,int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 

__attribute__((used)) static int usb_pcwd_get_temperature(struct usb_pcwd_private *usb_pcwd,
							int *temperature)
{
	unsigned char msb, lsb;

	usb_pcwd_send_command(usb_pcwd, CMD_READ_TEMP, &msb, &lsb);

	/*
	 * Convert celsius to fahrenheit, since this was
	 * the decided 'standard' for this return value.
	 */
	*temperature = (lsb * 9 / 5) + 32;

	return 0;
}