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
struct w100fb_par {int blanked; TYPE_1__* mach; } ;
struct w100_tg_info {int /*<<< orphan*/  (* resume ) (struct w100fb_par*) ;int /*<<< orphan*/  (* suspend ) (struct w100fb_par*) ;} ;
struct fb_info {struct w100fb_par* par; } ;
struct TYPE_2__ {struct w100_tg_info* tg; } ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  stub1 (struct w100fb_par*) ; 
 int /*<<< orphan*/  stub2 (struct w100fb_par*) ; 

__attribute__((used)) static int w100fb_blank(int blank_mode, struct fb_info *info)
{
	struct w100fb_par *par = info->par;
	struct w100_tg_info *tg = par->mach->tg;

	switch(blank_mode) {

 	case FB_BLANK_NORMAL:         /* Normal blanking */
	case FB_BLANK_VSYNC_SUSPEND:  /* VESA blank (vsync off) */
	case FB_BLANK_HSYNC_SUSPEND:  /* VESA blank (hsync off) */
 	case FB_BLANK_POWERDOWN:      /* Poweroff */
  		if (par->blanked == 0) {
			if(tg && tg->suspend)
				tg->suspend(par);
			par->blanked = 1;
  		}
  		break;

 	case FB_BLANK_UNBLANK: /* Unblanking */
  		if (par->blanked != 0) {
			if(tg && tg->resume)
				tg->resume(par);
			par->blanked = 0;
  		}
  		break;
 	}
	return 0;
}