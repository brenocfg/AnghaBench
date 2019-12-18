#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_1__ drm_radeon_private_t ;
struct TYPE_6__ {int func; } ;
typedef  TYPE_2__ drm_radeon_init_t ;

/* Variables and functions */
 int CHIP_R600 ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
#define  RADEON_CLEANUP_CP 132 
 int RADEON_FAMILY_MASK ; 
#define  RADEON_INIT_CP 131 
#define  RADEON_INIT_R200_CP 130 
#define  RADEON_INIT_R300_CP 129 
#define  RADEON_INIT_R600_CP 128 
 int /*<<< orphan*/  r300_init_reg_flags (struct drm_device*) ; 
 int r600_do_cleanup_cp (struct drm_device*) ; 
 int r600_do_init_cp (struct drm_device*,TYPE_2__*,struct drm_file*) ; 
 int radeon_do_cleanup_cp (struct drm_device*) ; 
 int radeon_do_init_cp (struct drm_device*,TYPE_2__*,struct drm_file*) ; 

int radeon_cp_init(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	drm_radeon_init_t *init = data;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	if (init->func == RADEON_INIT_R300_CP)
		r300_init_reg_flags(dev);

	switch (init->func) {
	case RADEON_INIT_CP:
	case RADEON_INIT_R200_CP:
	case RADEON_INIT_R300_CP:
		return radeon_do_init_cp(dev, init, file_priv);
	case RADEON_INIT_R600_CP:
		return r600_do_init_cp(dev, init, file_priv);
	case RADEON_CLEANUP_CP:
		if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600)
			return r600_do_cleanup_cp(dev);
		else
			return radeon_do_cleanup_cp(dev);
	}

	return -EINVAL;
}