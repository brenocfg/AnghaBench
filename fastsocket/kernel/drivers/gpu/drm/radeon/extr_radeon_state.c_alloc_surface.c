#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct radeon_virt_surface {int surface_index; int lower; int upper; scalar_t__ flags; struct drm_file* file_priv; } ;
struct drm_file {int dummy; } ;
struct TYPE_8__ {int address; int size; scalar_t__ flags; } ;
typedef  TYPE_2__ drm_radeon_surface_alloc_t ;
struct TYPE_9__ {TYPE_1__* surfaces; struct radeon_virt_surface* virt_surfaces; } ;
typedef  TYPE_3__ drm_radeon_private_t ;
struct TYPE_7__ {int refcount; int lower; int upper; scalar_t__ flags; } ;

/* Variables and functions */
 int RADEON_MAX_SURFACES ; 
 int RADEON_SURF_ADDRESS_FIXED_MASK ; 
 int /*<<< orphan*/  radeon_apply_surface_regs (int,TYPE_3__*) ; 

__attribute__((used)) static int alloc_surface(drm_radeon_surface_alloc_t *new,
			 drm_radeon_private_t *dev_priv,
			 struct drm_file *file_priv)
{
	struct radeon_virt_surface *s;
	int i;
	int virt_surface_index;
	uint32_t new_upper, new_lower;

	new_lower = new->address;
	new_upper = new_lower + new->size - 1;

	/* sanity check */
	if ((new_lower >= new_upper) || (new->flags == 0) || (new->size == 0) ||
	    ((new_upper & RADEON_SURF_ADDRESS_FIXED_MASK) !=
	     RADEON_SURF_ADDRESS_FIXED_MASK)
	    || ((new_lower & RADEON_SURF_ADDRESS_FIXED_MASK) != 0))
		return -1;

	/* make sure there is no overlap with existing surfaces */
	for (i = 0; i < RADEON_MAX_SURFACES; i++) {
		if ((dev_priv->surfaces[i].refcount != 0) &&
		    (((new_lower >= dev_priv->surfaces[i].lower) &&
		      (new_lower < dev_priv->surfaces[i].upper)) ||
		     ((new_lower < dev_priv->surfaces[i].lower) &&
		      (new_upper > dev_priv->surfaces[i].lower)))) {
			return -1;
		}
	}

	/* find a virtual surface */
	for (i = 0; i < 2 * RADEON_MAX_SURFACES; i++)
		if (dev_priv->virt_surfaces[i].file_priv == NULL)
			break;
	if (i == 2 * RADEON_MAX_SURFACES) {
		return -1;
	}
	virt_surface_index = i;

	/* try to reuse an existing surface */
	for (i = 0; i < RADEON_MAX_SURFACES; i++) {
		/* extend before */
		if ((dev_priv->surfaces[i].refcount == 1) &&
		    (new->flags == dev_priv->surfaces[i].flags) &&
		    (new_upper + 1 == dev_priv->surfaces[i].lower)) {
			s = &(dev_priv->virt_surfaces[virt_surface_index]);
			s->surface_index = i;
			s->lower = new_lower;
			s->upper = new_upper;
			s->flags = new->flags;
			s->file_priv = file_priv;
			dev_priv->surfaces[i].refcount++;
			dev_priv->surfaces[i].lower = s->lower;
			radeon_apply_surface_regs(s->surface_index, dev_priv);
			return virt_surface_index;
		}

		/* extend after */
		if ((dev_priv->surfaces[i].refcount == 1) &&
		    (new->flags == dev_priv->surfaces[i].flags) &&
		    (new_lower == dev_priv->surfaces[i].upper + 1)) {
			s = &(dev_priv->virt_surfaces[virt_surface_index]);
			s->surface_index = i;
			s->lower = new_lower;
			s->upper = new_upper;
			s->flags = new->flags;
			s->file_priv = file_priv;
			dev_priv->surfaces[i].refcount++;
			dev_priv->surfaces[i].upper = s->upper;
			radeon_apply_surface_regs(s->surface_index, dev_priv);
			return virt_surface_index;
		}
	}

	/* okay, we need a new one */
	for (i = 0; i < RADEON_MAX_SURFACES; i++) {
		if (dev_priv->surfaces[i].refcount == 0) {
			s = &(dev_priv->virt_surfaces[virt_surface_index]);
			s->surface_index = i;
			s->lower = new_lower;
			s->upper = new_upper;
			s->flags = new->flags;
			s->file_priv = file_priv;
			dev_priv->surfaces[i].refcount = 1;
			dev_priv->surfaces[i].lower = s->lower;
			dev_priv->surfaces[i].upper = s->upper;
			dev_priv->surfaces[i].flags = s->flags;
			radeon_apply_surface_regs(s->surface_index, dev_priv);
			return virt_surface_index;
		}
	}

	/* we didn't find anything */
	return -1;
}