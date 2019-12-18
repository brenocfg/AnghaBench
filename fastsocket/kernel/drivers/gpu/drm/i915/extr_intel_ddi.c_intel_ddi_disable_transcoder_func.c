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
typedef  int uint32_t ;
struct drm_i915_private {int dummy; } ;
typedef  enum transcoder { ____Placeholder_transcoder } transcoder ;

/* Variables and functions */
 int I915_READ (int) ; 
 int /*<<< orphan*/  I915_WRITE (int,int) ; 
 int TRANS_DDI_FUNC_CTL (int) ; 
 int TRANS_DDI_FUNC_ENABLE ; 
 int TRANS_DDI_PORT_MASK ; 
 int TRANS_DDI_PORT_NONE ; 

void intel_ddi_disable_transcoder_func(struct drm_i915_private *dev_priv,
				       enum transcoder cpu_transcoder)
{
	uint32_t reg = TRANS_DDI_FUNC_CTL(cpu_transcoder);
	uint32_t val = I915_READ(reg);

	val &= ~(TRANS_DDI_FUNC_ENABLE | TRANS_DDI_PORT_MASK);
	val |= TRANS_DDI_PORT_NONE;
	I915_WRITE(reg, val);
}