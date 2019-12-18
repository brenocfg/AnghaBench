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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_i915_private {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int PORT_A ; 
 int PORT_B ; 
 int /*<<< orphan*/  PORT_CLK_SEL (int) ; 
 int PORT_E ; 
 int TRANSCODER_EDP ; 
 int /*<<< orphan*/  TRANS_DDI_FUNC_CTL (int) ; 
 int /*<<< orphan*/  TRANS_DDI_PORT_MASK ; 
 int /*<<< orphan*/  TRANS_DDI_SELECT_PORT (int) ; 
 int intel_pipe_to_cpu_transcoder (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  pipe_name (int) ; 
 int /*<<< orphan*/  port_name (int) ; 

__attribute__((used)) static uint32_t intel_ddi_get_crtc_pll(struct drm_i915_private *dev_priv,
				       enum pipe pipe)
{
	uint32_t temp, ret;
	enum port port;
	enum transcoder cpu_transcoder = intel_pipe_to_cpu_transcoder(dev_priv,
								      pipe);
	int i;

	if (cpu_transcoder == TRANSCODER_EDP) {
		port = PORT_A;
	} else {
		temp = I915_READ(TRANS_DDI_FUNC_CTL(cpu_transcoder));
		temp &= TRANS_DDI_PORT_MASK;

		for (i = PORT_B; i <= PORT_E; i++)
			if (temp == TRANS_DDI_SELECT_PORT(i))
				port = i;
	}

	ret = I915_READ(PORT_CLK_SEL(port));

	DRM_DEBUG_KMS("Pipe %c connected to port %c using clock 0x%08x\n",
		      pipe_name(pipe), port_name(port), ret);

	return ret;
}