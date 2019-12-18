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
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {int bits_per_pixel; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ var; } ;
struct fb_image {int depth; int width; int dx; } ;

/* Variables and functions */
 scalar_t__ FB_TYPE_INTERLEAVED_PLANES ; 
 int /*<<< orphan*/  cfb_imageblit (struct fb_info*,struct fb_image const*) ; 
 int /*<<< orphan*/  s3fb_cfb4_imageblit (struct fb_info*,struct fb_image const*) ; 
 int /*<<< orphan*/  s3fb_iplan_imageblit (struct fb_info*,struct fb_image const*) ; 

__attribute__((used)) static void s3fb_imageblit(struct fb_info *info, const struct fb_image *image)
{
	if ((info->var.bits_per_pixel == 4) && (image->depth == 1)
	    && ((image->width % 8) == 0) && ((image->dx % 8) == 0)) {
		if (info->fix.type == FB_TYPE_INTERLEAVED_PLANES)
			s3fb_iplan_imageblit(info, image);
		else
			s3fb_cfb4_imageblit(info, image);
	} else
		cfb_imageblit(info, image);
}