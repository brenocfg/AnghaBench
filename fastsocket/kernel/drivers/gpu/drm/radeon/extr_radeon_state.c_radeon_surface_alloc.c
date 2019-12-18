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
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_radeon_surface_alloc_t ;
typedef  int /*<<< orphan*/  drm_radeon_private_t ;

/* Variables and functions */
 int EINVAL ; 
 int alloc_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct drm_file*) ; 

__attribute__((used)) static int radeon_surface_alloc(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_radeon_private_t *dev_priv = dev->dev_private;
	drm_radeon_surface_alloc_t *alloc = data;

	if (alloc_surface(alloc, dev_priv, file_priv) == -1)
		return -EINVAL;
	else
		return 0;
}