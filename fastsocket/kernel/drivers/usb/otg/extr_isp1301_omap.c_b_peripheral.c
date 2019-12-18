#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/  gadget; } ;
struct isp1301 {TYPE_1__ otg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP1301_OTG_CONTROL_1 ; 
 int /*<<< orphan*/  OTG1_DP_PULLDOWN ; 
 int /*<<< orphan*/  OTG1_DP_PULLUP ; 
 int /*<<< orphan*/  OTG_CTRL ; 
 int /*<<< orphan*/  OTG_STATE_B_PERIPHERAL ; 
 int OTG_XCEIV_OUTPUTS ; 
 int /*<<< orphan*/  dump_regs (struct isp1301*,char*) ; 
 int /*<<< orphan*/  enable_vbus_draw (struct isp1301*,int) ; 
 int /*<<< orphan*/  isp1301_clear_bits (struct isp1301*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp1301_set_bits (struct isp1301*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int omap_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  otg_update_isp (struct isp1301*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  usb_gadget_vbus_connect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b_peripheral(struct isp1301 *isp)
{
	u32 l;

	l = omap_readl(OTG_CTRL) & OTG_XCEIV_OUTPUTS;
	omap_writel(l, OTG_CTRL);

	usb_gadget_vbus_connect(isp->otg.gadget);

#ifdef	CONFIG_USB_OTG
	enable_vbus_draw(isp, 8);
	otg_update_isp(isp);
#else
	enable_vbus_draw(isp, 100);
	/* UDC driver just set OTG_BSESSVLD */
	isp1301_set_bits(isp, ISP1301_OTG_CONTROL_1, OTG1_DP_PULLUP);
	isp1301_clear_bits(isp, ISP1301_OTG_CONTROL_1, OTG1_DP_PULLDOWN);
	isp->otg.state = OTG_STATE_B_PERIPHERAL;
	pr_debug("  --> b_peripheral\n");
	dump_regs(isp, "2periph");
#endif
}