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
struct wdm_device {struct wdm_device* ubuf; struct wdm_device* irq; struct wdm_device* orq; TYPE_1__* response; int /*<<< orphan*/  inbuf; int /*<<< orphan*/  wMaxCommand; int /*<<< orphan*/  intf; TYPE_2__* validity; int /*<<< orphan*/  sbuf; int /*<<< orphan*/  wMaxPacketSize; } ;
struct TYPE_4__ {int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  transfer_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_urbs (struct wdm_device*) ; 
 int /*<<< orphan*/  interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct wdm_device*) ; 
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup(struct wdm_device *desc)
{
	usb_buffer_free(interface_to_usbdev(desc->intf),
			desc->wMaxPacketSize,
			desc->sbuf,
			desc->validity->transfer_dma);
	usb_buffer_free(interface_to_usbdev(desc->intf),
			desc->wMaxCommand,
			desc->inbuf,
			desc->response->transfer_dma);
	kfree(desc->orq);
	kfree(desc->irq);
	kfree(desc->ubuf);
	free_urbs(desc);
	kfree(desc);
}