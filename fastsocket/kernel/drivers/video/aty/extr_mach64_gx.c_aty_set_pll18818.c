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
struct TYPE_2__ {int program_bits; int locationAddr; } ;
union aty_pll {TYPE_1__ ics2595; } ;
typedef  int u8 ;
typedef  int u32 ;
struct fb_info {scalar_t__ par; } ;
struct atyfb_par {scalar_t__ clk_wr_offset; } ;

/* Variables and functions */
 scalar_t__ CLOCK_CNTL ; 
 int CLOCK_STROBE ; 
 int CRTC_EXT_DISP_EN ; 
 scalar_t__ CRTC_GEN_CNTL ; 
 scalar_t__ DAC_REGS ; 
 int /*<<< orphan*/  aty_ICS2595_put1bit (int,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_StrobeClock (struct atyfb_par*) ; 
 int aty_ld_8 (scalar_t__,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_8 (scalar_t__,int,struct atyfb_par*) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void aty_set_pll18818(const struct fb_info *info,
			     const union aty_pll *pll)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	u32 program_bits;
	u32 locationAddr;

	u32 i;

	u8 old_clock_cntl;
	u8 old_crtc_ext_disp;

	old_clock_cntl = aty_ld_8(CLOCK_CNTL, par);
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset, 0, par);

	old_crtc_ext_disp = aty_ld_8(CRTC_GEN_CNTL + 3, par);
	aty_st_8(CRTC_GEN_CNTL + 3,
		 old_crtc_ext_disp | (CRTC_EXT_DISP_EN >> 24), par);

	mdelay(15);		/* delay for 50 (15) ms */

	program_bits = pll->ics2595.program_bits;
	locationAddr = pll->ics2595.locationAddr;

	/* Program the clock chip */
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset, 0, par);	/* Strobe = 0 */
	aty_StrobeClock(par);
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset, 1, par);	/* Strobe = 0 */
	aty_StrobeClock(par);

	aty_ICS2595_put1bit(1, par);	/* Send start bits */
	aty_ICS2595_put1bit(0, par);	/* Start bit */
	aty_ICS2595_put1bit(0, par);	/* Read / ~Write */

	for (i = 0; i < 5; i++) {	/* Location 0..4 */
		aty_ICS2595_put1bit(locationAddr & 1, par);
		locationAddr >>= 1;
	}

	for (i = 0; i < 8 + 1 + 2 + 2; i++) {
		aty_ICS2595_put1bit(program_bits & 1, par);
		program_bits >>= 1;
	}

	mdelay(1);		/* delay for 1 ms */

	(void) aty_ld_8(DAC_REGS, par);	/* Clear DAC Counter */
	aty_st_8(CRTC_GEN_CNTL + 3, old_crtc_ext_disp, par);
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset,
		 old_clock_cntl | CLOCK_STROBE, par);

	mdelay(50);		/* delay for 50 (15) ms */
	aty_st_8(CLOCK_CNTL + par->clk_wr_offset,
		 ((pll->ics2595.locationAddr & 0x0F) | CLOCK_STROBE), par);
	return;
}