#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  pp_border_color; int /*<<< orphan*/  pp_tfactor; int /*<<< orphan*/  pp_txablend; int /*<<< orphan*/  pp_txcblend; int /*<<< orphan*/  pp_txoffset; int /*<<< orphan*/  pp_txformat; int /*<<< orphan*/  pp_txfilter; } ;
typedef  TYPE_1__ drm_radeon_texture_regs_t ;
typedef  int /*<<< orphan*/  drm_radeon_private_t ;
struct TYPE_6__ {int /*<<< orphan*/  re_misc; int /*<<< orphan*/  se_cntl_status; int /*<<< orphan*/  se_cntl; int /*<<< orphan*/  se_vport_zoffset; int /*<<< orphan*/  se_vport_zscale; int /*<<< orphan*/  se_vport_yoffset; int /*<<< orphan*/  se_vport_yscale; int /*<<< orphan*/  se_vport_xoffset; int /*<<< orphan*/  se_vport_xscale; int /*<<< orphan*/  rb3d_planemask; int /*<<< orphan*/  rb3d_ropcntl; int /*<<< orphan*/  rb3d_stencilrefmask; int /*<<< orphan*/  pp_rot_matrix_1; int /*<<< orphan*/  pp_rot_matrix_0; int /*<<< orphan*/  pp_lum_matrix; int /*<<< orphan*/  se_line_width; int /*<<< orphan*/  re_line_state; int /*<<< orphan*/  re_line_pattern; int /*<<< orphan*/  se_coord_fmt; int /*<<< orphan*/  rb3d_colorpitch; int /*<<< orphan*/  rb3d_coloroffset; int /*<<< orphan*/  rb3d_cntl; int /*<<< orphan*/  pp_cntl; int /*<<< orphan*/  rb3d_zstencilcntl; int /*<<< orphan*/  rb3d_depthpitch; int /*<<< orphan*/  rb3d_depthoffset; int /*<<< orphan*/  rb3d_blendcntl; int /*<<< orphan*/  re_solid_color; int /*<<< orphan*/  pp_fog_color; int /*<<< orphan*/  pp_misc; } ;
typedef  TYPE_2__ drm_radeon_context_regs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  CP_PACKET0 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,unsigned int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUT_RING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_PP_BORDER_COLOR_0 ; 
 int /*<<< orphan*/  RADEON_PP_BORDER_COLOR_1 ; 
 int /*<<< orphan*/  RADEON_PP_BORDER_COLOR_2 ; 
 int /*<<< orphan*/  RADEON_PP_CNTL ; 
 int /*<<< orphan*/  RADEON_PP_LUM_MATRIX ; 
 int /*<<< orphan*/  RADEON_PP_MISC ; 
 int /*<<< orphan*/  RADEON_PP_ROT_MATRIX_0 ; 
 int /*<<< orphan*/  RADEON_PP_TXFILTER_0 ; 
 int /*<<< orphan*/  RADEON_PP_TXFILTER_1 ; 
 int /*<<< orphan*/  RADEON_PP_TXFILTER_2 ; 
 int /*<<< orphan*/  RADEON_RB3D_COLORPITCH ; 
 int /*<<< orphan*/  RADEON_RB3D_STENCILREFMASK ; 
 int /*<<< orphan*/  RADEON_RE_LINE_PATTERN ; 
 int /*<<< orphan*/  RADEON_RE_MISC ; 
 int /*<<< orphan*/  RADEON_SE_CNTL ; 
 int /*<<< orphan*/  RADEON_SE_CNTL_STATUS ; 
 int /*<<< orphan*/  RADEON_SE_COORD_FMT ; 
 int /*<<< orphan*/  RADEON_SE_LINE_WIDTH ; 
 int /*<<< orphan*/  RADEON_SE_VPORT_XSCALE ; 
 unsigned int RADEON_UPLOAD_BUMPMAP ; 
 unsigned int RADEON_UPLOAD_CONTEXT ; 
 unsigned int RADEON_UPLOAD_LINE ; 
 unsigned int RADEON_UPLOAD_MASKS ; 
 unsigned int RADEON_UPLOAD_MISC ; 
 unsigned int RADEON_UPLOAD_SETUP ; 
 unsigned int RADEON_UPLOAD_TEX0 ; 
 unsigned int RADEON_UPLOAD_TEX1 ; 
 unsigned int RADEON_UPLOAD_TEX2 ; 
 unsigned int RADEON_UPLOAD_VERTFMT ; 
 unsigned int RADEON_UPLOAD_VIEWPORT ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 scalar_t__ radeon_check_and_fixup_offset (int /*<<< orphan*/ *,struct drm_file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int radeon_emit_state(drm_radeon_private_t * dev_priv,
			     struct drm_file *file_priv,
			     drm_radeon_context_regs_t * ctx,
			     drm_radeon_texture_regs_t * tex,
			     unsigned int dirty)
{
	RING_LOCALS;
	DRM_DEBUG("dirty=0x%08x\n", dirty);

	if (dirty & RADEON_UPLOAD_CONTEXT) {
		if (radeon_check_and_fixup_offset(dev_priv, file_priv,
						  &ctx->rb3d_depthoffset)) {
			DRM_ERROR("Invalid depth buffer offset\n");
			return -EINVAL;
		}

		if (radeon_check_and_fixup_offset(dev_priv, file_priv,
						  &ctx->rb3d_coloroffset)) {
			DRM_ERROR("Invalid depth buffer offset\n");
			return -EINVAL;
		}

		BEGIN_RING(14);
		OUT_RING(CP_PACKET0(RADEON_PP_MISC, 6));
		OUT_RING(ctx->pp_misc);
		OUT_RING(ctx->pp_fog_color);
		OUT_RING(ctx->re_solid_color);
		OUT_RING(ctx->rb3d_blendcntl);
		OUT_RING(ctx->rb3d_depthoffset);
		OUT_RING(ctx->rb3d_depthpitch);
		OUT_RING(ctx->rb3d_zstencilcntl);
		OUT_RING(CP_PACKET0(RADEON_PP_CNTL, 2));
		OUT_RING(ctx->pp_cntl);
		OUT_RING(ctx->rb3d_cntl);
		OUT_RING(ctx->rb3d_coloroffset);
		OUT_RING(CP_PACKET0(RADEON_RB3D_COLORPITCH, 0));
		OUT_RING(ctx->rb3d_colorpitch);
		ADVANCE_RING();
	}

	if (dirty & RADEON_UPLOAD_VERTFMT) {
		BEGIN_RING(2);
		OUT_RING(CP_PACKET0(RADEON_SE_COORD_FMT, 0));
		OUT_RING(ctx->se_coord_fmt);
		ADVANCE_RING();
	}

	if (dirty & RADEON_UPLOAD_LINE) {
		BEGIN_RING(5);
		OUT_RING(CP_PACKET0(RADEON_RE_LINE_PATTERN, 1));
		OUT_RING(ctx->re_line_pattern);
		OUT_RING(ctx->re_line_state);
		OUT_RING(CP_PACKET0(RADEON_SE_LINE_WIDTH, 0));
		OUT_RING(ctx->se_line_width);
		ADVANCE_RING();
	}

	if (dirty & RADEON_UPLOAD_BUMPMAP) {
		BEGIN_RING(5);
		OUT_RING(CP_PACKET0(RADEON_PP_LUM_MATRIX, 0));
		OUT_RING(ctx->pp_lum_matrix);
		OUT_RING(CP_PACKET0(RADEON_PP_ROT_MATRIX_0, 1));
		OUT_RING(ctx->pp_rot_matrix_0);
		OUT_RING(ctx->pp_rot_matrix_1);
		ADVANCE_RING();
	}

	if (dirty & RADEON_UPLOAD_MASKS) {
		BEGIN_RING(4);
		OUT_RING(CP_PACKET0(RADEON_RB3D_STENCILREFMASK, 2));
		OUT_RING(ctx->rb3d_stencilrefmask);
		OUT_RING(ctx->rb3d_ropcntl);
		OUT_RING(ctx->rb3d_planemask);
		ADVANCE_RING();
	}

	if (dirty & RADEON_UPLOAD_VIEWPORT) {
		BEGIN_RING(7);
		OUT_RING(CP_PACKET0(RADEON_SE_VPORT_XSCALE, 5));
		OUT_RING(ctx->se_vport_xscale);
		OUT_RING(ctx->se_vport_xoffset);
		OUT_RING(ctx->se_vport_yscale);
		OUT_RING(ctx->se_vport_yoffset);
		OUT_RING(ctx->se_vport_zscale);
		OUT_RING(ctx->se_vport_zoffset);
		ADVANCE_RING();
	}

	if (dirty & RADEON_UPLOAD_SETUP) {
		BEGIN_RING(4);
		OUT_RING(CP_PACKET0(RADEON_SE_CNTL, 0));
		OUT_RING(ctx->se_cntl);
		OUT_RING(CP_PACKET0(RADEON_SE_CNTL_STATUS, 0));
		OUT_RING(ctx->se_cntl_status);
		ADVANCE_RING();
	}

	if (dirty & RADEON_UPLOAD_MISC) {
		BEGIN_RING(2);
		OUT_RING(CP_PACKET0(RADEON_RE_MISC, 0));
		OUT_RING(ctx->re_misc);
		ADVANCE_RING();
	}

	if (dirty & RADEON_UPLOAD_TEX0) {
		if (radeon_check_and_fixup_offset(dev_priv, file_priv,
						  &tex[0].pp_txoffset)) {
			DRM_ERROR("Invalid texture offset for unit 0\n");
			return -EINVAL;
		}

		BEGIN_RING(9);
		OUT_RING(CP_PACKET0(RADEON_PP_TXFILTER_0, 5));
		OUT_RING(tex[0].pp_txfilter);
		OUT_RING(tex[0].pp_txformat);
		OUT_RING(tex[0].pp_txoffset);
		OUT_RING(tex[0].pp_txcblend);
		OUT_RING(tex[0].pp_txablend);
		OUT_RING(tex[0].pp_tfactor);
		OUT_RING(CP_PACKET0(RADEON_PP_BORDER_COLOR_0, 0));
		OUT_RING(tex[0].pp_border_color);
		ADVANCE_RING();
	}

	if (dirty & RADEON_UPLOAD_TEX1) {
		if (radeon_check_and_fixup_offset(dev_priv, file_priv,
						  &tex[1].pp_txoffset)) {
			DRM_ERROR("Invalid texture offset for unit 1\n");
			return -EINVAL;
		}

		BEGIN_RING(9);
		OUT_RING(CP_PACKET0(RADEON_PP_TXFILTER_1, 5));
		OUT_RING(tex[1].pp_txfilter);
		OUT_RING(tex[1].pp_txformat);
		OUT_RING(tex[1].pp_txoffset);
		OUT_RING(tex[1].pp_txcblend);
		OUT_RING(tex[1].pp_txablend);
		OUT_RING(tex[1].pp_tfactor);
		OUT_RING(CP_PACKET0(RADEON_PP_BORDER_COLOR_1, 0));
		OUT_RING(tex[1].pp_border_color);
		ADVANCE_RING();
	}

	if (dirty & RADEON_UPLOAD_TEX2) {
		if (radeon_check_and_fixup_offset(dev_priv, file_priv,
						  &tex[2].pp_txoffset)) {
			DRM_ERROR("Invalid texture offset for unit 2\n");
			return -EINVAL;
		}

		BEGIN_RING(9);
		OUT_RING(CP_PACKET0(RADEON_PP_TXFILTER_2, 5));
		OUT_RING(tex[2].pp_txfilter);
		OUT_RING(tex[2].pp_txformat);
		OUT_RING(tex[2].pp_txoffset);
		OUT_RING(tex[2].pp_txcblend);
		OUT_RING(tex[2].pp_txablend);
		OUT_RING(tex[2].pp_tfactor);
		OUT_RING(CP_PACKET0(RADEON_PP_BORDER_COLOR_2, 0));
		OUT_RING(tex[2].pp_border_color);
		ADVANCE_RING();
	}

	return 0;
}