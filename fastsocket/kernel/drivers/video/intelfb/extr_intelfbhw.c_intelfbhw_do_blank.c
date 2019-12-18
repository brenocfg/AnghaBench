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
struct intelfb_info {int cursor_on; int cursor_blanked; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADPA ; 
 int ADPA_DPMS_CONTROL_MASK ; 
 int ADPA_DPMS_D0 ; 
 int ADPA_DPMS_D1 ; 
 int ADPA_DPMS_D2 ; 
 int ADPA_DPMS_D3 ; 
 int /*<<< orphan*/  DBG_MSG (char*,int) ; 
 int DISPPLANE_PLANE_ENABLE ; 
 int /*<<< orphan*/  DSPABASE ; 
 int /*<<< orphan*/  DSPACNTR ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 struct intelfb_info* GET_DINFO (struct fb_info*) ; 
 int INREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intelfbhw_cursor_hide (struct intelfb_info*) ; 
 int /*<<< orphan*/  intelfbhw_cursor_show (struct intelfb_info*) ; 

void intelfbhw_do_blank(int blank, struct fb_info *info)
{
	struct intelfb_info *dinfo = GET_DINFO(info);
	u32 tmp;

#if VERBOSE > 0
	DBG_MSG("intelfbhw_do_blank: blank is %d\n", blank);
#endif

	/* Turn plane A on or off */
	tmp = INREG(DSPACNTR);
	if (blank)
		tmp &= ~DISPPLANE_PLANE_ENABLE;
	else
		tmp |= DISPPLANE_PLANE_ENABLE;
	OUTREG(DSPACNTR, tmp);
	/* Flush */
	tmp = INREG(DSPABASE);
	OUTREG(DSPABASE, tmp);

	/* Turn off/on the HW cursor */
#if VERBOSE > 0
	DBG_MSG("cursor_on is %d\n", dinfo->cursor_on);
#endif
	if (dinfo->cursor_on) {
		if (blank)
			intelfbhw_cursor_hide(dinfo);
		else
			intelfbhw_cursor_show(dinfo);
		dinfo->cursor_on = 1;
	}
	dinfo->cursor_blanked = blank;

	/* Set DPMS level */
	tmp = INREG(ADPA) & ~ADPA_DPMS_CONTROL_MASK;
	switch (blank) {
	case FB_BLANK_UNBLANK:
	case FB_BLANK_NORMAL:
		tmp |= ADPA_DPMS_D0;
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		tmp |= ADPA_DPMS_D1;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		tmp |= ADPA_DPMS_D2;
		break;
	case FB_BLANK_POWERDOWN:
		tmp |= ADPA_DPMS_D3;
		break;
	}
	OUTREG(ADPA, tmp);

	return;
}