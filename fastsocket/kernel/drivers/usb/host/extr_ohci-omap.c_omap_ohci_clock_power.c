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
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usb_dc_ck ; 
 int /*<<< orphan*/  usb_host_ck ; 

__attribute__((used)) static void omap_ohci_clock_power(int on)
{
	if (on) {
		clk_enable(usb_dc_ck);
		clk_enable(usb_host_ck);
		/* guesstimate for T5 == 1x 32K clock + APLL lock time */
		udelay(100);
	} else {
		clk_disable(usb_host_ck);
		clk_disable(usb_dc_ck);
	}
}