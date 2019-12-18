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
struct usba_udc {int dummy; } ;
struct usb_gadget {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FNUM ; 
 int /*<<< orphan*/  FRAME_NUMBER ; 
 int USBA_BFEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usba_udc* to_usba_udc (struct usb_gadget*) ; 
 int /*<<< orphan*/  usba_readl (struct usba_udc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usba_udc_get_frame(struct usb_gadget *gadget)
{
	struct usba_udc *udc = to_usba_udc(gadget);

	return USBA_BFEXT(FRAME_NUMBER, usba_readl(udc, FNUM));
}