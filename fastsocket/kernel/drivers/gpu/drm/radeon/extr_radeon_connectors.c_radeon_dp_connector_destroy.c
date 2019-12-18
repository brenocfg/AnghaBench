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
struct radeon_connector_atom_dig {scalar_t__ dp_i2c_bus; } ;
struct radeon_connector {struct radeon_connector_atom_dig* con_priv; struct radeon_connector_atom_dig* edid; } ;
struct drm_connector {scalar_t__ dp_i2c_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_cleanup (struct radeon_connector_atom_dig*) ; 
 int /*<<< orphan*/  drm_sysfs_connector_remove (struct radeon_connector_atom_dig*) ; 
 int /*<<< orphan*/  kfree (struct radeon_connector_atom_dig*) ; 
 int /*<<< orphan*/  radeon_i2c_destroy (scalar_t__) ; 
 struct radeon_connector* to_radeon_connector (struct radeon_connector_atom_dig*) ; 

__attribute__((used)) static void radeon_dp_connector_destroy(struct drm_connector *connector)
{
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	struct radeon_connector_atom_dig *radeon_dig_connector = radeon_connector->con_priv;

	if (radeon_connector->edid)
		kfree(radeon_connector->edid);
	if (radeon_dig_connector->dp_i2c_bus)
		radeon_i2c_destroy(radeon_dig_connector->dp_i2c_bus);
	kfree(radeon_connector->con_priv);
	drm_sysfs_connector_remove(connector);
	drm_connector_cleanup(connector);
	kfree(connector);
}