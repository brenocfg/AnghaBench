#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ clock; } ;
struct drm_crtc {TYPE_1__ mode; scalar_t__ fb; } ;
struct TYPE_4__ {scalar_t__ active; } ;

/* Variables and functions */
 TYPE_2__* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static bool intel_crtc_active(struct drm_crtc *crtc)
{
	/* Be paranoid as we can arrive here with only partial
	 * state retrieved from the hardware during setup.
	 */
	return to_intel_crtc(crtc)->active && crtc->fb && crtc->mode.clock;
}