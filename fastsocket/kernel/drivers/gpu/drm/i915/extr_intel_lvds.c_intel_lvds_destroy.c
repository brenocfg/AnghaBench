#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  panel; struct drm_connector* edid; } ;
struct TYPE_4__ {scalar_t__ notifier_call; } ;
struct intel_lvds_connector {TYPE_1__ base; TYPE_2__ lid_notifier; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct drm_connector*) ; 
 int /*<<< orphan*/  acpi_lid_notifier_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_sysfs_connector_remove (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_panel_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct drm_connector*) ; 
 struct intel_lvds_connector* to_lvds_connector (struct drm_connector*) ; 

__attribute__((used)) static void intel_lvds_destroy(struct drm_connector *connector)
{
	struct intel_lvds_connector *lvds_connector =
		to_lvds_connector(connector);

	if (lvds_connector->lid_notifier.notifier_call)
		acpi_lid_notifier_unregister(&lvds_connector->lid_notifier);

	if (!IS_ERR_OR_NULL(lvds_connector->base.edid))
		kfree(lvds_connector->base.edid);

	intel_panel_fini(&lvds_connector->base.panel);

	drm_sysfs_connector_remove(connector);
	drm_connector_cleanup(connector);
	kfree(connector);
}