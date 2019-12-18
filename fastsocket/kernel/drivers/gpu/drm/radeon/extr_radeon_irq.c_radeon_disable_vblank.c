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
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_2__ {int flags; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int CHIP_RS600 ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  R500_D1MODE_INT_MASK ; 
 int /*<<< orphan*/  R500_D2MODE_INT_MASK ; 
 int /*<<< orphan*/  RADEON_CRTC2_VBLANK_MASK ; 
 int /*<<< orphan*/  RADEON_CRTC_VBLANK_MASK ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  r500_vbl_irq_set_state (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_irq_set_state (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void radeon_disable_vblank(struct drm_device *dev, int crtc)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;

	if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_RS600) {
		switch (crtc) {
		case 0:
			r500_vbl_irq_set_state(dev, R500_D1MODE_INT_MASK, 0);
			break;
		case 1:
			r500_vbl_irq_set_state(dev, R500_D2MODE_INT_MASK, 0);
			break;
		default:
			DRM_ERROR("tried to enable vblank on non-existent crtc %d\n",
				  crtc);
			break;
		}
	} else {
		switch (crtc) {
		case 0:
			radeon_irq_set_state(dev, RADEON_CRTC_VBLANK_MASK, 0);
			break;
		case 1:
			radeon_irq_set_state(dev, RADEON_CRTC2_VBLANK_MASK, 0);
			break;
		default:
			DRM_ERROR("tried to enable vblank on non-existent crtc %d\n",
				  crtc);
			break;
		}
	}
}