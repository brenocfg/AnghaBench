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
typedef  int u8 ;
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  USB_WRITE_REMOTE ; 
 int /*<<< orphan*/  USB_WRITE_REMOTE_TYPE ; 
 int /*<<< orphan*/  adapter_nr ; 
 int /*<<< orphan*/  digitv_ctrl_msg (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  digitv_properties ; 
 int dvb_usb_device_init (struct usb_interface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dvb_usb_device**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int digitv_probe(struct usb_interface *intf,
		const struct usb_device_id *id)
{
	struct dvb_usb_device *d;
	int ret = dvb_usb_device_init(intf, &digitv_properties, THIS_MODULE, &d,
				      adapter_nr);
	if (ret == 0) {
		u8 b[4] = { 0 };

		if (d != NULL) { /* do that only when the firmware is loaded */
			b[0] = 1;
			digitv_ctrl_msg(d,USB_WRITE_REMOTE_TYPE,0,b,4,NULL,0);

			b[0] = 0;
			digitv_ctrl_msg(d,USB_WRITE_REMOTE,0,b,4,NULL,0);
		}
	}
	return ret;
}