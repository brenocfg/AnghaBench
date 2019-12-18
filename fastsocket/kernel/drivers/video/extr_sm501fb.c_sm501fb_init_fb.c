#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int (* fb_check_var ) (TYPE_3__*,struct fb_info*) ;int /*<<< orphan*/ * fb_cursor; } ;
struct sm501fb_par {TYPE_4__ ops; struct sm501fb_info* info; } ;
struct sm501fb_info {int /*<<< orphan*/  dev; scalar_t__ regs; TYPE_1__* pdata; } ;
struct sm501_platdata_fbsub {int flags; int def_bpp; scalar_t__ def_mode; } ;
struct fb_ops {int dummy; } ;
struct TYPE_9__ {int bits_per_pixel; int /*<<< orphan*/  yres; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres; int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  vmode; scalar_t__ accel_flags; int /*<<< orphan*/  activate; scalar_t__ nonstd; } ;
struct TYPE_8__ {int xpanstep; int ypanstep; int /*<<< orphan*/  accel; scalar_t__ ywrapstep; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct fb_info {int flags; TYPE_3__ var; TYPE_4__* fbops; int /*<<< orphan*/  cmap; TYPE_2__ fix; struct sm501fb_par* par; } ;
typedef  enum sm501_controller { ____Placeholder_sm501_controller } sm501_controller ;
struct TYPE_7__ {scalar_t__ fb_route; struct sm501_platdata_fbsub* fb_pnl; struct sm501_platdata_fbsub* fb_crt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FBINFO_FLAG_DEFAULT ; 
 int FBINFO_HWACCEL_XPAN ; 
 int FBINFO_HWACCEL_YPAN ; 
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
#define  HEAD_CRT 129 
#define  HEAD_PANEL 128 
 int /*<<< orphan*/  NR_PALETTE ; 
 int SM501FB_FLAG_USE_HWCURSOR ; 
 int SM501FB_FLAG_USE_INIT_MODE ; 
 scalar_t__ SM501_DC_CRT_CONTROL ; 
 unsigned long SM501_DC_CRT_CONTROL_ENABLE ; 
 unsigned long SM501_DC_CRT_CONTROL_SEL ; 
 scalar_t__ SM501_DC_PANEL_CONTROL ; 
 unsigned long SM501_DC_PANEL_CONTROL_EN ; 
 scalar_t__ SM501_FB_CRT_PANEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fb_alloc_cmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fb_find_mode (TYPE_3__*,struct fb_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fb_set_cmap (int /*<<< orphan*/ *,struct fb_info*) ; 
 int /*<<< orphan*/  fb_videomode_to_var (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  sm501fb_ops_crt ; 
 int /*<<< orphan*/  sm501fb_ops_pnl ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int stub1 (TYPE_3__*,struct fb_info*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int sm501fb_init_fb(struct fb_info *fb,
			   enum sm501_controller head,
			   const char *fbname)
{
	struct sm501_platdata_fbsub *pd;
	struct sm501fb_par *par = fb->par;
	struct sm501fb_info *info = par->info;
	unsigned long ctrl;
	unsigned int enable;
	int ret;

	switch (head) {
	case HEAD_CRT:
		pd = info->pdata->fb_crt;
		ctrl = readl(info->regs + SM501_DC_CRT_CONTROL);
		enable = (ctrl & SM501_DC_CRT_CONTROL_ENABLE) ? 1 : 0;

		/* ensure we set the correct source register */
		if (info->pdata->fb_route != SM501_FB_CRT_PANEL) {
			ctrl |= SM501_DC_CRT_CONTROL_SEL;
			writel(ctrl, info->regs + SM501_DC_CRT_CONTROL);
		}

		break;

	case HEAD_PANEL:
		pd = info->pdata->fb_pnl;
		ctrl = readl(info->regs + SM501_DC_PANEL_CONTROL);
		enable = (ctrl & SM501_DC_PANEL_CONTROL_EN) ? 1 : 0;
		break;

	default:
		pd = NULL;		/* stop compiler warnings */
		ctrl = 0;
		enable = 0;
		BUG();
	}

	dev_info(info->dev, "fb %s %sabled at start\n",
		 fbname, enable ? "en" : "dis");

	/* check to see if our routing allows this */

	if (head == HEAD_CRT && info->pdata->fb_route == SM501_FB_CRT_PANEL) {
		ctrl &= ~SM501_DC_CRT_CONTROL_SEL;
		writel(ctrl, info->regs + SM501_DC_CRT_CONTROL);
		enable = 0;
	}

	strlcpy(fb->fix.id, fbname, sizeof(fb->fix.id));

	memcpy(&par->ops,
	       (head == HEAD_CRT) ? &sm501fb_ops_crt : &sm501fb_ops_pnl,
	       sizeof(struct fb_ops));

	/* update ops dependant on what we've been passed */

	if ((pd->flags & SM501FB_FLAG_USE_HWCURSOR) == 0)
		par->ops.fb_cursor = NULL;

	fb->fbops = &par->ops;
	fb->flags = FBINFO_FLAG_DEFAULT |
		FBINFO_HWACCEL_XPAN | FBINFO_HWACCEL_YPAN;

	/* fixed data */

	fb->fix.type		= FB_TYPE_PACKED_PIXELS;
	fb->fix.type_aux	= 0;
	fb->fix.xpanstep	= 1;
	fb->fix.ypanstep	= 1;
	fb->fix.ywrapstep	= 0;
	fb->fix.accel		= FB_ACCEL_NONE;

	/* screenmode */

	fb->var.nonstd		= 0;
	fb->var.activate	= FB_ACTIVATE_NOW;
	fb->var.accel_flags	= 0;
	fb->var.vmode		= FB_VMODE_NONINTERLACED;
	fb->var.bits_per_pixel  = 16;

	if (enable && (pd->flags & SM501FB_FLAG_USE_INIT_MODE) && 0) {
		/* TODO read the mode from the current display */

	} else {
		if (pd->def_mode) {
			dev_info(info->dev, "using supplied mode\n");
			fb_videomode_to_var(&fb->var, pd->def_mode);

			fb->var.bits_per_pixel = pd->def_bpp ? pd->def_bpp : 8;
			fb->var.xres_virtual = fb->var.xres;
			fb->var.yres_virtual = fb->var.yres;
		} else {
			ret = fb_find_mode(&fb->var, fb,
					   NULL, NULL, 0, NULL, 8);

			if (ret == 0 || ret == 4) {
				dev_err(info->dev,
					"failed to get initial mode\n");
				return -EINVAL;
			}
		}
	}

	/* initialise and set the palette */
	if (fb_alloc_cmap(&fb->cmap, NR_PALETTE, 0)) {
		dev_err(info->dev, "failed to allocate cmap memory\n");
		return -ENOMEM;
	}
	fb_set_cmap(&fb->cmap, fb);

	ret = (fb->fbops->fb_check_var)(&fb->var, fb);
	if (ret)
		dev_err(info->dev, "check_var() failed on initial setup?\n");

	return 0;
}