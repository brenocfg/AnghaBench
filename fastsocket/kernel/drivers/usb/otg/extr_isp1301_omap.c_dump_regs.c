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
typedef  int /*<<< orphan*/  u8 ;
struct isp1301 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP1301_INTERRUPT_SOURCE ; 
 int /*<<< orphan*/  ISP1301_OTG_CONTROL_1 ; 
 int /*<<< orphan*/  ISP1301_OTG_STATUS ; 
 int /*<<< orphan*/  OTG_CTRL ; 
 int /*<<< orphan*/  isp1301_get_u8 (struct isp1301*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_name (struct isp1301*) ; 

__attribute__((used)) static void
dump_regs(struct isp1301 *isp, const char *label)
{
#ifdef	DEBUG
	u8	ctrl = isp1301_get_u8(isp, ISP1301_OTG_CONTROL_1);
	u8	status = isp1301_get_u8(isp, ISP1301_OTG_STATUS);
	u8	src = isp1301_get_u8(isp, ISP1301_INTERRUPT_SOURCE);

	pr_debug("otg: %06x, %s %s, otg/%02x stat/%02x.%02x\n",
		omap_readl(OTG_CTRL), label, state_name(isp),
		ctrl, status, src);
	/* mode control and irq enables don't change much */
#endif
}