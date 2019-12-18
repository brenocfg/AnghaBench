#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_radeon_master_private {TYPE_1__* sarea_priv; } ;
struct drm_file {TYPE_3__* master; } ;
struct drm_device {TYPE_2__* dev_private; } ;
struct TYPE_5__ {scalar_t__ nbox; scalar_t__ ctx_owner; } ;
typedef  TYPE_1__ drm_radeon_sarea_t ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_2__ drm_radeon_private_t ;
struct TYPE_7__ {struct drm_radeon_master_private* driver_priv; } ;

/* Variables and functions */
 int CHIP_R600 ; 
 int /*<<< orphan*/  COMMIT_RING () ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 int RADEON_FAMILY_MASK ; 
 scalar_t__ RADEON_NR_SAREA_CLIPRECTS ; 
 int /*<<< orphan*/  RING_SPACE_TEST_WITH_RETURN (TYPE_2__*) ; 
 int /*<<< orphan*/  r600_cp_dispatch_swap (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  radeon_cp_dispatch_swap (struct drm_device*,TYPE_3__*) ; 

__attribute__((used)) static int radeon_cp_swap(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	struct drm_radeon_master_private *master_priv = file_priv->master->driver_priv;
	drm_radeon_sarea_t *sarea_priv = master_priv->sarea_priv;

	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	RING_SPACE_TEST_WITH_RETURN(dev_priv);

	if (sarea_priv->nbox > RADEON_NR_SAREA_CLIPRECTS)
		sarea_priv->nbox = RADEON_NR_SAREA_CLIPRECTS;

	if ((dev_priv->flags & RADEON_FAMILY_MASK) >= CHIP_R600)
		r600_cp_dispatch_swap(dev, file_priv);
	else
		radeon_cp_dispatch_swap(dev, file_priv->master);
	sarea_priv->ctx_owner = 0;

	COMMIT_RING();
	return 0;
}