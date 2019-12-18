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
typedef  int /*<<< orphan*/  usb_complete_t ;
typedef  int /*<<< orphan*/  urb_t ;
typedef  int /*<<< orphan*/  u32_t ;
typedef  scalar_t__ u16_t ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ USB_DIR_OUT ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ *,struct usb_device*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,scalar_t__) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,scalar_t__) ; 
 int /*<<< orphan*/  usb_submit_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u32_t zfLnxUsbSubmitIntUrb(urb_t *urb, struct usb_device *usb, u16_t epnum, u16_t direction,
        void *transfer_buffer, int buffer_length, usb_complete_t complete, void *context,
        u32_t interval)
{
    u32_t ret;

    if(direction == USB_DIR_OUT)
    {
        usb_fill_int_urb(urb, usb, usb_sndbulkpipe(usb, epnum),
                transfer_buffer, buffer_length, complete, context, interval);
    }
    else
    {
        usb_fill_int_urb(urb, usb, usb_rcvbulkpipe(usb, epnum),
                transfer_buffer, buffer_length, complete, context, interval);
    }

    ret = usb_submit_urb(urb, GFP_ATOMIC);

    return ret;
}