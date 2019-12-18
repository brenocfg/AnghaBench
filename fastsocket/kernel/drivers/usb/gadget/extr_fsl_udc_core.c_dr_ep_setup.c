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
struct TYPE_2__ {int /*<<< orphan*/ * endptctrl; } ;

/* Variables and functions */
 unsigned int EPCTRL_RX_DATA_TOGGLE_RST ; 
 unsigned int EPCTRL_RX_ENABLE ; 
 unsigned int EPCTRL_RX_EP_TYPE_SHIFT ; 
 unsigned int EPCTRL_TX_DATA_TOGGLE_RST ; 
 unsigned int EPCTRL_TX_ENABLE ; 
 unsigned int EPCTRL_TX_EP_TYPE_SHIFT ; 
 TYPE_1__* dr_regs ; 
 unsigned int fsl_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_writel (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dr_ep_setup(unsigned char ep_num, unsigned char dir,
			unsigned char ep_type)
{
	unsigned int tmp_epctrl = 0;

	tmp_epctrl = fsl_readl(&dr_regs->endptctrl[ep_num]);
	if (dir) {
		if (ep_num)
			tmp_epctrl |= EPCTRL_TX_DATA_TOGGLE_RST;
		tmp_epctrl |= EPCTRL_TX_ENABLE;
		tmp_epctrl |= ((unsigned int)(ep_type)
				<< EPCTRL_TX_EP_TYPE_SHIFT);
	} else {
		if (ep_num)
			tmp_epctrl |= EPCTRL_RX_DATA_TOGGLE_RST;
		tmp_epctrl |= EPCTRL_RX_ENABLE;
		tmp_epctrl |= ((unsigned int)(ep_type)
				<< EPCTRL_RX_EP_TYPE_SHIFT);
	}

	fsl_writel(tmp_epctrl, &dr_regs->endptctrl[ep_num]);
}