#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_complete_t ;
struct TYPE_5__ {scalar_t__ hcpriv; int /*<<< orphan*/  transfer_flags; } ;
typedef  TYPE_1__ urb_t ;
typedef  scalar_t__ u32_t ;
typedef  scalar_t__ u16_t ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  URB_ZERO_PACKET ; 
 scalar_t__ USB_DIR_OUT ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_1__*,struct usb_device*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,scalar_t__) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,scalar_t__) ; 
 scalar_t__ usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

u32_t zfLnxUsbSubmitBulkUrb(urb_t *urb, struct usb_device *usb, u16_t epnum, u16_t direction,
        void *transfer_buffer, int buffer_length, usb_complete_t complete, void *context)
{
    u32_t ret;

    if(direction == USB_DIR_OUT)
    {
        usb_fill_bulk_urb(urb, usb, usb_sndbulkpipe(usb, epnum),
                transfer_buffer, buffer_length, complete, context);

        urb->transfer_flags |= URB_ZERO_PACKET;
    }
    else
    {
        usb_fill_bulk_urb(urb, usb, usb_rcvbulkpipe(usb, epnum),
                transfer_buffer, buffer_length, complete, context);
    }

    if (epnum == 4)
    {
        if (urb->hcpriv)
        {
            //printk("CWY - urb->hcpriv set by unknown reason, reset it\n");
            //urb->hcpriv = 0;
        }
    }

    ret = usb_submit_urb(urb, GFP_ATOMIC);
    if ((epnum == 4) & (ret != 0))
    {
        //printk("CWY - ret = %x\n", ret);
    }
    return ret;
}