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

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ gadget_is_amd5536udc (struct usb_gadget*) ; 
 scalar_t__ gadget_is_at91 (struct usb_gadget*) ; 
 scalar_t__ gadget_is_atmel_usba (struct usb_gadget*) ; 
 scalar_t__ gadget_is_ci13xxx (struct usb_gadget*) ; 
 scalar_t__ gadget_is_dummy (struct usb_gadget*) ; 
 scalar_t__ gadget_is_fsl_qe (struct usb_gadget*) ; 
 scalar_t__ gadget_is_fsl_usb2 (struct usb_gadget*) ; 
 scalar_t__ gadget_is_goku (struct usb_gadget*) ; 
 scalar_t__ gadget_is_imx (struct usb_gadget*) ; 
 scalar_t__ gadget_is_langwell (struct usb_gadget*) ; 
 scalar_t__ gadget_is_lh7a40x (struct usb_gadget*) ; 
 scalar_t__ gadget_is_m66592 (struct usb_gadget*) ; 
 scalar_t__ gadget_is_mpc8272 (struct usb_gadget*) ; 
 scalar_t__ gadget_is_mq11xx (struct usb_gadget*) ; 
 scalar_t__ gadget_is_musbhdrc (struct usb_gadget*) ; 
 scalar_t__ gadget_is_musbhsfc (struct usb_gadget*) ; 
 scalar_t__ gadget_is_n9604 (struct usb_gadget*) ; 
 scalar_t__ gadget_is_net2280 (struct usb_gadget*) ; 
 scalar_t__ gadget_is_omap (struct usb_gadget*) ; 
 scalar_t__ gadget_is_pxa (struct usb_gadget*) ; 
 scalar_t__ gadget_is_pxa27x (struct usb_gadget*) ; 
 scalar_t__ gadget_is_r8a66597 (struct usb_gadget*) ; 
 scalar_t__ gadget_is_s3c2410 (struct usb_gadget*) ; 
 scalar_t__ gadget_is_sa1100 (struct usb_gadget*) ; 
 scalar_t__ gadget_is_sh (struct usb_gadget*) ; 

__attribute__((used)) static inline int usb_gadget_controller_number(struct usb_gadget *gadget)
{
	if (gadget_is_net2280(gadget))
		return 0x01;
	else if (gadget_is_dummy(gadget))
		return 0x02;
	else if (gadget_is_pxa(gadget))
		return 0x03;
	else if (gadget_is_sh(gadget))
		return 0x04;
	else if (gadget_is_sa1100(gadget))
		return 0x05;
	else if (gadget_is_goku(gadget))
		return 0x06;
	else if (gadget_is_mq11xx(gadget))
		return 0x07;
	else if (gadget_is_omap(gadget))
		return 0x08;
	else if (gadget_is_lh7a40x(gadget))
		return 0x09;
	else if (gadget_is_n9604(gadget))
		return 0x10;
	else if (gadget_is_pxa27x(gadget))
		return 0x11;
	else if (gadget_is_s3c2410(gadget))
		return 0x12;
	else if (gadget_is_at91(gadget))
		return 0x13;
	else if (gadget_is_imx(gadget))
		return 0x14;
	else if (gadget_is_musbhsfc(gadget))
		return 0x15;
	else if (gadget_is_musbhdrc(gadget))
		return 0x16;
	else if (gadget_is_mpc8272(gadget))
		return 0x17;
	else if (gadget_is_atmel_usba(gadget))
		return 0x18;
	else if (gadget_is_fsl_usb2(gadget))
		return 0x19;
	else if (gadget_is_amd5536udc(gadget))
		return 0x20;
	else if (gadget_is_m66592(gadget))
		return 0x21;
	else if (gadget_is_fsl_qe(gadget))
		return 0x22;
	else if (gadget_is_ci13xxx(gadget))
		return 0x23;
	else if (gadget_is_langwell(gadget))
		return 0x24;
	else if (gadget_is_r8a66597(gadget))
		return 0x25;
	return -ENOENT;
}