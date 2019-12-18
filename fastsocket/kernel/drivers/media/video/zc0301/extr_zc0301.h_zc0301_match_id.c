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
struct zc0301_device {int /*<<< orphan*/  usbdev; } ;
struct usb_device_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_ifnum_to_if (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_match_id (int /*<<< orphan*/ ,struct usb_device_id const*) ; 

struct zc0301_device*
zc0301_match_id(struct zc0301_device* cam, const struct usb_device_id *id)
{
	return usb_match_id(usb_ifnum_to_if(cam->usbdev, 0), id) ? cam : NULL;
}