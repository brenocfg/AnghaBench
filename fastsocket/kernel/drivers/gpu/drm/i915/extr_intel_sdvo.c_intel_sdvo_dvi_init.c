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
struct drm_connector {int polled; int /*<<< orphan*/  connector_type; } ;
struct intel_connector {struct drm_connector base; } ;
struct intel_sdvo_connector {int output_flag; struct intel_connector base; } ;
struct drm_encoder {int /*<<< orphan*/  encoder_type; } ;
struct TYPE_2__ {struct drm_encoder base; } ;
struct intel_sdvo {int controlled_output; int hotplug_active; int is_hdmi; TYPE_1__ base; } ;
struct intel_encoder {int /*<<< orphan*/  (* hot_plug ) (struct intel_encoder*) ;} ;

/* Variables and functions */
 int DRM_CONNECTOR_POLL_CONNECT ; 
 int DRM_CONNECTOR_POLL_DISCONNECT ; 
 int DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DVID ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_HDMIA ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SDVO_OUTPUT_TMDS0 ; 
 int SDVO_OUTPUT_TMDS1 ; 
 int /*<<< orphan*/  intel_sdvo_add_hdmi_properties (struct intel_sdvo*,struct intel_sdvo_connector*) ; 
 int /*<<< orphan*/  intel_sdvo_connector_init (struct intel_sdvo_connector*,struct intel_sdvo*) ; 
 int /*<<< orphan*/  intel_sdvo_enable_hotplug (struct intel_encoder*) ; 
 int intel_sdvo_get_hotplug_support (struct intel_sdvo*) ; 
 scalar_t__ intel_sdvo_is_hdmi_connector (struct intel_sdvo*,int) ; 
 struct intel_sdvo_connector* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct intel_encoder* to_intel_encoder (struct drm_encoder*) ; 

__attribute__((used)) static bool
intel_sdvo_dvi_init(struct intel_sdvo *intel_sdvo, int device)
{
	struct drm_encoder *encoder = &intel_sdvo->base.base;
	struct drm_connector *connector;
	struct intel_encoder *intel_encoder = to_intel_encoder(encoder);
	struct intel_connector *intel_connector;
	struct intel_sdvo_connector *intel_sdvo_connector;

	intel_sdvo_connector = kzalloc(sizeof(struct intel_sdvo_connector), GFP_KERNEL);
	if (!intel_sdvo_connector)
		return false;

	if (device == 0) {
		intel_sdvo->controlled_output |= SDVO_OUTPUT_TMDS0;
		intel_sdvo_connector->output_flag = SDVO_OUTPUT_TMDS0;
	} else if (device == 1) {
		intel_sdvo->controlled_output |= SDVO_OUTPUT_TMDS1;
		intel_sdvo_connector->output_flag = SDVO_OUTPUT_TMDS1;
	}

	intel_connector = &intel_sdvo_connector->base;
	connector = &intel_connector->base;
	if (intel_sdvo_get_hotplug_support(intel_sdvo) &
		intel_sdvo_connector->output_flag) {
		connector->polled = DRM_CONNECTOR_POLL_HPD;
		intel_sdvo->hotplug_active |= intel_sdvo_connector->output_flag;
		/* Some SDVO devices have one-shot hotplug interrupts.
		 * Ensure that they get re-enabled when an interrupt happens.
		 */
		intel_encoder->hot_plug = intel_sdvo_enable_hotplug;
		intel_sdvo_enable_hotplug(intel_encoder);
	} else {
		connector->polled = DRM_CONNECTOR_POLL_CONNECT | DRM_CONNECTOR_POLL_DISCONNECT;
	}
	encoder->encoder_type = DRM_MODE_ENCODER_TMDS;
	connector->connector_type = DRM_MODE_CONNECTOR_DVID;

	if (intel_sdvo_is_hdmi_connector(intel_sdvo, device)) {
		connector->connector_type = DRM_MODE_CONNECTOR_HDMIA;
		intel_sdvo->is_hdmi = true;
	}

	intel_sdvo_connector_init(intel_sdvo_connector, intel_sdvo);
	if (intel_sdvo->is_hdmi)
		intel_sdvo_add_hdmi_properties(intel_sdvo, intel_sdvo_connector);

	return true;
}