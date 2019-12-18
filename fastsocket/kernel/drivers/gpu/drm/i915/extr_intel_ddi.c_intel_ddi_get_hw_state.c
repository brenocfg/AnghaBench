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
typedef  int u32 ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DDI_BUF_CTL (int) ; 
 int DDI_BUF_CTL_ENABLE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int PIPE_A ; 
 int PIPE_B ; 
 int PIPE_C ; 
 int PORT_A ; 
 int TRANSCODER_A ; 
 int TRANSCODER_C ; 
 int TRANSCODER_EDP ; 
#define  TRANS_DDI_EDP_INPUT_A_ON 131 
#define  TRANS_DDI_EDP_INPUT_A_ONOFF 130 
#define  TRANS_DDI_EDP_INPUT_B_ONOFF 129 
#define  TRANS_DDI_EDP_INPUT_C_ONOFF 128 
 int TRANS_DDI_EDP_INPUT_MASK ; 
 int /*<<< orphan*/  TRANS_DDI_FUNC_CTL (int) ; 
 int TRANS_DDI_PORT_MASK ; 
 int TRANS_DDI_SELECT_PORT (int) ; 
 int intel_ddi_get_encoder_port (struct intel_encoder*) ; 

bool intel_ddi_get_hw_state(struct intel_encoder *encoder,
			    enum pipe *pipe)
{
	struct drm_device *dev = encoder->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	enum port port = intel_ddi_get_encoder_port(encoder);
	u32 tmp;
	int i;

	tmp = I915_READ(DDI_BUF_CTL(port));

	if (!(tmp & DDI_BUF_CTL_ENABLE))
		return false;

	if (port == PORT_A) {
		tmp = I915_READ(TRANS_DDI_FUNC_CTL(TRANSCODER_EDP));

		switch (tmp & TRANS_DDI_EDP_INPUT_MASK) {
		case TRANS_DDI_EDP_INPUT_A_ON:
		case TRANS_DDI_EDP_INPUT_A_ONOFF:
			*pipe = PIPE_A;
			break;
		case TRANS_DDI_EDP_INPUT_B_ONOFF:
			*pipe = PIPE_B;
			break;
		case TRANS_DDI_EDP_INPUT_C_ONOFF:
			*pipe = PIPE_C;
			break;
		}

		return true;
	} else {
		for (i = TRANSCODER_A; i <= TRANSCODER_C; i++) {
			tmp = I915_READ(TRANS_DDI_FUNC_CTL(i));

			if ((tmp & TRANS_DDI_PORT_MASK)
			    == TRANS_DDI_SELECT_PORT(port)) {
				*pipe = i;
				return true;
			}
		}
	}

	DRM_DEBUG_KMS("No pipe for ddi port %i found\n", port);

	return true;
}