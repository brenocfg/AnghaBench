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
struct usb_gadget {int dummy; } ;
struct musb {TYPE_1__* xceiv; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_power; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct musb* gadget_to_musb (struct usb_gadget*) ; 
 int otg_set_power (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static int musb_gadget_vbus_draw(struct usb_gadget *gadget, unsigned mA)
{
	struct musb	*musb = gadget_to_musb(gadget);

	if (!musb->xceiv->set_power)
		return -EOPNOTSUPP;
	return otg_set_power(musb->xceiv, mA);
}