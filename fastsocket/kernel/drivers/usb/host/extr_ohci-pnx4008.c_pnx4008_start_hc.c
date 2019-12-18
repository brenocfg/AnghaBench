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
 unsigned long HOST_EN ; 
 int /*<<< orphan*/  USB_OTG_STAT_CONTROL ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp1301_vbus_on () ; 

__attribute__((used)) static void pnx4008_start_hc(void)
{
	unsigned long tmp = __raw_readl(USB_OTG_STAT_CONTROL) | HOST_EN;
	__raw_writel(tmp, USB_OTG_STAT_CONTROL);
	isp1301_vbus_on();
}