#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tga_par {int tga_type; int xres; int bits_per_pixel; int yres; scalar_t__ tga_regs_base; scalar_t__ tga_fb_base; int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int length; scalar_t__ offset; } ;
struct TYPE_8__ {int length; int offset; } ;
struct TYPE_7__ {int length; int offset; } ;
struct TYPE_10__ {TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;
struct TYPE_6__ {int line_length; size_t smem_start; int smem_len; size_t mmio_start; int mmio_len; int /*<<< orphan*/  accel; scalar_t__ ywrapstep; scalar_t__ ypanstep; scalar_t__ xpanstep; int /*<<< orphan*/  visual; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct fb_info {TYPE_5__ var; TYPE_1__ fix; scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ACCEL_DEC_TGA ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_DIRECTCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int TGA_BUS_PCI (int /*<<< orphan*/ ) ; 
 int TGA_BUS_TC (int /*<<< orphan*/ ) ; 
#define  TGA_TYPE_24PLANE 130 
#define  TGA_TYPE_24PLUSZ 129 
#define  TGA_TYPE_8PLANE 128 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
tgafb_init_fix(struct fb_info *info)
{
	struct tga_par *par = (struct tga_par *)info->par;
	int tga_bus_pci = TGA_BUS_PCI(par->dev);
	int tga_bus_tc = TGA_BUS_TC(par->dev);
	u8 tga_type = par->tga_type;
	const char *tga_type_name = NULL;

	switch (tga_type) {
	case TGA_TYPE_8PLANE:
		if (tga_bus_pci)
			tga_type_name = "Digital ZLXp-E1";
		if (tga_bus_tc)
			tga_type_name = "Digital ZLX-E1";
		break;
	case TGA_TYPE_24PLANE:
		if (tga_bus_pci)
			tga_type_name = "Digital ZLXp-E2";
		if (tga_bus_tc)
			tga_type_name = "Digital ZLX-E2";
		break;
	case TGA_TYPE_24PLUSZ:
		if (tga_bus_pci)
			tga_type_name = "Digital ZLXp-E3";
		if (tga_bus_tc)
			tga_type_name = "Digital ZLX-E3";
		break;
	default:
		tga_type_name = "Unknown";
		break;
	}

	strlcpy(info->fix.id, tga_type_name, sizeof(info->fix.id));

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux = 0;
	info->fix.visual = (tga_type == TGA_TYPE_8PLANE
			    ? FB_VISUAL_PSEUDOCOLOR
			    : FB_VISUAL_DIRECTCOLOR);

	info->fix.line_length = par->xres * (par->bits_per_pixel >> 3);
	info->fix.smem_start = (size_t) par->tga_fb_base;
	info->fix.smem_len = info->fix.line_length * par->yres;
	info->fix.mmio_start = (size_t) par->tga_regs_base;
	info->fix.mmio_len = 512;

	info->fix.xpanstep = 0;
	info->fix.ypanstep = 0;
	info->fix.ywrapstep = 0;

	info->fix.accel = FB_ACCEL_DEC_TGA;

	/*
	 * These are needed by fb_set_logo_truepalette(), so we
	 * set them here for 24-plane cards.
	 */
	if (tga_type != TGA_TYPE_8PLANE) {
		info->var.red.length = 8;
		info->var.green.length = 8;
		info->var.blue.length = 8;
		info->var.red.offset = 16;
		info->var.green.offset = 8;
		info->var.blue.offset = 0;
	}
}