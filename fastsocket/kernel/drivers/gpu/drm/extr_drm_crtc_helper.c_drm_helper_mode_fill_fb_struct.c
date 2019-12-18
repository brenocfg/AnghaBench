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
struct drm_mode_fb_cmd2 {int /*<<< orphan*/  pixel_format; int /*<<< orphan*/ * offsets; int /*<<< orphan*/ * pitches; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_framebuffer {int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  depth; int /*<<< orphan*/ * offsets; int /*<<< orphan*/ * pitches; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_fb_get_bpp_depth (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int drm_helper_mode_fill_fb_struct(struct drm_framebuffer *fb,
				   struct drm_mode_fb_cmd2 *mode_cmd)
{
	int i;

	fb->width = mode_cmd->width;
	fb->height = mode_cmd->height;
	for (i = 0; i < 4; i++) {
		fb->pitches[i] = mode_cmd->pitches[i];
		fb->offsets[i] = mode_cmd->offsets[i];
	}
	drm_fb_get_bpp_depth(mode_cmd->pixel_format, &fb->depth,
				    &fb->bits_per_pixel);
	fb->pixel_format = mode_cmd->pixel_format;

	return 0;
}