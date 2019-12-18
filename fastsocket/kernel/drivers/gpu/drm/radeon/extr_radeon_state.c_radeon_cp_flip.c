#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int /*<<< orphan*/  master; } ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  page_flipping; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_RING () ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  RING_SPACE_TEST_WITH_RETURN (TYPE_1__*) ; 
 int /*<<< orphan*/  radeon_cp_dispatch_flip (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_do_init_pageflip (struct drm_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int radeon_cp_flip(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	RING_SPACE_TEST_WITH_RETURN(dev_priv);

	if (!dev_priv->page_flipping)
		radeon_do_init_pageflip(dev, file_priv->master);

	radeon_cp_dispatch_flip(dev, file_priv->master);

	COMMIT_RING();
	return 0;
}