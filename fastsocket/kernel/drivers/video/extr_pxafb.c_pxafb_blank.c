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
struct TYPE_3__ {int /*<<< orphan*/  visual; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmap; TYPE_1__ fix; } ;
struct pxafb_info {int palette_size; TYPE_2__ fb; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_DISABLE ; 
 int /*<<< orphan*/  C_ENABLE ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_STATIC_PSEUDOCOLOR ; 
 int /*<<< orphan*/  fb_set_cmap (int /*<<< orphan*/ *,struct fb_info*) ; 
 int /*<<< orphan*/  pxafb_schedule_work (struct pxafb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxafb_setpalettereg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fb_info*) ; 

__attribute__((used)) static int pxafb_blank(int blank, struct fb_info *info)
{
	struct pxafb_info *fbi = (struct pxafb_info *)info;
	int i;

	switch (blank) {
	case FB_BLANK_POWERDOWN:
	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_NORMAL:
		if (fbi->fb.fix.visual == FB_VISUAL_PSEUDOCOLOR ||
		    fbi->fb.fix.visual == FB_VISUAL_STATIC_PSEUDOCOLOR)
			for (i = 0; i < fbi->palette_size; i++)
				pxafb_setpalettereg(i, 0, 0, 0, 0, info);

		pxafb_schedule_work(fbi, C_DISABLE);
		/* TODO if (pxafb_blank_helper) pxafb_blank_helper(blank); */
		break;

	case FB_BLANK_UNBLANK:
		/* TODO if (pxafb_blank_helper) pxafb_blank_helper(blank); */
		if (fbi->fb.fix.visual == FB_VISUAL_PSEUDOCOLOR ||
		    fbi->fb.fix.visual == FB_VISUAL_STATIC_PSEUDOCOLOR)
			fb_set_cmap(&fbi->fb.cmap, info);
		pxafb_schedule_work(fbi, C_ENABLE);
	}
	return 0;
}