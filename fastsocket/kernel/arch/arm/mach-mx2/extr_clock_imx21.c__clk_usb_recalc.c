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
 unsigned long CCM_CSCR_USB_MASK ; 
 unsigned long CCM_CSCR_USB_OFFSET ; 
 unsigned long CSCR () ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long _clk_usb_recalc(struct clk *clk)
{
	unsigned long usb_pdf;
	unsigned long parent_rate;

	parent_rate = clk_get_rate(clk->parent);

	usb_pdf = (CSCR() & CCM_CSCR_USB_MASK) >> CCM_CSCR_USB_OFFSET;

	return parent_rate / (usb_pdf + 1U);
}