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
struct usb_device_id {int /*<<< orphan*/  member_0; } ;
struct et61x251_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  USB_DEVICE (int,int) ; 
 int /*<<< orphan*/  et61x251_attach_sensor (struct et61x251_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  et61x251_match_id (struct et61x251_device*,struct usb_device_id const*) ; 
 int /*<<< orphan*/  tas5130d1b ; 

int et61x251_probe_tas5130d1b(struct et61x251_device* cam)
{
	const struct usb_device_id tas5130d1b_id_table[] = {
		{ USB_DEVICE(0x102c, 0x6251), },
		{ }
	};

	/* Sensor detection is based on USB pid/vid */
	if (!et61x251_match_id(cam, tas5130d1b_id_table))
		return -ENODEV;

	et61x251_attach_sensor(cam, &tas5130d1b);

	return 0;
}