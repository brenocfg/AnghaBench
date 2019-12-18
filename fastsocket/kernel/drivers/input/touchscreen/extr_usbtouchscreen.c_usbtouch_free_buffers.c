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
struct usbtouch_usb {int /*<<< orphan*/  buffer; int /*<<< orphan*/  data_dma; int /*<<< orphan*/  data; TYPE_1__* type; } ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rept_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_buffer_free (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbtouch_free_buffers(struct usb_device *udev,
				  struct usbtouch_usb *usbtouch)
{
	usb_buffer_free(udev, usbtouch->type->rept_size,
	                usbtouch->data, usbtouch->data_dma);
	kfree(usbtouch->buffer);
}