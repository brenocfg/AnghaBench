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
struct radeon_connector {int /*<<< orphan*/  dac_load_detect; } ;
struct drm_encoder_helper_funcs {int (* detect ) (struct drm_encoder*,struct drm_connector*) ;} ;
struct drm_encoder {struct drm_encoder_helper_funcs* helper_private; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 struct drm_encoder* radeon_best_single_encoder (struct drm_connector*) ; 
 int radeon_connector_analog_encoder_conflict_solve (struct drm_connector*,struct drm_encoder*,int,int) ; 
 int /*<<< orphan*/  radeon_connector_update_scratch_regs (struct drm_connector*,int) ; 
 int stub1 (struct drm_encoder*,struct drm_connector*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 

__attribute__((used)) static enum drm_connector_status
radeon_tv_detect(struct drm_connector *connector, bool force)
{
	struct drm_encoder *encoder;
	struct drm_encoder_helper_funcs *encoder_funcs;
	struct radeon_connector *radeon_connector = to_radeon_connector(connector);
	enum drm_connector_status ret = connector_status_disconnected;

	if (!radeon_connector->dac_load_detect)
		return ret;

	encoder = radeon_best_single_encoder(connector);
	if (!encoder)
		ret = connector_status_disconnected;
	else {
		encoder_funcs = encoder->helper_private;
		ret = encoder_funcs->detect(encoder, connector);
	}
	if (ret == connector_status_connected)
		ret = radeon_connector_analog_encoder_conflict_solve(connector, encoder, ret, false);
	radeon_connector_update_scratch_regs(connector, ret);
	return ret;
}