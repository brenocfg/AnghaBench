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
 int BM_APBH_CTRL0_CLKGATE ; 
 int BM_APBH_CTRL0_SFTRST ; 
 int BM_APBX_CTRL0_CLKGATE ; 
 int BM_APBX_CTRL0_SFTRST ; 
 scalar_t__ HW_APBH_CTRL0 ; 
 scalar_t__ HW_APBX_CTRL0 ; 
 scalar_t__ REGS_APBH_BASE ; 
 scalar_t__ REGS_APBX_BASE ; 
 int /*<<< orphan*/  stmp3xxx_clearl (int,scalar_t__) ; 

void stmp3xxx_dma_resume(void)
{
	stmp3xxx_clearl(BM_APBH_CTRL0_CLKGATE | BM_APBH_CTRL0_SFTRST,
			REGS_APBH_BASE + HW_APBH_CTRL0);
	stmp3xxx_clearl(BM_APBX_CTRL0_CLKGATE | BM_APBX_CTRL0_SFTRST,
			REGS_APBX_BASE + HW_APBX_CTRL0);
}