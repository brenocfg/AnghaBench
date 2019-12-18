#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct drm_crtc* crtc; } ;
struct intel_encoder {int (* get_hw_state ) (struct intel_encoder*,int*) ;TYPE_2__ base; int /*<<< orphan*/  connectors_active; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {scalar_t__ dpms; TYPE_2__* encoder; TYPE_1__ base; } ;
struct intel_connector {TYPE_4__ base; struct intel_encoder* encoder; scalar_t__ (* get_hw_state ) (struct intel_connector*) ;} ;
struct drm_crtc {int /*<<< orphan*/  enabled; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;
struct TYPE_7__ {int pipe; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  drm_get_connector_name (TYPE_4__*) ; 
 scalar_t__ stub1 (struct intel_connector*) ; 
 int stub2 (struct intel_encoder*,int*) ; 
 TYPE_3__* to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void intel_connector_check_state(struct intel_connector *connector)
{
	if (connector->get_hw_state(connector)) {
		struct intel_encoder *encoder = connector->encoder;
		struct drm_crtc *crtc;
		bool encoder_enabled;
		enum pipe pipe;

		DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n",
			      connector->base.base.id,
			      drm_get_connector_name(&connector->base));

		WARN(connector->base.dpms == DRM_MODE_DPMS_OFF,
		     "wrong connector dpms state\n");
		WARN(connector->base.encoder != &encoder->base,
		     "active connector not linked to encoder\n");
		WARN(!encoder->connectors_active,
		     "encoder->connectors_active not set\n");

		encoder_enabled = encoder->get_hw_state(encoder, &pipe);
		WARN(!encoder_enabled, "encoder not enabled\n");
		if (WARN_ON(!encoder->base.crtc))
			return;

		crtc = encoder->base.crtc;

		WARN(!crtc->enabled, "crtc not enabled\n");
		WARN(!to_intel_crtc(crtc)->active, "crtc not active\n");
		WARN(pipe != to_intel_crtc(crtc)->pipe,
		     "encoder active on the wrong pipe\n");
	}
}