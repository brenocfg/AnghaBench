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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct amradio_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMRADIO_START ; 
 int amradio_set_mute (struct amradio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct amradio_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int usb_amradio_resume(struct usb_interface *intf)
{
	struct amradio_device *radio = usb_get_intfdata(intf);
	int retval;

	retval = amradio_set_mute(radio, AMRADIO_START);
	if (retval < 0)
		dev_warn(&intf->dev, "amradio_start failed\n");

	dev_info(&intf->dev, "coming out of suspend..\n");

	return 0;
}