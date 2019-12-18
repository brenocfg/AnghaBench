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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * endptctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPCTRL_RX_DATA_TOGGLE_RST ; 
 int /*<<< orphan*/  EPCTRL_RX_EP_STALL ; 
 int /*<<< orphan*/  EPCTRL_TX_DATA_TOGGLE_RST ; 
 int /*<<< orphan*/  EPCTRL_TX_EP_STALL ; 
 TYPE_1__* dr_regs ; 
 int /*<<< orphan*/  fsl_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dr_ep_change_stall(unsigned char ep_num, unsigned char dir, int value)
{
	u32 tmp_epctrl = 0;

	tmp_epctrl = fsl_readl(&dr_regs->endptctrl[ep_num]);

	if (value) {
		/* set the stall bit */
		if (dir)
			tmp_epctrl |= EPCTRL_TX_EP_STALL;
		else
			tmp_epctrl |= EPCTRL_RX_EP_STALL;
	} else {
		/* clear the stall bit and reset data toggle */
		if (dir) {
			tmp_epctrl &= ~EPCTRL_TX_EP_STALL;
			tmp_epctrl |= EPCTRL_TX_DATA_TOGGLE_RST;
		} else {
			tmp_epctrl &= ~EPCTRL_RX_EP_STALL;
			tmp_epctrl |= EPCTRL_RX_DATA_TOGGLE_RST;
		}
	}
	fsl_writel(tmp_epctrl, &dr_regs->endptctrl[ep_num]);
}