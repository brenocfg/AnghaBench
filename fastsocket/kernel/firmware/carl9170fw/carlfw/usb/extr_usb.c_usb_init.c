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
struct TYPE_3__ {int config; int /*<<< orphan*/  device_feature; } ;
struct TYPE_4__ {TYPE_1__ usb; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DEVICE_REMOTE_WAKEUP ; 
 TYPE_2__ fw ; 
 int /*<<< orphan*/  usb_enable_remote_wakeup () ; 
 int /*<<< orphan*/  usb_pta_init () ; 

void usb_init(void)
{
	usb_pta_init();

	fw.usb.config = 1;
	/*
	 * The fw structure is always initialized with "0"
	 * during boot(); No need to waste precious bytes here.
	 *
	 * fw.usb.interface_setting = 0;
	 * fw.usb.alternate_interface_setting = 0;
	 * fw.usb.device_feature = 0;
	 */

#ifdef CONFIG_CARL9170FW_WOL
	fw.usb.device_feature |= USB_DEVICE_REMOTE_WAKEUP;
	usb_enable_remote_wakeup();
#endif /* CONFIG_CARL9170FW_WOL */
}