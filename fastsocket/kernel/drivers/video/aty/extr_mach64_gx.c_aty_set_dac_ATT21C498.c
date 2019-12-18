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
struct TYPE_2__ {int period_in_ps; } ;
union aty_pll {TYPE_1__ ics2595; } ;
typedef  int u32 ;
struct fb_info {scalar_t__ par; } ;
struct atyfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_CNTL ; 
 int /*<<< orphan*/  DAC_CNTL ; 
 scalar_t__ DAC_REGS ; 
 int /*<<< orphan*/  aty_dac_waste4 (struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_8 (scalar_t__,int,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 

__attribute__((used)) static int aty_set_dac_ATT21C498(const struct fb_info *info,
				 const union aty_pll *pll, u32 bpp,
				 u32 accel)
{
	struct atyfb_par *par = (struct atyfb_par *) info->par;
	u32 dotClock;
	int muxmode = 0;
	int DACMask = 0;

	dotClock = 100000000 / pll->ics2595.period_in_ps;

	switch (bpp) {
	case 8:
		if (dotClock > 8000) {
			DACMask = 0x24;
			muxmode = 1;
		} else
			DACMask = 0x04;
		break;
	case 15:
		DACMask = 0x16;
		break;
	case 16:
		DACMask = 0x36;
		break;
	case 24:
		DACMask = 0xE6;
		break;
	case 32:
		DACMask = 0xE6;
		break;
	}

	if (1 /* info->mach64DAC8Bit */ )
		DACMask |= 0x02;

	aty_dac_waste4(par);
	aty_st_8(DAC_REGS + 2, DACMask, par);

	aty_st_le32(BUS_CNTL, 0x890e20f1, par);
	aty_st_le32(DAC_CNTL, 0x00072000, par);
	return muxmode;
}