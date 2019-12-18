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
 int USBH_DISABLE ; 
 int USBH_ENABLE_CE ; 
 int /*<<< orphan*/  USB_HOST_CONFIG ; 
 int au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void au1xxx_stop_ohc(void)
{
#ifdef CONFIG_SOC_AU1200
	/* Disable mem */
	au_writel(au_readl(USB_HOST_CONFIG) & ~USBH_DISABLE, USB_HOST_CONFIG);
	au_sync();
	udelay(1000);
#endif
	/* Disable clock */
	au_writel(au_readl(USB_HOST_CONFIG) & ~USBH_ENABLE_CE, USB_HOST_CONFIG);
	au_sync();
}