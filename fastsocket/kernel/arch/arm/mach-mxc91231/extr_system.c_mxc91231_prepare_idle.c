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

/* Variables and functions */
 int /*<<< orphan*/  MXC_DSM_CRM_CONTROL ; 
 int MXC_DSM_CRM_CTRL_LPMD0 ; 
 int MXC_DSM_CRM_CTRL_LPMD1 ; 
 int MXC_DSM_CRM_CTRL_LPMD_WAIT_MODE ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 

void mxc91231_prepare_idle(void)
{
	u32 crm_ctl;

	/* Go to WAIT mode after WFI */
	crm_ctl = __raw_readl(MXC_DSM_CRM_CONTROL);
	crm_ctl &= ~(MXC_DSM_CRM_CTRL_LPMD0 | MXC_DSM_CRM_CTRL_LPMD1);
	crm_ctl |=  MXC_DSM_CRM_CTRL_LPMD_WAIT_MODE;
	__raw_writel(crm_ctl, MXC_DSM_CRM_CONTROL);
}