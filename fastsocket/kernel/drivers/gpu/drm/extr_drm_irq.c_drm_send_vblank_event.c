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
struct timeval {int dummy; } ;
struct drm_pending_vblank_event {int pipe; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 unsigned int drm_vblank_count_and_time (struct drm_device*,int,struct timeval*) ; 
 struct timeval get_drm_timestamp () ; 
 int /*<<< orphan*/  send_vblank_event (struct drm_device*,struct drm_pending_vblank_event*,unsigned int,struct timeval*) ; 

void drm_send_vblank_event(struct drm_device *dev, int crtc,
		struct drm_pending_vblank_event *e)
{
	struct timeval now;
	unsigned int seq;
	if (crtc >= 0) {
		seq = drm_vblank_count_and_time(dev, crtc, &now);
	} else {
		seq = 0;

		now = get_drm_timestamp();
	}
	e->pipe = crtc;
	send_vblank_event(dev, e, seq, &now);
}