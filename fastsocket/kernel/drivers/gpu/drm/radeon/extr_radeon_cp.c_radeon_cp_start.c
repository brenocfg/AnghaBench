#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_4__ {scalar_t__ cp_mode; int flags; scalar_t__ cp_running; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int CHIP_R600 ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 scalar_t__ RADEON_CSQ_PRIDIS_INDDIS ; 
 int RADEON_FAMILY_MASK ; 
 int /*<<< orphan*/  r600_do_cp_start (TYPE_1__*) ; 
 int /*<<< orphan*/  radeon_do_cp_start (TYPE_1__*) ; 

int radeon_cp_start(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	if (dev_priv->cp_running) {
		DRM_DEBUG("while CP running\n");
		return 0;
	}
	if (dev_priv->cp_mode == RADEON_CSQ_PRIDIS_INDDIS) {
		DRM_DEBUG("called with bogus CP mode (%d)\n",
			  dev_priv->cp_mode);
		return 0;
	}

	if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600)
		r600_do_cp_start(dev_priv);
	else
		radeon_do_cp_start(dev_priv);

	return 0;
}