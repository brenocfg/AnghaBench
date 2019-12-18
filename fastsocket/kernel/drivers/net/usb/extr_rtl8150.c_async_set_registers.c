#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {void* wLength; scalar_t__ wIndex; void* wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bRequestType; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  netdev; TYPE_3__* ctrl_urb; int /*<<< orphan*/  rx_creg; TYPE_1__ dr; int /*<<< orphan*/  udev; } ;
typedef  TYPE_2__ rtl8150_t ;
struct TYPE_9__ {int /*<<< orphan*/  transfer_buffer_length; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RTL8150_REQT_WRITE ; 
 int /*<<< orphan*/  RTL8150_REQ_SET_REGS ; 
 int /*<<< orphan*/  RX_REG_SET ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_callback ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_control_urb (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int async_set_registers(rtl8150_t * dev, u16 indx, u16 size)
{
	int ret;

	if (test_bit(RX_REG_SET, &dev->flags))
		return -EAGAIN;

	dev->dr.bRequestType = RTL8150_REQT_WRITE;
	dev->dr.bRequest = RTL8150_REQ_SET_REGS;
	dev->dr.wValue = cpu_to_le16(indx);
	dev->dr.wIndex = 0;
	dev->dr.wLength = cpu_to_le16(size);
	dev->ctrl_urb->transfer_buffer_length = size;
	usb_fill_control_urb(dev->ctrl_urb, dev->udev,
			 usb_sndctrlpipe(dev->udev, 0), (char *) &dev->dr,
			 &dev->rx_creg, size, ctrl_callback, dev);
	if ((ret = usb_submit_urb(dev->ctrl_urb, GFP_ATOMIC))) {
		if (ret == -ENODEV)
			netif_device_detach(dev->netdev);
		err("control request submission failed: %d", ret);
	} else
		set_bit(RX_REG_SET, &dev->flags);

	return ret;
}