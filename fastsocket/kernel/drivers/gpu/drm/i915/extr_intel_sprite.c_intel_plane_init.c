#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct intel_plane {int can_scale; int max_downscale; int pipe; int /*<<< orphan*/  base; int /*<<< orphan*/  get_colorkey; int /*<<< orphan*/  update_colorkey; int /*<<< orphan*/  disable_plane; int /*<<< orphan*/  update_plane; } ;
struct drm_device {int dummy; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* INTEL_INFO (struct drm_device*) ; 
 int /*<<< orphan*/  IS_GEN6 (struct drm_device*) ; 
 int /*<<< orphan*/  IS_HASWELL (struct drm_device*) ; 
 int /*<<< orphan*/  IS_VALLEYVIEW (struct drm_device*) ; 
 int drm_plane_init (struct drm_device*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  ilk_disable_plane ; 
 int /*<<< orphan*/  ilk_get_colorkey ; 
 int /*<<< orphan*/ * ilk_plane_formats ; 
 int /*<<< orphan*/  ilk_update_colorkey ; 
 int /*<<< orphan*/  ilk_update_plane ; 
 int /*<<< orphan*/  intel_plane_funcs ; 
 int /*<<< orphan*/  ivb_disable_plane ; 
 int /*<<< orphan*/  ivb_get_colorkey ; 
 int /*<<< orphan*/  ivb_update_colorkey ; 
 int /*<<< orphan*/  ivb_update_plane ; 
 int /*<<< orphan*/  kfree (struct intel_plane*) ; 
 struct intel_plane* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * snb_plane_formats ; 

int
intel_plane_init(struct drm_device *dev, enum pipe pipe)
{
	struct intel_plane *intel_plane;
	unsigned long possible_crtcs;
	const uint32_t *plane_formats;
	int num_plane_formats;
	int ret;

	if (INTEL_INFO(dev)->gen < 5)
		return -ENODEV;

	intel_plane = kzalloc(sizeof(struct intel_plane), GFP_KERNEL);
	if (!intel_plane)
		return -ENOMEM;

	switch (INTEL_INFO(dev)->gen) {
	case 5:
	case 6:
		intel_plane->can_scale = true;
		intel_plane->max_downscale = 16;
		intel_plane->update_plane = ilk_update_plane;
		intel_plane->disable_plane = ilk_disable_plane;
		intel_plane->update_colorkey = ilk_update_colorkey;
		intel_plane->get_colorkey = ilk_get_colorkey;

		if (IS_GEN6(dev)) {
			plane_formats = snb_plane_formats;
			num_plane_formats = ARRAY_SIZE(snb_plane_formats);
		} else {
			plane_formats = ilk_plane_formats;
			num_plane_formats = ARRAY_SIZE(ilk_plane_formats);
		}
		break;

	case 7:
		if (IS_HASWELL(dev) || IS_VALLEYVIEW(dev))
			intel_plane->can_scale = false;
		else
			intel_plane->can_scale = true;
		intel_plane->max_downscale = 2;
		intel_plane->update_plane = ivb_update_plane;
		intel_plane->disable_plane = ivb_disable_plane;
		intel_plane->update_colorkey = ivb_update_colorkey;
		intel_plane->get_colorkey = ivb_get_colorkey;

		plane_formats = snb_plane_formats;
		num_plane_formats = ARRAY_SIZE(snb_plane_formats);
		break;

	default:
		kfree(intel_plane);
		return -ENODEV;
	}

	intel_plane->pipe = pipe;
	possible_crtcs = (1 << pipe);
	ret = drm_plane_init(dev, &intel_plane->base, possible_crtcs,
			     &intel_plane_funcs,
			     plane_formats, num_plane_formats,
			     false);
	if (ret)
		kfree(intel_plane);

	return ret;
}