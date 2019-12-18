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

/* Variables and functions */
 int /*<<< orphan*/  err (char*,int) ; 
 int libusb_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libusb_set_debug (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_ctx ; 

int usb_init(void)
{
	int ret;

	ret = libusb_init(&usb_ctx);
	if (ret != 0) {
		err("failed to initialize usb subsystem (%d)\n", ret);
		return ret;
	}

	/* like a silent chatterbox! */
	libusb_set_debug(usb_ctx, 2);

	return 0;
}