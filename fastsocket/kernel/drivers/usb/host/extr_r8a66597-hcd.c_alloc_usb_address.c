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
typedef  int u8 ;
struct urb {TYPE_1__* dev; } ;
struct r8a66597_device {scalar_t__ state; int address; } ;
struct r8a66597 {int address_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  devpath; } ;

/* Variables and functions */
 int R8A66597_MAX_DEVICE ; 
 scalar_t__ USB_STATE_ADDRESS ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct r8a66597_device* get_urb_to_r8a66597_dev (struct r8a66597*,struct urb*) ; 
 scalar_t__ is_hub_limit (int /*<<< orphan*/ ) ; 
 scalar_t__ make_r8a66597_device (struct r8a66597*,struct urb*,int) ; 

__attribute__((used)) static u8 alloc_usb_address(struct r8a66597 *r8a66597, struct urb *urb)
{
	u8 addr;	/* R8A66597's address */
	struct r8a66597_device *dev;

	if (is_hub_limit(urb->dev->devpath)) {
		dev_err(&urb->dev->dev, "External hub limit reached.\n");
		return 0;
	}

	dev = get_urb_to_r8a66597_dev(r8a66597, urb);
	if (dev && dev->state >= USB_STATE_ADDRESS)
		return dev->address;

	for (addr = 1; addr <= R8A66597_MAX_DEVICE; addr++) {
		if (r8a66597->address_map & (1 << addr))
			continue;

		dbg("alloc_address: r8a66597_addr=%d", addr);
		r8a66597->address_map |= 1 << addr;

		if (make_r8a66597_device(r8a66597, urb, addr) < 0)
			return 0;

		return addr;
	}

	dev_err(&urb->dev->dev,
		"cannot communicate with a USB device more than 10.(%x)\n",
		r8a66597->address_map);

	return 0;
}