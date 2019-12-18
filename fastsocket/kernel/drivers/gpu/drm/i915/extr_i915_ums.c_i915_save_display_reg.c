#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* savePIPEB_DP_LINK_N; void* savePIPEA_DP_LINK_N; void* savePIPEB_DP_LINK_M; void* savePIPEA_DP_LINK_M; void* savePIPEB_GMCH_DATA_N; void* savePIPEA_GMCH_DATA_N; void* savePIPEB_GMCH_DATA_M; void* savePIPEA_GMCH_DATA_M; void* saveDP_D; void* saveDP_C; void* saveDP_B; void* saveADPA; void** saveFENCE; void* savePIPEBSTAT; void* saveDSPBTILEOFF; void* saveDSPBSURF; void* saveDSPBADDR; void* saveDSPBPOS; void* saveDSPBSIZE; void* saveDSPBSTRIDE; void* saveDSPBCNTR; void* saveTRANS_VSYNC_B; void* saveTRANS_VBLANK_B; void* saveTRANS_VTOTAL_B; void* saveTRANS_HSYNC_B; void* saveTRANS_HBLANK_B; void* saveTRANS_HTOTAL_B; void* saveTRANSBCONF; void* savePFB_WIN_POS; void* savePFB_WIN_SZ; void* savePFB_CTL_1; void* saveFDI_RXB_CTL; void* saveFDI_TXB_CTL; void* savePIPEB_LINK_N1; void* savePIPEB_LINK_M1; void* savePIPEB_DATA_N1; void* savePIPEB_DATA_M1; void* saveBCLRPAT_B; void* saveVSYNC_B; void* saveVBLANK_B; void* saveVTOTAL_B; void* saveHSYNC_B; void* saveHBLANK_B; void* saveHTOTAL_B; void* saveDPLL_B_MD; void* saveDPLL_B; void* saveFPB1; void* saveFPB0; void* savePIPEBSRC; void* savePIPEBCONF; void* savePIPEASTAT; void* saveDSPATILEOFF; void* saveDSPASURF; void* saveDSPAADDR; void* saveDSPAPOS; void* saveDSPASIZE; void* saveDSPASTRIDE; void* saveDSPACNTR; void* saveTRANS_VSYNC_A; void* saveTRANS_VBLANK_A; void* saveTRANS_VTOTAL_A; void* saveTRANS_HSYNC_A; void* saveTRANS_HBLANK_A; void* saveTRANS_HTOTAL_A; void* saveTRANSACONF; void* savePFA_WIN_POS; void* savePFA_WIN_SZ; void* savePFA_CTL_1; void* saveFDI_RXA_CTL; void* saveFDI_TXA_CTL; void* savePIPEA_LINK_N1; void* savePIPEA_LINK_M1; void* savePIPEA_DATA_N1; void* savePIPEA_DATA_M1; void* saveBCLRPAT_A; void* saveVSYNC_A; void* saveVBLANK_A; void* saveVTOTAL_A; void* saveHSYNC_A; void* saveHBLANK_A; void* saveHTOTAL_A; void* saveDPLL_A_MD; void* saveDPLL_A; void* saveFPA1; void* saveFPA0; void* savePIPEASRC; void* savePIPEACONF; void* saveDISP_ARB_CTL; void* savePCH_DREF_CONTROL; void* saveCURSIZE; void* saveCURBBASE; void* saveCURBPOS; void* saveCURBCNTR; void* saveCURABASE; void* saveCURAPOS; void* saveCURACNTR; } ;
struct drm_i915_private {TYPE_1__ regfile; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_4__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADPA ; 
 int /*<<< orphan*/  CURSIZE ; 
 int /*<<< orphan*/  DISP_ARB_CTL ; 
 int /*<<< orphan*/  DP_B ; 
 int /*<<< orphan*/  DP_C ; 
 int /*<<< orphan*/  DP_D ; 
 int /*<<< orphan*/  FENCE_REG_830_0 ; 
 int /*<<< orphan*/  FENCE_REG_945_8 ; 
 int /*<<< orphan*/  FENCE_REG_965_0 ; 
 int /*<<< orphan*/  FENCE_REG_SANDYBRIDGE_0 ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 void* I915_READ (int /*<<< orphan*/ ) ; 
 void* I915_READ64 (int /*<<< orphan*/ ) ; 
 TYPE_2__* INTEL_INFO (struct drm_device*) ; 
 int /*<<< orphan*/  IS_G33 (struct drm_device*) ; 
 scalar_t__ IS_GEN2 (struct drm_device*) ; 
 int /*<<< orphan*/  IS_I945G (struct drm_device*) ; 
 int /*<<< orphan*/  IS_I945GM (struct drm_device*) ; 
 int /*<<< orphan*/  PCH_ADPA ; 
 int /*<<< orphan*/  PCH_DREF_CONTROL ; 
 int /*<<< orphan*/  PIPE_A ; 
 int /*<<< orphan*/  PIPE_B ; 
 scalar_t__ SUPPORTS_INTEGRATED_DP (struct drm_device*) ; 
 int /*<<< orphan*/  _BCLRPAT_A ; 
 int /*<<< orphan*/  _BCLRPAT_B ; 
 int /*<<< orphan*/  _CURABASE ; 
 int /*<<< orphan*/  _CURACNTR ; 
 int /*<<< orphan*/  _CURAPOS ; 
 int /*<<< orphan*/  _CURBBASE ; 
 int /*<<< orphan*/  _CURBCNTR ; 
 int /*<<< orphan*/  _CURBPOS ; 
 int /*<<< orphan*/  _DPLL_A ; 
 int /*<<< orphan*/  _DPLL_A_MD ; 
 int /*<<< orphan*/  _DPLL_B ; 
 int /*<<< orphan*/  _DPLL_B_MD ; 
 int /*<<< orphan*/  _DSPAADDR ; 
 int /*<<< orphan*/  _DSPACNTR ; 
 int /*<<< orphan*/  _DSPAPOS ; 
 int /*<<< orphan*/  _DSPASIZE ; 
 int /*<<< orphan*/  _DSPASTRIDE ; 
 int /*<<< orphan*/  _DSPASURF ; 
 int /*<<< orphan*/  _DSPATILEOFF ; 
 int /*<<< orphan*/  _DSPBADDR ; 
 int /*<<< orphan*/  _DSPBCNTR ; 
 int /*<<< orphan*/  _DSPBPOS ; 
 int /*<<< orphan*/  _DSPBSIZE ; 
 int /*<<< orphan*/  _DSPBSTRIDE ; 
 int /*<<< orphan*/  _DSPBSURF ; 
 int /*<<< orphan*/  _DSPBTILEOFF ; 
 int /*<<< orphan*/  _FDI_RXA_CTL ; 
 int /*<<< orphan*/  _FDI_RXB_CTL ; 
 int /*<<< orphan*/  _FDI_TXA_CTL ; 
 int /*<<< orphan*/  _FDI_TXB_CTL ; 
 int /*<<< orphan*/  _FPA0 ; 
 int /*<<< orphan*/  _FPA1 ; 
 int /*<<< orphan*/  _FPB0 ; 
 int /*<<< orphan*/  _FPB1 ; 
 int /*<<< orphan*/  _HBLANK_A ; 
 int /*<<< orphan*/  _HBLANK_B ; 
 int /*<<< orphan*/  _HSYNC_A ; 
 int /*<<< orphan*/  _HSYNC_B ; 
 int /*<<< orphan*/  _HTOTAL_A ; 
 int /*<<< orphan*/  _HTOTAL_B ; 
 int /*<<< orphan*/  _PCH_DPLL_A ; 
 int /*<<< orphan*/  _PCH_DPLL_B ; 
 int /*<<< orphan*/  _PCH_FPA0 ; 
 int /*<<< orphan*/  _PCH_FPA1 ; 
 int /*<<< orphan*/  _PCH_FPB0 ; 
 int /*<<< orphan*/  _PCH_FPB1 ; 
 int /*<<< orphan*/  _PFA_CTL_1 ; 
 int /*<<< orphan*/  _PFA_WIN_POS ; 
 int /*<<< orphan*/  _PFA_WIN_SZ ; 
 int /*<<< orphan*/  _PFB_CTL_1 ; 
 int /*<<< orphan*/  _PFB_WIN_POS ; 
 int /*<<< orphan*/  _PFB_WIN_SZ ; 
 int /*<<< orphan*/  _PIPEACONF ; 
 int /*<<< orphan*/  _PIPEASRC ; 
 int /*<<< orphan*/  _PIPEASTAT ; 
 int /*<<< orphan*/  _PIPEA_DATA_M1 ; 
 int /*<<< orphan*/  _PIPEA_DATA_N1 ; 
 int /*<<< orphan*/  _PIPEA_DP_LINK_M ; 
 int /*<<< orphan*/  _PIPEA_DP_LINK_N ; 
 int /*<<< orphan*/  _PIPEA_GMCH_DATA_M ; 
 int /*<<< orphan*/  _PIPEA_GMCH_DATA_N ; 
 int /*<<< orphan*/  _PIPEA_LINK_M1 ; 
 int /*<<< orphan*/  _PIPEA_LINK_N1 ; 
 int /*<<< orphan*/  _PIPEBCONF ; 
 int /*<<< orphan*/  _PIPEBSRC ; 
 int /*<<< orphan*/  _PIPEBSTAT ; 
 int /*<<< orphan*/  _PIPEB_DATA_M1 ; 
 int /*<<< orphan*/  _PIPEB_DATA_N1 ; 
 int /*<<< orphan*/  _PIPEB_DP_LINK_M ; 
 int /*<<< orphan*/  _PIPEB_DP_LINK_N ; 
 int /*<<< orphan*/  _PIPEB_GMCH_DATA_M ; 
 int /*<<< orphan*/  _PIPEB_GMCH_DATA_N ; 
 int /*<<< orphan*/  _PIPEB_LINK_M1 ; 
 int /*<<< orphan*/  _PIPEB_LINK_N1 ; 
 int /*<<< orphan*/  _TRANSACONF ; 
 int /*<<< orphan*/  _TRANSBCONF ; 
 int /*<<< orphan*/  _TRANS_HBLANK_A ; 
 int /*<<< orphan*/  _TRANS_HBLANK_B ; 
 int /*<<< orphan*/  _TRANS_HSYNC_A ; 
 int /*<<< orphan*/  _TRANS_HSYNC_B ; 
 int /*<<< orphan*/  _TRANS_HTOTAL_A ; 
 int /*<<< orphan*/  _TRANS_HTOTAL_B ; 
 int /*<<< orphan*/  _TRANS_VBLANK_A ; 
 int /*<<< orphan*/  _TRANS_VBLANK_B ; 
 int /*<<< orphan*/  _TRANS_VSYNC_A ; 
 int /*<<< orphan*/  _TRANS_VSYNC_B ; 
 int /*<<< orphan*/  _TRANS_VTOTAL_A ; 
 int /*<<< orphan*/  _TRANS_VTOTAL_B ; 
 int /*<<< orphan*/  _VBLANK_A ; 
 int /*<<< orphan*/  _VBLANK_B ; 
 int /*<<< orphan*/  _VSYNC_A ; 
 int /*<<< orphan*/  _VSYNC_B ; 
 int /*<<< orphan*/  _VTOTAL_A ; 
 int /*<<< orphan*/  _VTOTAL_B ; 
 int /*<<< orphan*/  i915_save_palette (struct drm_device*,int /*<<< orphan*/ ) ; 

void i915_save_display_reg(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int i;

	/* Cursor state */
	dev_priv->regfile.saveCURACNTR = I915_READ(_CURACNTR);
	dev_priv->regfile.saveCURAPOS = I915_READ(_CURAPOS);
	dev_priv->regfile.saveCURABASE = I915_READ(_CURABASE);
	dev_priv->regfile.saveCURBCNTR = I915_READ(_CURBCNTR);
	dev_priv->regfile.saveCURBPOS = I915_READ(_CURBPOS);
	dev_priv->regfile.saveCURBBASE = I915_READ(_CURBBASE);
	if (IS_GEN2(dev))
		dev_priv->regfile.saveCURSIZE = I915_READ(CURSIZE);

	if (HAS_PCH_SPLIT(dev)) {
		dev_priv->regfile.savePCH_DREF_CONTROL = I915_READ(PCH_DREF_CONTROL);
		dev_priv->regfile.saveDISP_ARB_CTL = I915_READ(DISP_ARB_CTL);
	}

	/* Pipe & plane A info */
	dev_priv->regfile.savePIPEACONF = I915_READ(_PIPEACONF);
	dev_priv->regfile.savePIPEASRC = I915_READ(_PIPEASRC);
	if (HAS_PCH_SPLIT(dev)) {
		dev_priv->regfile.saveFPA0 = I915_READ(_PCH_FPA0);
		dev_priv->regfile.saveFPA1 = I915_READ(_PCH_FPA1);
		dev_priv->regfile.saveDPLL_A = I915_READ(_PCH_DPLL_A);
	} else {
		dev_priv->regfile.saveFPA0 = I915_READ(_FPA0);
		dev_priv->regfile.saveFPA1 = I915_READ(_FPA1);
		dev_priv->regfile.saveDPLL_A = I915_READ(_DPLL_A);
	}
	if (INTEL_INFO(dev)->gen >= 4 && !HAS_PCH_SPLIT(dev))
		dev_priv->regfile.saveDPLL_A_MD = I915_READ(_DPLL_A_MD);
	dev_priv->regfile.saveHTOTAL_A = I915_READ(_HTOTAL_A);
	dev_priv->regfile.saveHBLANK_A = I915_READ(_HBLANK_A);
	dev_priv->regfile.saveHSYNC_A = I915_READ(_HSYNC_A);
	dev_priv->regfile.saveVTOTAL_A = I915_READ(_VTOTAL_A);
	dev_priv->regfile.saveVBLANK_A = I915_READ(_VBLANK_A);
	dev_priv->regfile.saveVSYNC_A = I915_READ(_VSYNC_A);
	if (!HAS_PCH_SPLIT(dev))
		dev_priv->regfile.saveBCLRPAT_A = I915_READ(_BCLRPAT_A);

	if (HAS_PCH_SPLIT(dev)) {
		dev_priv->regfile.savePIPEA_DATA_M1 = I915_READ(_PIPEA_DATA_M1);
		dev_priv->regfile.savePIPEA_DATA_N1 = I915_READ(_PIPEA_DATA_N1);
		dev_priv->regfile.savePIPEA_LINK_M1 = I915_READ(_PIPEA_LINK_M1);
		dev_priv->regfile.savePIPEA_LINK_N1 = I915_READ(_PIPEA_LINK_N1);

		dev_priv->regfile.saveFDI_TXA_CTL = I915_READ(_FDI_TXA_CTL);
		dev_priv->regfile.saveFDI_RXA_CTL = I915_READ(_FDI_RXA_CTL);

		dev_priv->regfile.savePFA_CTL_1 = I915_READ(_PFA_CTL_1);
		dev_priv->regfile.savePFA_WIN_SZ = I915_READ(_PFA_WIN_SZ);
		dev_priv->regfile.savePFA_WIN_POS = I915_READ(_PFA_WIN_POS);

		dev_priv->regfile.saveTRANSACONF = I915_READ(_TRANSACONF);
		dev_priv->regfile.saveTRANS_HTOTAL_A = I915_READ(_TRANS_HTOTAL_A);
		dev_priv->regfile.saveTRANS_HBLANK_A = I915_READ(_TRANS_HBLANK_A);
		dev_priv->regfile.saveTRANS_HSYNC_A = I915_READ(_TRANS_HSYNC_A);
		dev_priv->regfile.saveTRANS_VTOTAL_A = I915_READ(_TRANS_VTOTAL_A);
		dev_priv->regfile.saveTRANS_VBLANK_A = I915_READ(_TRANS_VBLANK_A);
		dev_priv->regfile.saveTRANS_VSYNC_A = I915_READ(_TRANS_VSYNC_A);
	}

	dev_priv->regfile.saveDSPACNTR = I915_READ(_DSPACNTR);
	dev_priv->regfile.saveDSPASTRIDE = I915_READ(_DSPASTRIDE);
	dev_priv->regfile.saveDSPASIZE = I915_READ(_DSPASIZE);
	dev_priv->regfile.saveDSPAPOS = I915_READ(_DSPAPOS);
	dev_priv->regfile.saveDSPAADDR = I915_READ(_DSPAADDR);
	if (INTEL_INFO(dev)->gen >= 4) {
		dev_priv->regfile.saveDSPASURF = I915_READ(_DSPASURF);
		dev_priv->regfile.saveDSPATILEOFF = I915_READ(_DSPATILEOFF);
	}
	i915_save_palette(dev, PIPE_A);
	dev_priv->regfile.savePIPEASTAT = I915_READ(_PIPEASTAT);

	/* Pipe & plane B info */
	dev_priv->regfile.savePIPEBCONF = I915_READ(_PIPEBCONF);
	dev_priv->regfile.savePIPEBSRC = I915_READ(_PIPEBSRC);
	if (HAS_PCH_SPLIT(dev)) {
		dev_priv->regfile.saveFPB0 = I915_READ(_PCH_FPB0);
		dev_priv->regfile.saveFPB1 = I915_READ(_PCH_FPB1);
		dev_priv->regfile.saveDPLL_B = I915_READ(_PCH_DPLL_B);
	} else {
		dev_priv->regfile.saveFPB0 = I915_READ(_FPB0);
		dev_priv->regfile.saveFPB1 = I915_READ(_FPB1);
		dev_priv->regfile.saveDPLL_B = I915_READ(_DPLL_B);
	}
	if (INTEL_INFO(dev)->gen >= 4 && !HAS_PCH_SPLIT(dev))
		dev_priv->regfile.saveDPLL_B_MD = I915_READ(_DPLL_B_MD);
	dev_priv->regfile.saveHTOTAL_B = I915_READ(_HTOTAL_B);
	dev_priv->regfile.saveHBLANK_B = I915_READ(_HBLANK_B);
	dev_priv->regfile.saveHSYNC_B = I915_READ(_HSYNC_B);
	dev_priv->regfile.saveVTOTAL_B = I915_READ(_VTOTAL_B);
	dev_priv->regfile.saveVBLANK_B = I915_READ(_VBLANK_B);
	dev_priv->regfile.saveVSYNC_B = I915_READ(_VSYNC_B);
	if (!HAS_PCH_SPLIT(dev))
		dev_priv->regfile.saveBCLRPAT_B = I915_READ(_BCLRPAT_B);

	if (HAS_PCH_SPLIT(dev)) {
		dev_priv->regfile.savePIPEB_DATA_M1 = I915_READ(_PIPEB_DATA_M1);
		dev_priv->regfile.savePIPEB_DATA_N1 = I915_READ(_PIPEB_DATA_N1);
		dev_priv->regfile.savePIPEB_LINK_M1 = I915_READ(_PIPEB_LINK_M1);
		dev_priv->regfile.savePIPEB_LINK_N1 = I915_READ(_PIPEB_LINK_N1);

		dev_priv->regfile.saveFDI_TXB_CTL = I915_READ(_FDI_TXB_CTL);
		dev_priv->regfile.saveFDI_RXB_CTL = I915_READ(_FDI_RXB_CTL);

		dev_priv->regfile.savePFB_CTL_1 = I915_READ(_PFB_CTL_1);
		dev_priv->regfile.savePFB_WIN_SZ = I915_READ(_PFB_WIN_SZ);
		dev_priv->regfile.savePFB_WIN_POS = I915_READ(_PFB_WIN_POS);

		dev_priv->regfile.saveTRANSBCONF = I915_READ(_TRANSBCONF);
		dev_priv->regfile.saveTRANS_HTOTAL_B = I915_READ(_TRANS_HTOTAL_B);
		dev_priv->regfile.saveTRANS_HBLANK_B = I915_READ(_TRANS_HBLANK_B);
		dev_priv->regfile.saveTRANS_HSYNC_B = I915_READ(_TRANS_HSYNC_B);
		dev_priv->regfile.saveTRANS_VTOTAL_B = I915_READ(_TRANS_VTOTAL_B);
		dev_priv->regfile.saveTRANS_VBLANK_B = I915_READ(_TRANS_VBLANK_B);
		dev_priv->regfile.saveTRANS_VSYNC_B = I915_READ(_TRANS_VSYNC_B);
	}

	dev_priv->regfile.saveDSPBCNTR = I915_READ(_DSPBCNTR);
	dev_priv->regfile.saveDSPBSTRIDE = I915_READ(_DSPBSTRIDE);
	dev_priv->regfile.saveDSPBSIZE = I915_READ(_DSPBSIZE);
	dev_priv->regfile.saveDSPBPOS = I915_READ(_DSPBPOS);
	dev_priv->regfile.saveDSPBADDR = I915_READ(_DSPBADDR);
	if (INTEL_INFO(dev)->gen >= 4) {
		dev_priv->regfile.saveDSPBSURF = I915_READ(_DSPBSURF);
		dev_priv->regfile.saveDSPBTILEOFF = I915_READ(_DSPBTILEOFF);
	}
	i915_save_palette(dev, PIPE_B);
	dev_priv->regfile.savePIPEBSTAT = I915_READ(_PIPEBSTAT);

	/* Fences */
	switch (INTEL_INFO(dev)->gen) {
	case 7:
	case 6:
		for (i = 0; i < 16; i++)
			dev_priv->regfile.saveFENCE[i] = I915_READ64(FENCE_REG_SANDYBRIDGE_0 + (i * 8));
		break;
	case 5:
	case 4:
		for (i = 0; i < 16; i++)
			dev_priv->regfile.saveFENCE[i] = I915_READ64(FENCE_REG_965_0 + (i * 8));
		break;
	case 3:
		if (IS_I945G(dev) || IS_I945GM(dev) || IS_G33(dev))
			for (i = 0; i < 8; i++)
				dev_priv->regfile.saveFENCE[i+8] = I915_READ(FENCE_REG_945_8 + (i * 4));
	case 2:
		for (i = 0; i < 8; i++)
			dev_priv->regfile.saveFENCE[i] = I915_READ(FENCE_REG_830_0 + (i * 4));
		break;
	}

	/* CRT state */
	if (HAS_PCH_SPLIT(dev))
		dev_priv->regfile.saveADPA = I915_READ(PCH_ADPA);
	else
		dev_priv->regfile.saveADPA = I915_READ(ADPA);

	/* Display Port state */
	if (SUPPORTS_INTEGRATED_DP(dev)) {
		dev_priv->regfile.saveDP_B = I915_READ(DP_B);
		dev_priv->regfile.saveDP_C = I915_READ(DP_C);
		dev_priv->regfile.saveDP_D = I915_READ(DP_D);
		dev_priv->regfile.savePIPEA_GMCH_DATA_M = I915_READ(_PIPEA_GMCH_DATA_M);
		dev_priv->regfile.savePIPEB_GMCH_DATA_M = I915_READ(_PIPEB_GMCH_DATA_M);
		dev_priv->regfile.savePIPEA_GMCH_DATA_N = I915_READ(_PIPEA_GMCH_DATA_N);
		dev_priv->regfile.savePIPEB_GMCH_DATA_N = I915_READ(_PIPEB_GMCH_DATA_N);
		dev_priv->regfile.savePIPEA_DP_LINK_M = I915_READ(_PIPEA_DP_LINK_M);
		dev_priv->regfile.savePIPEB_DP_LINK_M = I915_READ(_PIPEB_DP_LINK_M);
		dev_priv->regfile.savePIPEA_DP_LINK_N = I915_READ(_PIPEA_DP_LINK_N);
		dev_priv->regfile.savePIPEB_DP_LINK_N = I915_READ(_PIPEB_DP_LINK_N);
	}
	/* FIXME: regfile.save TV & SDVO state */

	return;
}