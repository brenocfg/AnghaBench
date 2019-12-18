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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct intel_sdvo {int /*<<< orphan*/  attached_output; int /*<<< orphan*/  sdvo_reg; } ;
struct TYPE_2__ {struct drm_crtc* crtc; struct drm_device* dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc {int pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_ON ; 
 scalar_t__ HAS_PCH_IBX (struct drm_device*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int PIPE_B ; 
 scalar_t__ SDVO_CMD_STATUS_SUCCESS ; 
 int SDVO_ENABLE ; 
 int /*<<< orphan*/  SDVO_NAME (struct intel_sdvo*) ; 
 int SDVO_PIPE_B_SELECT ; 
 scalar_t__ intel_sdvo_get_trained_inputs (struct intel_sdvo*,int*,int*) ; 
 int /*<<< orphan*/  intel_sdvo_set_active_outputs (struct intel_sdvo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_sdvo_set_encoder_power_state (struct intel_sdvo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_sdvo_write_sdvox (struct intel_sdvo*,int) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_device*,int) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 struct intel_sdvo* to_intel_sdvo (TYPE_1__*) ; 

__attribute__((used)) static void intel_enable_sdvo(struct intel_encoder *encoder)
{
	struct drm_device *dev = encoder->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_sdvo *intel_sdvo = to_intel_sdvo(&encoder->base);
	struct intel_crtc *intel_crtc = to_intel_crtc(encoder->base.crtc);
	u32 temp;
	bool input1, input2;
	int i;
	u8 status;

	temp = I915_READ(intel_sdvo->sdvo_reg);
	if ((temp & SDVO_ENABLE) == 0) {
		/* HW workaround for IBX, we need to move the port
		 * to transcoder A before disabling it. */
		if (HAS_PCH_IBX(dev)) {
			struct drm_crtc *crtc = encoder->base.crtc;
			int pipe = crtc ? to_intel_crtc(crtc)->pipe : -1;

			/* Restore the transcoder select bit. */
			if (pipe == PIPE_B)
				temp |= SDVO_PIPE_B_SELECT;
		}

		intel_sdvo_write_sdvox(intel_sdvo, temp | SDVO_ENABLE);
	}
	for (i = 0; i < 2; i++)
		intel_wait_for_vblank(dev, intel_crtc->pipe);

	status = intel_sdvo_get_trained_inputs(intel_sdvo, &input1, &input2);
	/* Warn if the device reported failure to sync.
	 * A lot of SDVO devices fail to notify of sync, but it's
	 * a given it the status is a success, we succeeded.
	 */
	if (status == SDVO_CMD_STATUS_SUCCESS && !input1) {
		DRM_DEBUG_KMS("First %s output reported failure to "
				"sync\n", SDVO_NAME(intel_sdvo));
	}

	if (0)
		intel_sdvo_set_encoder_power_state(intel_sdvo,
						   DRM_MODE_DPMS_ON);
	intel_sdvo_set_active_outputs(intel_sdvo, intel_sdvo->attached_output);
}