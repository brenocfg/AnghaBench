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
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_MODE_0 ; 
 int /*<<< orphan*/  CM0_PIPELINED_RENDER_FLUSH_DISABLE ; 
 int /*<<< orphan*/  DISP_ARB_CTL ; 
 int DISP_FBC_WM_DIS ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ILK_DISPLAY_CHICKEN1 ; 
 int /*<<< orphan*/  ILK_DISPLAY_CHICKEN2 ; 
 int ILK_DPARBUNIT_CLOCK_GATE_ENABLE ; 
 int ILK_DPARB_GATE ; 
 int ILK_DPFCRUNIT_CLOCK_GATE_DISABLE ; 
 int ILK_DPFCUNIT_CLOCK_GATE_DISABLE ; 
 int ILK_DPFDUNIT_CLOCK_GATE_ENABLE ; 
 int /*<<< orphan*/  ILK_DSPCLK_GATE_D ; 
 int ILK_ELPIN_409_SELECT ; 
 int ILK_FBCQ_DIS ; 
 int ILK_VRHUNIT_CLOCK_GATE_DISABLE ; 
 int ILK_VSDPFD_FULL ; 
 scalar_t__ IS_IRONLAKE_M (struct drm_device*) ; 
 int MARIUNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  PCH_3DCGDIS0 ; 
 int /*<<< orphan*/  PCH_3DCGDIS1 ; 
 int SVSMUNIT_CLOCK_GATE_DISABLE ; 
 int VFMUNIT_CLOCK_GATE_DISABLE ; 
 int /*<<< orphan*/  WM1_LP_ILK ; 
 int /*<<< orphan*/  WM2_LP_ILK ; 
 int /*<<< orphan*/  WM3_LP_ILK ; 
 int /*<<< orphan*/  _3D_CHICKEN2 ; 
 int _3D_CHICKEN2_WM_READ_PIPELINED ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibx_init_clock_gating (struct drm_device*) ; 

__attribute__((used)) static void ironlake_init_clock_gating(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	uint32_t dspclk_gate = ILK_VRHUNIT_CLOCK_GATE_DISABLE;

	/* Required for FBC */
	dspclk_gate |= ILK_DPFCRUNIT_CLOCK_GATE_DISABLE |
		   ILK_DPFCUNIT_CLOCK_GATE_DISABLE |
		   ILK_DPFDUNIT_CLOCK_GATE_ENABLE;

	I915_WRITE(PCH_3DCGDIS0,
		   MARIUNIT_CLOCK_GATE_DISABLE |
		   SVSMUNIT_CLOCK_GATE_DISABLE);
	I915_WRITE(PCH_3DCGDIS1,
		   VFMUNIT_CLOCK_GATE_DISABLE);

	/*
	 * According to the spec the following bits should be set in
	 * order to enable memory self-refresh
	 * The bit 22/21 of 0x42004
	 * The bit 5 of 0x42020
	 * The bit 15 of 0x45000
	 */
	I915_WRITE(ILK_DISPLAY_CHICKEN2,
		   (I915_READ(ILK_DISPLAY_CHICKEN2) |
		    ILK_DPARB_GATE | ILK_VSDPFD_FULL));
	dspclk_gate |= ILK_DPARBUNIT_CLOCK_GATE_ENABLE;
	I915_WRITE(DISP_ARB_CTL,
		   (I915_READ(DISP_ARB_CTL) |
		    DISP_FBC_WM_DIS));
	I915_WRITE(WM3_LP_ILK, 0);
	I915_WRITE(WM2_LP_ILK, 0);
	I915_WRITE(WM1_LP_ILK, 0);

	/*
	 * Based on the document from hardware guys the following bits
	 * should be set unconditionally in order to enable FBC.
	 * The bit 22 of 0x42000
	 * The bit 22 of 0x42004
	 * The bit 7,8,9 of 0x42020.
	 */
	if (IS_IRONLAKE_M(dev)) {
		I915_WRITE(ILK_DISPLAY_CHICKEN1,
			   I915_READ(ILK_DISPLAY_CHICKEN1) |
			   ILK_FBCQ_DIS);
		I915_WRITE(ILK_DISPLAY_CHICKEN2,
			   I915_READ(ILK_DISPLAY_CHICKEN2) |
			   ILK_DPARB_GATE);
	}

	I915_WRITE(ILK_DSPCLK_GATE_D, dspclk_gate);

	I915_WRITE(ILK_DISPLAY_CHICKEN2,
		   I915_READ(ILK_DISPLAY_CHICKEN2) |
		   ILK_ELPIN_409_SELECT);
	I915_WRITE(_3D_CHICKEN2,
		   _3D_CHICKEN2_WM_READ_PIPELINED << 16 |
		   _3D_CHICKEN2_WM_READ_PIPELINED);

	/* WaDisableRenderCachePipelinedFlush */
	I915_WRITE(CACHE_MODE_0,
		   _MASKED_BIT_ENABLE(CM0_PIPELINED_RENDER_FLUSH_DISABLE));

	ibx_init_clock_gating(dev);
}