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
typedef  int u32 ;
struct intel_crtc {int fdi_lanes; int ddi_pll_sel; } ;
struct drm_i915_private {int fdi_rx_config; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  DDI_BUF_CTL (int /*<<< orphan*/ ) ; 
 int DDI_BUF_CTL_ENABLE ; 
 int /*<<< orphan*/  DP_TP_CTL (int /*<<< orphan*/ ) ; 
 int DP_TP_CTL_ENABLE ; 
 int DP_TP_CTL_ENHANCED_FRAME_ENABLE ; 
 int DP_TP_CTL_FDI_AUTOTRAIN ; 
 int DP_TP_CTL_LINK_TRAIN_MASK ; 
 int DP_TP_CTL_LINK_TRAIN_NORMAL ; 
 int DP_TP_CTL_LINK_TRAIN_PAT1 ; 
 int /*<<< orphan*/  DP_TP_STATUS (int /*<<< orphan*/ ) ; 
 int DP_TP_STATUS_AUTOTRAIN_DONE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int FDI_LINK_TRAIN_AUTO ; 
 int FDI_PCDCLK ; 
 int FDI_RX_ENABLE ; 
 int FDI_RX_ENHANCE_FRAME_ENABLE ; 
 int FDI_RX_FDI_DELAY_90 ; 
 int FDI_RX_PLL_ENABLE ; 
 int FDI_RX_PWRDN_LANE0_MASK ; 
 int FDI_RX_PWRDN_LANE0_VAL (int) ; 
 int FDI_RX_PWRDN_LANE1_MASK ; 
 int FDI_RX_PWRDN_LANE1_VAL (int) ; 
 int FDI_RX_TP1_TO_TP2_48 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PORT_CLK_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_E ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int TU_SIZE (int) ; 
 int /*<<< orphan*/  _FDI_RXA_CTL ; 
 int /*<<< orphan*/  _FDI_RXA_MISC ; 
 int /*<<< orphan*/  _FDI_RXA_TUSIZE1 ; 
 int* hsw_ddi_buf_ctl_values ; 
 int /*<<< orphan*/  intel_wait_ddi_buf_idle (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  udelay (int) ; 

void hsw_fdi_link_train(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	u32 temp, i, rx_ctl_val;

	/* Set the FDI_RX_MISC pwrdn lanes and the 2 workarounds listed at the
	 * mode set "sequence for CRT port" document:
	 * - TP1 to TP2 time with the default value
	 * - FDI delay to 90h
	 */
	I915_WRITE(_FDI_RXA_MISC, FDI_RX_PWRDN_LANE1_VAL(2) |
				  FDI_RX_PWRDN_LANE0_VAL(2) |
				  FDI_RX_TP1_TO_TP2_48 | FDI_RX_FDI_DELAY_90);

	/* Enable the PCH Receiver FDI PLL */
	rx_ctl_val = dev_priv->fdi_rx_config | FDI_RX_ENHANCE_FRAME_ENABLE |
		     FDI_RX_PLL_ENABLE | ((intel_crtc->fdi_lanes - 1) << 19);
	I915_WRITE(_FDI_RXA_CTL, rx_ctl_val);
	POSTING_READ(_FDI_RXA_CTL);
	udelay(220);

	/* Switch from Rawclk to PCDclk */
	rx_ctl_val |= FDI_PCDCLK;
	I915_WRITE(_FDI_RXA_CTL, rx_ctl_val);

	/* Configure Port Clock Select */
	I915_WRITE(PORT_CLK_SEL(PORT_E), intel_crtc->ddi_pll_sel);

	/* Start the training iterating through available voltages and emphasis,
	 * testing each value twice. */
	for (i = 0; i < ARRAY_SIZE(hsw_ddi_buf_ctl_values) * 2; i++) {
		/* Configure DP_TP_CTL with auto-training */
		I915_WRITE(DP_TP_CTL(PORT_E),
					DP_TP_CTL_FDI_AUTOTRAIN |
					DP_TP_CTL_ENHANCED_FRAME_ENABLE |
					DP_TP_CTL_LINK_TRAIN_PAT1 |
					DP_TP_CTL_ENABLE);

		/* Configure and enable DDI_BUF_CTL for DDI E with next voltage.
		 * DDI E does not support port reversal, the functionality is
		 * achieved on the PCH side in FDI_RX_CTL, so no need to set the
		 * port reversal bit */
		I915_WRITE(DDI_BUF_CTL(PORT_E),
			   DDI_BUF_CTL_ENABLE |
			   ((intel_crtc->fdi_lanes - 1) << 1) |
			   hsw_ddi_buf_ctl_values[i / 2]);
		POSTING_READ(DDI_BUF_CTL(PORT_E));

		udelay(600);

		/* Program PCH FDI Receiver TU */
		I915_WRITE(_FDI_RXA_TUSIZE1, TU_SIZE(64));

		/* Enable PCH FDI Receiver with auto-training */
		rx_ctl_val |= FDI_RX_ENABLE | FDI_LINK_TRAIN_AUTO;
		I915_WRITE(_FDI_RXA_CTL, rx_ctl_val);
		POSTING_READ(_FDI_RXA_CTL);

		/* Wait for FDI receiver lane calibration */
		udelay(30);

		/* Unset FDI_RX_MISC pwrdn lanes */
		temp = I915_READ(_FDI_RXA_MISC);
		temp &= ~(FDI_RX_PWRDN_LANE1_MASK | FDI_RX_PWRDN_LANE0_MASK);
		I915_WRITE(_FDI_RXA_MISC, temp);
		POSTING_READ(_FDI_RXA_MISC);

		/* Wait for FDI auto training time */
		udelay(5);

		temp = I915_READ(DP_TP_STATUS(PORT_E));
		if (temp & DP_TP_STATUS_AUTOTRAIN_DONE) {
			DRM_DEBUG_KMS("FDI link training done on step %d\n", i);

			/* Enable normal pixel sending for FDI */
			I915_WRITE(DP_TP_CTL(PORT_E),
				   DP_TP_CTL_FDI_AUTOTRAIN |
				   DP_TP_CTL_LINK_TRAIN_NORMAL |
				   DP_TP_CTL_ENHANCED_FRAME_ENABLE |
				   DP_TP_CTL_ENABLE);

			return;
		}

		temp = I915_READ(DDI_BUF_CTL(PORT_E));
		temp &= ~DDI_BUF_CTL_ENABLE;
		I915_WRITE(DDI_BUF_CTL(PORT_E), temp);
		POSTING_READ(DDI_BUF_CTL(PORT_E));

		/* Disable DP_TP_CTL and FDI_RX_CTL and retry */
		temp = I915_READ(DP_TP_CTL(PORT_E));
		temp &= ~(DP_TP_CTL_ENABLE | DP_TP_CTL_LINK_TRAIN_MASK);
		temp |= DP_TP_CTL_LINK_TRAIN_PAT1;
		I915_WRITE(DP_TP_CTL(PORT_E), temp);
		POSTING_READ(DP_TP_CTL(PORT_E));

		intel_wait_ddi_buf_idle(dev_priv, PORT_E);

		rx_ctl_val &= ~FDI_RX_ENABLE;
		I915_WRITE(_FDI_RXA_CTL, rx_ctl_val);
		POSTING_READ(_FDI_RXA_CTL);

		/* Reset FDI_RX_MISC pwrdn lanes */
		temp = I915_READ(_FDI_RXA_MISC);
		temp &= ~(FDI_RX_PWRDN_LANE1_MASK | FDI_RX_PWRDN_LANE0_MASK);
		temp |= FDI_RX_PWRDN_LANE1_VAL(2) | FDI_RX_PWRDN_LANE0_VAL(2);
		I915_WRITE(_FDI_RXA_MISC, temp);
		POSTING_READ(_FDI_RXA_MISC);
	}

	DRM_ERROR("FDI link training failed!\n");
}