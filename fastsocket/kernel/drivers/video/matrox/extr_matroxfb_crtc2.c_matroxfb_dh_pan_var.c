#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ offbase; } ;
struct TYPE_4__ {unsigned int xoffset; unsigned int yoffset; int bits_per_pixel; unsigned int xres_virtual; } ;
struct TYPE_5__ {TYPE_1__ var; } ;
struct matroxfb_dh_fb_info {scalar_t__ interlaced; TYPE_3__ video; TYPE_2__ fbcon; struct matrox_fb_info* primary_dev; } ;
struct matrox_fb_info {int dummy; } ;
struct fb_var_screeninfo {unsigned int xoffset; unsigned int yoffset; } ;

/* Variables and functions */
 int /*<<< orphan*/  mga_outl (int,unsigned int) ; 

__attribute__((used)) static void matroxfb_dh_pan_var(struct matroxfb_dh_fb_info* m2info,
		struct fb_var_screeninfo* var) {
	unsigned int pos;
	unsigned int linelen;
	unsigned int pixelsize;
	struct matrox_fb_info *minfo = m2info->primary_dev;

	m2info->fbcon.var.xoffset = var->xoffset;
	m2info->fbcon.var.yoffset = var->yoffset;
	pixelsize = m2info->fbcon.var.bits_per_pixel >> 3;
	linelen = m2info->fbcon.var.xres_virtual * pixelsize;
	pos = m2info->fbcon.var.yoffset * linelen + m2info->fbcon.var.xoffset * pixelsize;
	pos += m2info->video.offbase;
	if (m2info->interlaced) {
		mga_outl(0x3C2C, pos);
		mga_outl(0x3C28, pos + linelen);
	} else {
		mga_outl(0x3C28, pos);
	}
}