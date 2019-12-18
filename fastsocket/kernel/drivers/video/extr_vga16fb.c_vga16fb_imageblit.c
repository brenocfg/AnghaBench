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
struct fb_info {int dummy; } ;
struct fb_image {int depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  vga_imageblit_color (struct fb_info*,struct fb_image const*) ; 
 int /*<<< orphan*/  vga_imageblit_expand (struct fb_info*,struct fb_image const*) ; 

__attribute__((used)) static void vga16fb_imageblit(struct fb_info *info, const struct fb_image *image)
{
	if (image->depth == 1)
		vga_imageblit_expand(info, image);
	else
		vga_imageblit_color(info, image);
}