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

/* Variables and functions */
 int /*<<< orphan*/  SE_USB_AHB_NEED_CLK_INT ; 
 int /*<<< orphan*/  SE_USB_I2C_INT ; 
 int /*<<< orphan*/  SE_USB_INT ; 
 int /*<<< orphan*/  SE_USB_NEED_CLK_INT ; 
 int /*<<< orphan*/  SE_USB_OTG_ATX_INT_N ; 
 int /*<<< orphan*/  SE_USB_OTG_TIMER_INT ; 
 int /*<<< orphan*/  start_int_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pnx4008_unset_usb_bits(void)
{
	start_int_mask(SE_USB_OTG_ATX_INT_N);
	start_int_mask(SE_USB_OTG_TIMER_INT);
	start_int_mask(SE_USB_I2C_INT);
	start_int_mask(SE_USB_INT);
	start_int_mask(SE_USB_NEED_CLK_INT);
	start_int_mask(SE_USB_AHB_NEED_CLK_INT);
}