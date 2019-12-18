#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/ * pfp_fw; int /*<<< orphan*/ * me_fw; int /*<<< orphan*/  fb_heap; int /*<<< orphan*/  gart_heap; scalar_t__ mmio; scalar_t__ cp_running; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int CHIP_R600 ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int /*<<< orphan*/  PZERO ; 
 int RADEON_FAMILY_MASK ; 
 scalar_t__ RADEON_GEN_INT_CNTL ; 
 int RADEON_MAX_SURFACES ; 
 scalar_t__ RADEON_SURFACE0_INFO ; 
 scalar_t__ RADEON_SURFACE0_LOWER_BOUND ; 
 scalar_t__ RADEON_SURFACE0_UPPER_BOUND ; 
 int /*<<< orphan*/  RADEON_WRITE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_do_cleanup_cp (struct drm_device*) ; 
 int r600_do_cp_idle (TYPE_1__*) ; 
 int /*<<< orphan*/  r600_do_cp_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  r600_do_engine_reset (struct drm_device*) ; 
 int /*<<< orphan*/  radeon_do_cleanup_cp (struct drm_device*) ; 
 int radeon_do_cp_idle (TYPE_1__*) ; 
 int /*<<< orphan*/  radeon_do_cp_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  radeon_do_engine_reset (struct drm_device*) ; 
 int /*<<< orphan*/  radeon_mem_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  tsleep (int*,int /*<<< orphan*/ ,char*,int) ; 

void radeon_do_release(struct drm_device * dev)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	int i, ret;

	if (dev_priv) {
		if (dev_priv->cp_running) {
			/* Stop the cp */
			if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600) {
				while ((ret = r600_do_cp_idle(dev_priv)) != 0) {
					DRM_DEBUG("radeon_do_cp_idle %d\n", ret);
#ifdef __linux__
					schedule();
#else
					tsleep(&ret, PZERO, "rdnrel", 1);
#endif
				}
			} else {
				while ((ret = radeon_do_cp_idle(dev_priv)) != 0) {
					DRM_DEBUG("radeon_do_cp_idle %d\n", ret);
#ifdef __linux__
					schedule();
#else
					tsleep(&ret, PZERO, "rdnrel", 1);
#endif
				}
			}
			if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600) {
				r600_do_cp_stop(dev_priv);
				r600_do_engine_reset(dev);
			} else {
				radeon_do_cp_stop(dev_priv);
				radeon_do_engine_reset(dev);
			}
		}

		if ((dev_priv->flags & RADEON_FAMILY_MASK) < CHIP_R600) {
			/* Disable *all* interrupts */
			if (dev_priv->mmio)	/* remove this after permanent addmaps */
				RADEON_WRITE(RADEON_GEN_INT_CNTL, 0);

			if (dev_priv->mmio) {	/* remove all surfaces */
				for (i = 0; i < RADEON_MAX_SURFACES; i++) {
					RADEON_WRITE(RADEON_SURFACE0_INFO + 16 * i, 0);
					RADEON_WRITE(RADEON_SURFACE0_LOWER_BOUND +
						     16 * i, 0);
					RADEON_WRITE(RADEON_SURFACE0_UPPER_BOUND +
						     16 * i, 0);
				}
			}
		}

		/* Free memory heap structures */
		radeon_mem_takedown(&(dev_priv->gart_heap));
		radeon_mem_takedown(&(dev_priv->fb_heap));

		/* deallocate kernel resources */
		if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600)
			r600_do_cleanup_cp(dev);
		else
			radeon_do_cleanup_cp(dev);
		release_firmware(dev_priv->me_fw);
		dev_priv->me_fw = NULL;
		release_firmware(dev_priv->pfp_fw);
		dev_priv->pfp_fw = NULL;
	}
}