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
struct TYPE_6__ {TYPE_1__* virt_surfaces; } ;
typedef  TYPE_2__ drm_radeon_private_t ;
struct TYPE_5__ {int /*<<< orphan*/  lower; struct drm_file* file_priv; } ;

/* Variables and functions */
 int RADEON_MAX_SURFACES ; 
 int /*<<< orphan*/  free_surface (struct drm_file*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_surfaces_release(struct drm_file *file_priv,
				    drm_radeon_private_t * dev_priv)
{
	int i;
	for (i = 0; i < 2 * RADEON_MAX_SURFACES; i++) {
		if (dev_priv->virt_surfaces[i].file_priv == file_priv)
			free_surface(file_priv, dev_priv,
				     dev_priv->virt_surfaces[i].lower);
	}
}