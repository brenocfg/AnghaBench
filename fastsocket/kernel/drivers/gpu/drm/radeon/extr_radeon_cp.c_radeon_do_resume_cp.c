#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_5__ {int flags; scalar_t__ have_z_offset; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int RADEON_IS_AGP ; 
 int /*<<< orphan*/  RADEON_SW_INT_ENABLE ; 
 int /*<<< orphan*/  radeon_cp_init_ring_buffer (struct drm_device*,TYPE_1__*,struct drm_file*) ; 
 int /*<<< orphan*/  radeon_cp_load_microcode (TYPE_1__*) ; 
 int /*<<< orphan*/  radeon_do_engine_reset (struct drm_device*) ; 
 int /*<<< orphan*/  radeon_irq_set_state (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_set_pcigart (TYPE_1__*,int) ; 

__attribute__((used)) static int radeon_do_resume_cp(struct drm_device *dev, struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;

	if (!dev_priv) {
		DRM_ERROR("Called with no initialization\n");
		return -EINVAL;
	}

	DRM_DEBUG("Starting radeon_do_resume_cp()\n");

#if __OS_HAS_AGP
	if (dev_priv->flags & RADEON_IS_AGP) {
		/* Turn off PCI GART */
		radeon_set_pcigart(dev_priv, 0);
	} else
#endif
	{
		/* Turn on PCI GART */
		radeon_set_pcigart(dev_priv, 1);
	}

	radeon_cp_load_microcode(dev_priv);
	radeon_cp_init_ring_buffer(dev, dev_priv, file_priv);

	dev_priv->have_z_offset = 0;
	radeon_do_engine_reset(dev);
	radeon_irq_set_state(dev, RADEON_SW_INT_ENABLE, 1);

	DRM_DEBUG("radeon_do_resume_cp() complete\n");

	return 0;
}