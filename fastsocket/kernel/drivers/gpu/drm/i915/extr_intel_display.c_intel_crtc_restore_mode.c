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
struct drm_crtc {int /*<<< orphan*/  fb; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_set_mode (struct drm_crtc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intel_crtc_restore_mode(struct drm_crtc *crtc)
{
	intel_set_mode(crtc, &crtc->mode, crtc->x, crtc->y, crtc->fb);
}