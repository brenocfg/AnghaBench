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
struct TYPE_2__ {int /*<<< orphan*/ * endptctrl; } ;

/* Variables and functions */
 int EPCTRL_RX_EP_STALL ; 
 int EPCTRL_TX_EP_STALL ; 
 TYPE_1__* dr_regs ; 
 int fsl_readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dr_ep_get_stall(unsigned char ep_num, unsigned char dir)
{
	u32 epctrl;

	epctrl = fsl_readl(&dr_regs->endptctrl[ep_num]);
	if (dir)
		return (epctrl & EPCTRL_TX_EP_STALL) ? 1 : 0;
	else
		return (epctrl & EPCTRL_RX_EP_STALL) ? 1 : 0;
}