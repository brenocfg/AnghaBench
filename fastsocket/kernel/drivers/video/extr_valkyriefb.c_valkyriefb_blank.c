#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct valkyrie_regvals {int mode; } ;
struct fb_par_valkyrie {struct valkyrie_regvals* init; } ;
struct fb_info_valkyrie {TYPE_2__* valkyrie_regs; } ;
struct fb_info {struct fb_par_valkyrie* par; } ;
struct TYPE_3__ {int /*<<< orphan*/  r; } ;
struct TYPE_4__ {TYPE_1__ mode; } ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int valkyriefb_blank(int blank_mode, struct fb_info *info)
{
	struct fb_info_valkyrie *p = (struct fb_info_valkyrie *) info;
	struct fb_par_valkyrie *par = info->par;
	struct valkyrie_regvals	*init = par->init;

	if (init == NULL)
		return 1;

	switch (blank_mode) {
	case FB_BLANK_UNBLANK:			/* unblank */
		out_8(&p->valkyrie_regs->mode.r, init->mode);
		break;
	case FB_BLANK_NORMAL:
		return 1;	/* get caller to set CLUT to all black */
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
		/*
		 * [kps] Value extracted from MacOS. I don't know
		 * whether this bit disables hsync or vsync, or
		 * whether the hardware can do the other as well.
		 */
		out_8(&p->valkyrie_regs->mode.r, init->mode | 0x40);
		break;
	case FB_BLANK_POWERDOWN:
		out_8(&p->valkyrie_regs->mode.r, 0x66);
		break;
	}
	return 0;
}