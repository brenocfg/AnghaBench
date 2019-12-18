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
struct fb_info {struct arcfb_par* par; } ;
struct fb_image {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
struct arcfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arcfb_lcd_update (struct arcfb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_imageblit (struct fb_info*,struct fb_image const*) ; 

__attribute__((used)) static void arcfb_imageblit(struct fb_info *info, const struct fb_image *image)
{
	struct arcfb_par *par = info->par;

	sys_imageblit(info, image);

	/* update the physical lcd */
	arcfb_lcd_update(par, image->dx, image->dy, image->width,
				image->height);
}