#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int maxpacket; } ;
struct dummy_ep {TYPE_3__* desc; TYPE_1__ ep; } ;
struct TYPE_5__ {scalar_t__ speed; } ;
struct dummy {TYPE_2__ gadget; } ;
struct TYPE_6__ {int /*<<< orphan*/  wMaxPacketSize; } ;

/* Variables and functions */
 scalar_t__ USB_SPEED_HIGH ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int periodic_bytes (struct dummy *dum, struct dummy_ep *ep)
{
	int	limit = ep->ep.maxpacket;

	if (dum->gadget.speed == USB_SPEED_HIGH) {
		int	tmp;

		/* high bandwidth mode */
		tmp = le16_to_cpu(ep->desc->wMaxPacketSize);
		tmp = (tmp >> 11) & 0x03;
		tmp *= 8 /* applies to entire frame */;
		limit += limit * tmp;
	}
	return limit;
}