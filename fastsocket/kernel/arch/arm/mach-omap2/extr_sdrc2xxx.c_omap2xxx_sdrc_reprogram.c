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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ CORE_CLK_SRC_DPLL ; 
 scalar_t__ CORE_CLK_SRC_DPLL_X2 ; 
 int /*<<< orphan*/  OMAP2420_PRCM_VOLTSETUP ; 
 int /*<<< orphan*/  OMAP2430_PRCM_VOLTSETUP ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_is_omap2420 () ; 
 scalar_t__ curr_perf_level ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  omap2_sram_reprogram_sdrc (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ omap2xxx_sdrc_get_fast_dll_ctrl () ; 
 scalar_t__ omap2xxx_sdrc_get_slow_dll_ctrl () ; 
 scalar_t__ omap2xxx_sdrc_get_type () ; 

u32 omap2xxx_sdrc_reprogram(u32 level, u32 force)
{
	u32 dll_ctrl, m_type;
	u32 prev = curr_perf_level;
	unsigned long flags;

	if ((curr_perf_level == level) && !force)
		return prev;

	if (level == CORE_CLK_SRC_DPLL)
		dll_ctrl = omap2xxx_sdrc_get_slow_dll_ctrl();
	else if (level == CORE_CLK_SRC_DPLL_X2)
		dll_ctrl = omap2xxx_sdrc_get_fast_dll_ctrl();
	else
		return prev;

	m_type = omap2xxx_sdrc_get_type();

	local_irq_save(flags);
	if (cpu_is_omap2420())
		__raw_writel(0xffff, OMAP2420_PRCM_VOLTSETUP);
	else
		__raw_writel(0xffff, OMAP2430_PRCM_VOLTSETUP);
	omap2_sram_reprogram_sdrc(level, dll_ctrl, m_type);
	curr_perf_level = level;
	local_irq_restore(flags);

	return prev;
}