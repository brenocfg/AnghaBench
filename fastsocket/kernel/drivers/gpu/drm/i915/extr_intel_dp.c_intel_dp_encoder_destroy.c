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
struct intel_dp {int /*<<< orphan*/  panel_vdd_work; int /*<<< orphan*/  adapter; } ;
struct intel_digital_port {struct intel_dp dp; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 struct intel_digital_port* enc_to_dig_port (struct drm_encoder*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct drm_device* intel_dp_to_dev (struct intel_dp*) ; 
 int /*<<< orphan*/  ironlake_panel_vdd_off_sync (struct intel_dp*) ; 
 scalar_t__ is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  kfree (struct intel_digital_port*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_dp_encoder_destroy(struct drm_encoder *encoder)
{
	struct intel_digital_port *intel_dig_port = enc_to_dig_port(encoder);
	struct intel_dp *intel_dp = &intel_dig_port->dp;
	struct drm_device *dev = intel_dp_to_dev(intel_dp);

	i2c_del_adapter(&intel_dp->adapter);
	drm_encoder_cleanup(encoder);
	if (is_edp(intel_dp)) {
		cancel_delayed_work_sync(&intel_dp->panel_vdd_work);
		mutex_lock(&dev->mode_config.mutex);
		ironlake_panel_vdd_off_sync(intel_dp);
		mutex_unlock(&dev->mode_config.mutex);
	}
	kfree(intel_dig_port);
}