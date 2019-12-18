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
struct radeonfb_info {int dummy; } ;
struct fb_info {scalar_t__ state; struct radeonfb_info* par; } ;
struct fb_image {int dummy; } ;

/* Variables and functions */
 scalar_t__ FBINFO_STATE_RUNNING ; 
 int /*<<< orphan*/  cfb_imageblit (struct fb_info*,struct fb_image const*) ; 
 int /*<<< orphan*/  radeon_engine_idle () ; 

void radeonfb_imageblit(struct fb_info *info, const struct fb_image *image)
{
	struct radeonfb_info *rinfo = info->par;

	if (info->state != FBINFO_STATE_RUNNING)
		return;
	radeon_engine_idle();

	cfb_imageblit(info, image);
}