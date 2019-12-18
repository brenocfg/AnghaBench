#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_1__ descriptor; } ;
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int USB_TYPE_CLASS ; 
 int USB_TYPE_MASK ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

void snd_usb_ctl_msg_quirk(struct usb_device *dev, unsigned int pipe,
			   __u8 request, __u8 requesttype, __u16 value,
			   __u16 index, void *data, __u16 size)
{
	/*
	 * "Playback Design" products need a 20ms delay after each
	 * class compliant request
	 */
	if ((le16_to_cpu(dev->descriptor.idVendor) == 0x23ba) &&
	    (requesttype & USB_TYPE_MASK) == USB_TYPE_CLASS)
		mdelay(20);
}