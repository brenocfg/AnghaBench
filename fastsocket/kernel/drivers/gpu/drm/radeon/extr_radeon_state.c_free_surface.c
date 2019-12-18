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
struct radeon_virt_surface {int lower; size_t surface_index; int upper; struct drm_file* file_priv; } ;
struct drm_file {int dummy; } ;
struct TYPE_6__ {TYPE_1__* surfaces; struct radeon_virt_surface* virt_surfaces; } ;
typedef  TYPE_2__ drm_radeon_private_t ;
struct TYPE_5__ {int lower; int upper; scalar_t__ refcount; scalar_t__ flags; } ;

/* Variables and functions */
 int RADEON_MAX_SURFACES ; 
 int /*<<< orphan*/  radeon_apply_surface_regs (size_t,TYPE_2__*) ; 

__attribute__((used)) static int free_surface(struct drm_file *file_priv,
			drm_radeon_private_t * dev_priv,
			int lower)
{
	struct radeon_virt_surface *s;
	int i;
	/* find the virtual surface */
	for (i = 0; i < 2 * RADEON_MAX_SURFACES; i++) {
		s = &(dev_priv->virt_surfaces[i]);
		if (s->file_priv) {
			if ((lower == s->lower) && (file_priv == s->file_priv))
			{
				if (dev_priv->surfaces[s->surface_index].
				    lower == s->lower)
					dev_priv->surfaces[s->surface_index].
					    lower = s->upper;

				if (dev_priv->surfaces[s->surface_index].
				    upper == s->upper)
					dev_priv->surfaces[s->surface_index].
					    upper = s->lower;

				dev_priv->surfaces[s->surface_index].refcount--;
				if (dev_priv->surfaces[s->surface_index].
				    refcount == 0)
					dev_priv->surfaces[s->surface_index].
					    flags = 0;
				s->file_priv = NULL;
				radeon_apply_surface_regs(s->surface_index,
							  dev_priv);
				return 0;
			}
		}
	}
	return 1;
}