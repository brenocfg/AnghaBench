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
struct ffb_par {int flags; int board_type; } ;
struct TYPE_2__ {int line_length; int /*<<< orphan*/  accel; int /*<<< orphan*/  visual; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct fb_info {TYPE_1__ fix; scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ACCEL_SUN_CREATOR ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int FFB_FLAG_AFB ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void ffb_init_fix(struct fb_info *info)
{
	struct ffb_par *par = (struct ffb_par *)info->par;
	const char *ffb_type_name;

	if (!(par->flags & FFB_FLAG_AFB)) {
		if ((par->board_type & 0x7) == 0x3)
			ffb_type_name = "Creator 3D";
		else
			ffb_type_name = "Creator";
	} else
		ffb_type_name = "Elite 3D";

	strlcpy(info->fix.id, ffb_type_name, sizeof(info->fix.id));

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_TRUECOLOR;

	/* Framebuffer length is the same regardless of resolution. */
	info->fix.line_length = 8192;

	info->fix.accel = FB_ACCEL_SUN_CREATOR;
}