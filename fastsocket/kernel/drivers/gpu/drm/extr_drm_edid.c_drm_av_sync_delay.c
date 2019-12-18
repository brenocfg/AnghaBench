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
struct drm_display_mode {int flags; } ;
struct drm_connector {int* audio_latency; int* video_latency; int /*<<< orphan*/ * latency_present; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 

int drm_av_sync_delay(struct drm_connector *connector,
		      struct drm_display_mode *mode)
{
	int i = !!(mode->flags & DRM_MODE_FLAG_INTERLACE);
	int a, v;

	if (!connector->latency_present[0])
		return 0;
	if (!connector->latency_present[1])
		i = 0;

	a = connector->audio_latency[i];
	v = connector->video_latency[i];

	/*
	 * HDMI/DP sink doesn't support audio or video?
	 */
	if (a == 255 || v == 255)
		return 0;

	/*
	 * Convert raw EDID values to millisecond.
	 * Treat unknown latency as 0ms.
	 */
	if (a)
		a = min(2 * (a - 1), 500);
	if (v)
		v = min(2 * (v - 1), 500);

	return max(v - a, 0);
}