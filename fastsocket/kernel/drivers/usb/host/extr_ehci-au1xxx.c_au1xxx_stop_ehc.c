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
 unsigned long USBH_DISABLE ; 
 int /*<<< orphan*/  USB_HOST_CONFIG ; 
 unsigned long USB_MCFG_EHCCLKEN ; 
 unsigned long USB_MCFG_PHYPLLEN ; 
 unsigned long USB_MCFG_UCECLKEN ; 
 unsigned long au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void au1xxx_stop_ehc(void)
{
	unsigned long c;

	/* Disable mem */
	au_writel(au_readl(USB_HOST_CONFIG) & ~USBH_DISABLE, USB_HOST_CONFIG);
	au_sync();
	udelay(1000);

	/* Disable EHC clock. If the HS PHY is unused disable it too. */
	c = au_readl(USB_HOST_CONFIG) & ~USB_MCFG_EHCCLKEN;
	if (!(c & USB_MCFG_UCECLKEN))		/* UDC disabled? */
		c &= ~USB_MCFG_PHYPLLEN;	/* yes: disable HS PHY PLL */
	au_writel(c, USB_HOST_CONFIG);
	au_sync();
}