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
struct TYPE_2__ {int m_type; int base_cs; int fast_dll_ctrl; int slow_dll_ctrl; int /*<<< orphan*/  dll_mode; } ;

/* Variables and functions */
 int M_DDR ; 
 int /*<<< orphan*/  M_LOCK ; 
 int M_LOCK_CTRL ; 
 int /*<<< orphan*/  M_UNLOCK ; 
 int /*<<< orphan*/  SDRC_DLLA_CTRL ; 
 int /*<<< orphan*/  SDRC_DLLA_STATUS ; 
 int /*<<< orphan*/  SDRC_DLLB_CTRL ; 
 int /*<<< orphan*/  SDRC_DLLB_STATUS ; 
 int /*<<< orphan*/  SDRC_MR_0 ; 
 scalar_t__ cpu_is_omap2422 () ; 
 TYPE_1__ mem_timings ; 
 int /*<<< orphan*/  omap2_sram_ddr_init (int*,int,int,int) ; 
 int sdrc_read_reg (int /*<<< orphan*/ ) ; 

void omap2xxx_sdrc_init_params(u32 force_lock_to_unlock_mode)
{
	unsigned long dll_cnt;
	u32 fast_dll = 0;

	/* DDR = 1, SDR = 0 */
	mem_timings.m_type = !((sdrc_read_reg(SDRC_MR_0) & 0x3) == 0x1);

	/* 2422 es2.05 and beyond has a single SIP DDR instead of 2 like others.
	 * In the case of 2422, its ok to use CS1 instead of CS0.
	 */
	if (cpu_is_omap2422())
		mem_timings.base_cs = 1;
	else
		mem_timings.base_cs = 0;

	if (mem_timings.m_type != M_DDR)
		return;

	/* With DDR we need to determine the low frequency DLL value */
	if (((mem_timings.fast_dll_ctrl & (1 << 2)) == M_LOCK_CTRL))
		mem_timings.dll_mode = M_UNLOCK;
	else
		mem_timings.dll_mode = M_LOCK;

	if (mem_timings.base_cs == 0) {
		fast_dll = sdrc_read_reg(SDRC_DLLA_CTRL);
		dll_cnt = sdrc_read_reg(SDRC_DLLA_STATUS) & 0xff00;
	} else {
		fast_dll = sdrc_read_reg(SDRC_DLLB_CTRL);
		dll_cnt = sdrc_read_reg(SDRC_DLLB_STATUS) & 0xff00;
	}
	if (force_lock_to_unlock_mode) {
		fast_dll &= ~0xff00;
		fast_dll |= dll_cnt;		/* Current lock mode */
	}
	/* set fast timings with DLL filter disabled */
	mem_timings.fast_dll_ctrl = (fast_dll | (3 << 8));

	/* No disruptions, DDR will be offline & C-ABI not followed */
	omap2_sram_ddr_init(&mem_timings.slow_dll_ctrl,
			    mem_timings.fast_dll_ctrl,
			    mem_timings.base_cs,
			    force_lock_to_unlock_mode);
	mem_timings.slow_dll_ctrl &= 0xff00;	/* Keep lock value */

	/* Turn status into unlock ctrl */
	mem_timings.slow_dll_ctrl |=
		((mem_timings.fast_dll_ctrl & 0xF) | (1 << 2));

	/* 90 degree phase for anything below 133Mhz + disable DLL filter */
	mem_timings.slow_dll_ctrl |= ((1 << 1) | (3 << 8));
}