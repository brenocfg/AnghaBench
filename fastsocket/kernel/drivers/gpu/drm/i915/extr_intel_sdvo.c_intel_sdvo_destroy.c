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
struct intel_sdvo_connector {scalar_t__ tv_format; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_property_destroy (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  drm_sysfs_connector_remove (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_sdvo_destroy_enhance_property (struct drm_connector*) ; 
 int /*<<< orphan*/  kfree (struct intel_sdvo_connector*) ; 
 struct intel_sdvo_connector* to_intel_sdvo_connector (struct drm_connector*) ; 

__attribute__((used)) static void intel_sdvo_destroy(struct drm_connector *connector)
{
	struct intel_sdvo_connector *intel_sdvo_connector = to_intel_sdvo_connector(connector);

	if (intel_sdvo_connector->tv_format)
		drm_property_destroy(connector->dev,
				     intel_sdvo_connector->tv_format);

	intel_sdvo_destroy_enhance_property(connector);
	drm_sysfs_connector_remove(connector);
	drm_connector_cleanup(connector);
	kfree(intel_sdvo_connector);
}