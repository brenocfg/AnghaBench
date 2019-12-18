#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tdfx_par {int* palette; } ;
struct TYPE_13__ {int offset; int /*<<< orphan*/  length; } ;
struct TYPE_12__ {int offset; int /*<<< orphan*/  length; } ;
struct TYPE_11__ {int offset; int /*<<< orphan*/  length; } ;
struct TYPE_10__ {int offset; int /*<<< orphan*/  length; } ;
struct TYPE_14__ {int /*<<< orphan*/  bits_per_pixel; TYPE_6__ transp; TYPE_5__ blue; TYPE_4__ green; TYPE_3__ red; scalar_t__ grayscale; } ;
struct TYPE_9__ {int visual; } ;
struct TYPE_8__ {unsigned int len; } ;
struct fb_info {TYPE_7__ var; TYPE_2__ fix; TYPE_1__ cmap; struct tdfx_par* par; } ;

/* Variables and functions */
 int CNVT_TOHW (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
#define  FB_VISUAL_PSEUDOCOLOR 129 
#define  FB_VISUAL_TRUECOLOR 128 
 int /*<<< orphan*/  do_setpalentry (struct tdfx_par*,unsigned int,int) ; 

__attribute__((used)) static int tdfxfb_setcolreg(unsigned regno, unsigned red, unsigned green,
			    unsigned blue, unsigned transp,
			    struct fb_info *info)
{
	struct tdfx_par *par = info->par;
	u32 rgbcol;

	if (regno >= info->cmap.len || regno > 255)
		return 1;

	/* grayscale works only partially under directcolor */
	if (info->var.grayscale) {
		/* grayscale = 0.30*R + 0.59*G + 0.11*B */
		blue = (red * 77 + green * 151 + blue * 28) >> 8;
		green = blue;
		red = blue;
	}

	switch (info->fix.visual) {
	case FB_VISUAL_PSEUDOCOLOR:
		rgbcol = (((u32)red   & 0xff00) << 8) |
			 (((u32)green & 0xff00) << 0) |
			 (((u32)blue  & 0xff00) >> 8);
		do_setpalentry(par, regno, rgbcol);
		break;
	/* Truecolor has no hardware color palettes. */
	case FB_VISUAL_TRUECOLOR:
		if (regno < 16) {
			rgbcol = (CNVT_TOHW(red, info->var.red.length) <<
				  info->var.red.offset) |
				(CNVT_TOHW(green, info->var.green.length) <<
				 info->var.green.offset) |
				(CNVT_TOHW(blue, info->var.blue.length) <<
				 info->var.blue.offset) |
				(CNVT_TOHW(transp, info->var.transp.length) <<
				 info->var.transp.offset);
			par->palette[regno] = rgbcol;
		}

		break;
	default:
		DPRINTK("bad depth %u\n", info->var.bits_per_pixel);
		break;
	}

	return 0;
}