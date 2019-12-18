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
typedef  int u32 ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OXU_ASO ; 
 int OXU_ASO_OP ; 
 int /*<<< orphan*/  OXU_CHIPIRQEN_CLR ; 
 int /*<<< orphan*/  OXU_CHIPIRQEN_SET ; 
 int /*<<< orphan*/  OXU_CHIPIRQSTATUS ; 
 int /*<<< orphan*/  OXU_CLKCTRL_SET ; 
 int OXU_COMPARATOR ; 
 int /*<<< orphan*/  OXU_HOSTIFCONFIG ; 
 int OXU_OVRCCURPUPDEN ; 
 int /*<<< orphan*/  OXU_PIOBURSTREADCTRL ; 
 int /*<<< orphan*/  OXU_SOFTRESET ; 
 int OXU_SPHPOEN ; 
 int OXU_SRESET ; 
 int OXU_SYSCLKEN ; 
 int OXU_USBOTGCLKEN ; 
 int OXU_USBOTGLPWUI ; 
 int OXU_USBSPHLPWUI ; 
 int oxu_readl (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxu_writel (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void oxu_configuration(struct platform_device *pdev, void *base)
{
	u32 tmp;

	/* Initialize top level registers.
	 * First write ever
	 */
	oxu_writel(base, OXU_HOSTIFCONFIG, 0x0000037D);
	oxu_writel(base, OXU_SOFTRESET, OXU_SRESET);
	oxu_writel(base, OXU_HOSTIFCONFIG, 0x0000037D);

	tmp = oxu_readl(base, OXU_PIOBURSTREADCTRL);
	oxu_writel(base, OXU_PIOBURSTREADCTRL, tmp | 0x0040);

	oxu_writel(base, OXU_ASO, OXU_SPHPOEN | OXU_OVRCCURPUPDEN |
					OXU_COMPARATOR | OXU_ASO_OP);

	tmp = oxu_readl(base, OXU_CLKCTRL_SET);
	oxu_writel(base, OXU_CLKCTRL_SET, tmp | OXU_SYSCLKEN | OXU_USBOTGCLKEN);

	/* Clear all top interrupt enable */
	oxu_writel(base, OXU_CHIPIRQEN_CLR, 0xff);

	/* Clear all top interrupt status */
	oxu_writel(base, OXU_CHIPIRQSTATUS, 0xff);

	/* Enable all needed top interrupt except OTG SPH core */
	oxu_writel(base, OXU_CHIPIRQEN_SET, OXU_USBSPHLPWUI | OXU_USBOTGLPWUI);
}