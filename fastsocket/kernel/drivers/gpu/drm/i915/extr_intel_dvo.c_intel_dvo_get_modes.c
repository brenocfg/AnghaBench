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
struct intel_dvo {int /*<<< orphan*/ * panel_fixed_mode; } ;
struct drm_i915_private {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct drm_connector {TYPE_1__* dev; int /*<<< orphan*/  probed_modes; } ;
struct TYPE_2__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMBUS_PORT_DPC ; 
 struct drm_display_mode* drm_mode_duplicate (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 struct intel_dvo* intel_attached_dvo (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_ddc_get_modes (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_gmbus_get_adapter (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_dvo_get_modes(struct drm_connector *connector)
{
	struct intel_dvo *intel_dvo = intel_attached_dvo(connector);
	struct drm_i915_private *dev_priv = connector->dev->dev_private;

	/* We should probably have an i2c driver get_modes function for those
	 * devices which will have a fixed set of modes determined by the chip
	 * (TV-out, for example), but for now with just TMDS and LVDS,
	 * that's not the case.
	 */
	intel_ddc_get_modes(connector,
			    intel_gmbus_get_adapter(dev_priv, GMBUS_PORT_DPC));
	if (!list_empty(&connector->probed_modes))
		return 1;

	if (intel_dvo->panel_fixed_mode != NULL) {
		struct drm_display_mode *mode;
		mode = drm_mode_duplicate(connector->dev, intel_dvo->panel_fixed_mode);
		if (mode) {
			drm_mode_probed_add(connector, mode);
			return 1;
		}
	}

	return 0;
}