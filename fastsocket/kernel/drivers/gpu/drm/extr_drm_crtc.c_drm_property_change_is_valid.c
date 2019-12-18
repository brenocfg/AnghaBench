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
typedef  unsigned long long uint64_t ;
struct drm_property {int flags; unsigned long long* values; int num_values; } ;

/* Variables and functions */
 int DRM_MODE_PROP_BITMASK ; 
 int DRM_MODE_PROP_BLOB ; 
 int DRM_MODE_PROP_IMMUTABLE ; 
 int DRM_MODE_PROP_RANGE ; 

__attribute__((used)) static bool drm_property_change_is_valid(struct drm_property *property,
					 uint64_t value)
{
	if (property->flags & DRM_MODE_PROP_IMMUTABLE)
		return false;
	if (property->flags & DRM_MODE_PROP_RANGE) {
		if (value < property->values[0] || value > property->values[1])
			return false;
		return true;
	} else if (property->flags & DRM_MODE_PROP_BITMASK) {
		int i;
		uint64_t valid_mask = 0;
		for (i = 0; i < property->num_values; i++)
			valid_mask |= (1ULL << property->values[i]);
		return !(value & ~valid_mask);
	} else if (property->flags & DRM_MODE_PROP_BLOB) {
		/* Only the driver knows */
		return true;
	} else {
		int i;
		for (i = 0; i < property->num_values; i++)
			if (property->values[i] == value)
				return true;
		return false;
	}
}