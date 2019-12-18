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
struct intel_sdvo_connector {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  probed_modes; } ;

/* Variables and functions */
 scalar_t__ IS_LVDS (struct intel_sdvo_connector*) ; 
 scalar_t__ IS_TV (struct intel_sdvo_connector*) ; 
 int /*<<< orphan*/  intel_sdvo_get_ddc_modes (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_sdvo_get_lvds_modes (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_sdvo_get_tv_modes (struct drm_connector*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct intel_sdvo_connector* to_intel_sdvo_connector (struct drm_connector*) ; 

__attribute__((used)) static int intel_sdvo_get_modes(struct drm_connector *connector)
{
	struct intel_sdvo_connector *intel_sdvo_connector = to_intel_sdvo_connector(connector);

	if (IS_TV(intel_sdvo_connector))
		intel_sdvo_get_tv_modes(connector);
	else if (IS_LVDS(intel_sdvo_connector))
		intel_sdvo_get_lvds_modes(connector);
	else
		intel_sdvo_get_ddc_modes(connector);

	return !list_empty(&connector->probed_modes);
}