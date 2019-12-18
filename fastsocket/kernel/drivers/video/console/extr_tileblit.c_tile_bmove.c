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
struct vc_data {int dummy; } ;
struct fb_tilearea {int sx; int sy; int dx; int dy; int height; int width; } ;
struct fb_info {TYPE_1__* tileops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fb_tilecopy ) (struct fb_info*,struct fb_tilearea*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct fb_info*,struct fb_tilearea*) ; 

__attribute__((used)) static void tile_bmove(struct vc_data *vc, struct fb_info *info, int sy,
		       int sx, int dy, int dx, int height, int width)
{
	struct fb_tilearea area;

	area.sx = sx;
	area.sy = sy;
	area.dx = dx;
	area.dy = dy;
	area.height = height;
	area.width = width;

	info->tileops->fb_tilecopy(info, &area);
}