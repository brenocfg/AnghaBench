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
typedef  int u32 ;
struct fb_info {scalar_t__ par; } ;
struct atyfb_par {int dummy; } ;

/* Variables and functions */
 int CRTC_EXT_DISP_EN ; 
 scalar_t__ CRTC_GEN_CNTL ; 
 scalar_t__ DAC_CNTL ; 
 char DAC_EXT_SEL_RS2 ; 
 char DAC_EXT_SEL_RS3 ; 
 scalar_t__ DAC_REGS ; 
 char aty_ld_8 (scalar_t__,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_8 (scalar_t__,char,struct atyfb_par*) ; 

__attribute__((used)) static void aty_set_pll_8398(const struct fb_info *info,
			     const union aty_pll *pll)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	u32 program_bits;
	u32 locationAddr;

	char old_crtc_ext_disp;
	char tmp;

	old_crtc_ext_disp = aty_ld_8(CRTC_GEN_CNTL + 3, par);
	aty_st_8(CRTC_GEN_CNTL + 3,
		 old_crtc_ext_disp | (CRTC_EXT_DISP_EN >> 24), par);

	program_bits = pll->ics2595.program_bits;
	locationAddr = pll->ics2595.locationAddr;

	/* Program clock */
	tmp = aty_ld_8(DAC_CNTL, par);
	aty_st_8(DAC_CNTL, tmp | DAC_EXT_SEL_RS2 | DAC_EXT_SEL_RS3, par);

	aty_st_8(DAC_REGS, locationAddr, par);
	aty_st_8(DAC_REGS + 1, (program_bits & 0xff00) >> 8, par);
	aty_st_8(DAC_REGS + 1, (program_bits & 0xff), par);

	tmp = aty_ld_8(DAC_CNTL, par);
	aty_st_8(DAC_CNTL, (tmp & ~DAC_EXT_SEL_RS2) | DAC_EXT_SEL_RS3,
		 par);

	(void) aty_ld_8(DAC_REGS, par);	/* Clear DAC Counter */
	aty_st_8(CRTC_GEN_CNTL + 3, old_crtc_ext_disp, par);

	return;
}