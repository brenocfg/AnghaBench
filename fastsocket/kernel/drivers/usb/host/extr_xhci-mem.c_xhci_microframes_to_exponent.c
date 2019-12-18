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
struct TYPE_2__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_host_endpoint {TYPE_1__ desc; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int clamp_val (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int fls (unsigned int) ; 

__attribute__((used)) static unsigned int xhci_microframes_to_exponent(struct usb_device *udev,
		struct usb_host_endpoint *ep, unsigned int desc_interval,
		unsigned int min_exponent, unsigned int max_exponent)
{
	unsigned int interval;

	interval = fls(desc_interval) - 1;
	interval = clamp_val(interval, min_exponent, max_exponent);
	if ((1 << interval) != desc_interval)
		dev_warn(&udev->dev,
			 "ep %#x - rounding interval to %d microframes, ep desc says %d microframes\n",
			 ep->desc.bEndpointAddress,
			 1 << interval,
			 desc_interval);

	return interval;
}