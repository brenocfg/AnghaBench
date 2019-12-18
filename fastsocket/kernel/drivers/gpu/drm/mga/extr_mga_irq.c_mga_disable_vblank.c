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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 

void mga_disable_vblank(struct drm_device *dev, int crtc)
{
	if (crtc != 0) {
		DRM_ERROR("tried to disable vblank on non-existent crtc %d\n",
			  crtc);
	}

	/* Do *NOT* disable the vertical refresh interrupt.  MGA doesn't have
	 * a nice hardware counter that tracks the number of refreshes when
	 * the interrupt is disabled, and the kernel doesn't know the refresh
	 * rate to calculate an estimate.
	 */
	/* MGA_WRITE(MGA_IEN, MGA_VLINEIEN | MGA_SOFTRAPEN); */
}