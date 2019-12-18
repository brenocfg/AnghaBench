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
typedef  int u8 ;
typedef  int u16 ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int I915_READ16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE16 (int /*<<< orphan*/ ,int) ; 
 int MEMCTL_CMD_CHFREQ ; 
 int MEMCTL_CMD_SHIFT ; 
 int MEMCTL_CMD_STS ; 
 int MEMCTL_FREQ_SHIFT ; 
 int MEMCTL_SFCAVM ; 
 int /*<<< orphan*/  MEMSWCTL ; 
 int /*<<< orphan*/  POSTING_READ16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mchdev_lock ; 

bool ironlake_set_drps(struct drm_device *dev, u8 val)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u16 rgvswctl;

	assert_spin_locked(&mchdev_lock);

	rgvswctl = I915_READ16(MEMSWCTL);
	if (rgvswctl & MEMCTL_CMD_STS) {
		DRM_DEBUG("gpu busy, RCS change rejected\n");
		return false; /* still busy with another command */
	}

	rgvswctl = (MEMCTL_CMD_CHFREQ << MEMCTL_CMD_SHIFT) |
		(val << MEMCTL_FREQ_SHIFT) | MEMCTL_SFCAVM;
	I915_WRITE16(MEMSWCTL, rgvswctl);
	POSTING_READ16(MEMSWCTL);

	rgvswctl |= MEMCTL_CMD_STS;
	I915_WRITE16(MEMSWCTL, rgvswctl);

	return true;
}