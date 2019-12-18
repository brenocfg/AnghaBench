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
struct clk {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXC_CCM_PDR1_USB_PODF_MASK ; 
 int /*<<< orphan*/  MXC_CCM_PDR1_USB_PODF_OFFSET ; 
 int /*<<< orphan*/  MXC_CCM_PDR1_USB_PRDF_MASK ; 
 int /*<<< orphan*/  MXC_CCM_PDR1_USB_PRDF_OFFSET ; 
 unsigned long PDR1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long usb_get_rate(struct clk *clk)
{
	unsigned long usb_pdf, usb_prepdf;

	usb_pdf = PDR1(MXC_CCM_PDR1_USB_PODF_MASK,
		       MXC_CCM_PDR1_USB_PODF_OFFSET);
	usb_prepdf = PDR1(MXC_CCM_PDR1_USB_PRDF_MASK,
			  MXC_CCM_PDR1_USB_PRDF_OFFSET);
	return clk_get_rate(clk->parent) / (usb_prepdf + 1) / (usb_pdf + 1);
}