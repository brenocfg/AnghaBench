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
struct usb_gadget {int dummy; } ;
struct at91_udc {int /*<<< orphan*/  clocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_UDP_FRM_NUM ; 
 int AT91_UDP_NUM ; 
 int EINVAL ; 
 int at91_udp_read (struct at91_udc*,int /*<<< orphan*/ ) ; 
 struct at91_udc* to_udc (struct usb_gadget*) ; 

__attribute__((used)) static int at91_get_frame(struct usb_gadget *gadget)
{
	struct at91_udc *udc = to_udc(gadget);

	if (!to_udc(gadget)->clocked)
		return -EINVAL;
	return at91_udp_read(udc, AT91_UDP_FRM_NUM) & AT91_UDP_NUM;
}