#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_6__ {struct drm_crtc* crtc; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
struct intel_tv {scalar_t__* margin; int /*<<< orphan*/  tv_format; TYPE_2__ base; } ;
struct drm_property {int dummy; } ;
struct TYPE_8__ {struct drm_property* tv_mode_property; struct drm_property* tv_bottom_margin_property; struct drm_property* tv_top_margin_property; struct drm_property* tv_right_margin_property; struct drm_property* tv_left_margin_property; } ;
struct drm_device {TYPE_3__ mode_config; } ;
struct drm_crtc {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  base; struct drm_device* dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (TYPE_4__*) ; 
 int EINVAL ; 
 size_t TV_MARGIN_BOTTOM ; 
 size_t TV_MARGIN_LEFT ; 
 size_t TV_MARGIN_RIGHT ; 
 size_t TV_MARGIN_TOP ; 
 int drm_object_property_set_value (int /*<<< orphan*/ *,struct drm_property*,scalar_t__) ; 
 struct intel_tv* intel_attached_tv (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_crtc_restore_mode (struct drm_crtc*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* tv_modes ; 

__attribute__((used)) static int
intel_tv_set_property(struct drm_connector *connector, struct drm_property *property,
		      uint64_t val)
{
	struct drm_device *dev = connector->dev;
	struct intel_tv *intel_tv = intel_attached_tv(connector);
	struct drm_crtc *crtc = intel_tv->base.base.crtc;
	int ret = 0;
	bool changed = false;

	ret = drm_object_property_set_value(&connector->base, property, val);
	if (ret < 0)
		goto out;

	if (property == dev->mode_config.tv_left_margin_property &&
		intel_tv->margin[TV_MARGIN_LEFT] != val) {
		intel_tv->margin[TV_MARGIN_LEFT] = val;
		changed = true;
	} else if (property == dev->mode_config.tv_right_margin_property &&
		intel_tv->margin[TV_MARGIN_RIGHT] != val) {
		intel_tv->margin[TV_MARGIN_RIGHT] = val;
		changed = true;
	} else if (property == dev->mode_config.tv_top_margin_property &&
		intel_tv->margin[TV_MARGIN_TOP] != val) {
		intel_tv->margin[TV_MARGIN_TOP] = val;
		changed = true;
	} else if (property == dev->mode_config.tv_bottom_margin_property &&
		intel_tv->margin[TV_MARGIN_BOTTOM] != val) {
		intel_tv->margin[TV_MARGIN_BOTTOM] = val;
		changed = true;
	} else if (property == dev->mode_config.tv_mode_property) {
		if (val >= ARRAY_SIZE(tv_modes)) {
			ret = -EINVAL;
			goto out;
		}
		if (!strcmp(intel_tv->tv_format, tv_modes[val].name))
			goto out;

		intel_tv->tv_format = tv_modes[val].name;
		changed = true;
	} else {
		ret = -EINVAL;
		goto out;
	}

	if (changed && crtc)
		intel_crtc_restore_mode(crtc);
out:
	return ret;
}