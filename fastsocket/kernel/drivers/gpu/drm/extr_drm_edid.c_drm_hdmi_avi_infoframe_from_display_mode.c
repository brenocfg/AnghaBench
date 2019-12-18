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
struct hdmi_avi_infoframe {int /*<<< orphan*/  active_aspect; int /*<<< orphan*/  picture_aspect; int /*<<< orphan*/  video_code; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HDMI_ACTIVE_ASPECT_PICTURE ; 
 int /*<<< orphan*/  HDMI_PICTURE_ASPECT_NONE ; 
 int /*<<< orphan*/  drm_match_cea_mode (struct drm_display_mode const*) ; 
 int hdmi_avi_infoframe_init (struct hdmi_avi_infoframe*) ; 

int
drm_hdmi_avi_infoframe_from_display_mode(struct hdmi_avi_infoframe *frame,
					 const struct drm_display_mode *mode)
{
	int err;

	if (!frame || !mode)
		return -EINVAL;

	err = hdmi_avi_infoframe_init(frame);
	if (err < 0)
		return err;

	frame->video_code = drm_match_cea_mode(mode);
	if (!frame->video_code)
		return 0;

	frame->picture_aspect = HDMI_PICTURE_ASPECT_NONE;
	frame->active_aspect = HDMI_ACTIVE_ASPECT_PICTURE;

	return 0;
}