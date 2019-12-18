#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct drm_file {int dummy; } ;
struct drm_buffer {int dummy; } ;
struct TYPE_4__ {int have_z_offset; } ;
typedef  TYPE_1__ drm_radeon_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_RING () ; 
 int /*<<< orphan*/  BEGIN_RING (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OUT_RING_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  R200_EMIT_ATF_TFACTOR 222 
#define  R200_EMIT_MATRIX_SELECT_0 221 
#define  R200_EMIT_OUTPUT_VTX_COMP_SEL 220 
#define  R200_EMIT_PP_AFS_0 219 
#define  R200_EMIT_PP_AFS_1 218 
#define  R200_EMIT_PP_CNTL_X 217 
#define  R200_EMIT_PP_CUBIC_FACES_0 216 
#define  R200_EMIT_PP_CUBIC_FACES_1 215 
#define  R200_EMIT_PP_CUBIC_FACES_2 214 
#define  R200_EMIT_PP_CUBIC_FACES_3 213 
#define  R200_EMIT_PP_CUBIC_FACES_4 212 
#define  R200_EMIT_PP_CUBIC_FACES_5 211 
#define  R200_EMIT_PP_CUBIC_OFFSETS_0 210 
#define  R200_EMIT_PP_CUBIC_OFFSETS_1 209 
#define  R200_EMIT_PP_CUBIC_OFFSETS_2 208 
#define  R200_EMIT_PP_CUBIC_OFFSETS_3 207 
#define  R200_EMIT_PP_CUBIC_OFFSETS_4 206 
#define  R200_EMIT_PP_CUBIC_OFFSETS_5 205 
#define  R200_EMIT_PP_TAM_DEBUG3 204 
#define  R200_EMIT_PP_TRI_PERF_CNTL 203 
#define  R200_EMIT_PP_TXCBLEND_0 202 
#define  R200_EMIT_PP_TXCBLEND_1 201 
#define  R200_EMIT_PP_TXCBLEND_2 200 
#define  R200_EMIT_PP_TXCBLEND_3 199 
#define  R200_EMIT_PP_TXCBLEND_4 198 
#define  R200_EMIT_PP_TXCBLEND_5 197 
#define  R200_EMIT_PP_TXCBLEND_6 196 
#define  R200_EMIT_PP_TXCBLEND_7 195 
#define  R200_EMIT_PP_TXCTLALL_0 194 
#define  R200_EMIT_PP_TXCTLALL_1 193 
#define  R200_EMIT_PP_TXCTLALL_2 192 
#define  R200_EMIT_PP_TXCTLALL_3 191 
#define  R200_EMIT_PP_TXCTLALL_4 190 
#define  R200_EMIT_PP_TXCTLALL_5 189 
#define  R200_EMIT_PP_TXFILTER_0 188 
#define  R200_EMIT_PP_TXFILTER_1 187 
#define  R200_EMIT_PP_TXFILTER_2 186 
#define  R200_EMIT_PP_TXFILTER_3 185 
#define  R200_EMIT_PP_TXFILTER_4 184 
#define  R200_EMIT_PP_TXFILTER_5 183 
#define  R200_EMIT_PP_TXOFFSET_0 182 
#define  R200_EMIT_PP_TXOFFSET_1 181 
#define  R200_EMIT_PP_TXOFFSET_2 180 
#define  R200_EMIT_PP_TXOFFSET_3 179 
#define  R200_EMIT_PP_TXOFFSET_4 178 
#define  R200_EMIT_PP_TXOFFSET_5 177 
#define  R200_EMIT_RB3D_BLENDCOLOR 176 
#define  R200_EMIT_RB3D_DEPTHXY_OFFSET 175 
#define  R200_EMIT_RE_AUX_SCISSOR_CNTL 174 
#define  R200_EMIT_RE_POINTSIZE 173 
#define  R200_EMIT_RE_SCISSOR_TL_0 172 
#define  R200_EMIT_RE_SCISSOR_TL_1 171 
#define  R200_EMIT_RE_SCISSOR_TL_2 170 
#define  R200_EMIT_SE_VAP_CNTL_STATUS 169 
#define  R200_EMIT_SE_VTX_STATE_CNTL 168 
#define  R200_EMIT_TCL_INPUT_VTX_VECTOR_ADDR_0 167 
#define  R200_EMIT_TCL_LIGHT_MODEL_CTL_0 166 
#define  R200_EMIT_TCL_POINT_SPRITE_CNTL 165 
#define  R200_EMIT_TCL_UCP_VERT_BLEND_CTL 164 
#define  R200_EMIT_TEX_PROC_CTL_2 163 
#define  R200_EMIT_TFACTOR_0 162 
#define  R200_EMIT_VAP_CTL 161 
#define  R200_EMIT_VAP_PVS_CNTL 160 
#define  R200_EMIT_VTE_CNTL 159 
#define  R200_EMIT_VTX_FMT_0 158 
#define  RADEON_EMIT_PP_BORDER_COLOR_0 157 
#define  RADEON_EMIT_PP_BORDER_COLOR_1 156 
#define  RADEON_EMIT_PP_BORDER_COLOR_2 155 
#define  RADEON_EMIT_PP_CNTL 154 
#define  RADEON_EMIT_PP_CUBIC_FACES_0 153 
#define  RADEON_EMIT_PP_CUBIC_FACES_1 152 
#define  RADEON_EMIT_PP_CUBIC_FACES_2 151 
#define  RADEON_EMIT_PP_CUBIC_OFFSETS_T0 150 
#define  RADEON_EMIT_PP_CUBIC_OFFSETS_T1 149 
#define  RADEON_EMIT_PP_CUBIC_OFFSETS_T2 148 
#define  RADEON_EMIT_PP_LUM_MATRIX 147 
#define  RADEON_EMIT_PP_MISC 146 
#define  RADEON_EMIT_PP_ROT_MATRIX_0 145 
#define  RADEON_EMIT_PP_TEX_SIZE_0 144 
#define  RADEON_EMIT_PP_TEX_SIZE_1 143 
#define  RADEON_EMIT_PP_TEX_SIZE_2 142 
#define  RADEON_EMIT_PP_TXFILTER_0 141 
#define  RADEON_EMIT_PP_TXFILTER_1 140 
#define  RADEON_EMIT_PP_TXFILTER_2 139 
#define  RADEON_EMIT_RB3D_COLORPITCH 138 
#define  RADEON_EMIT_RB3D_STENCILREFMASK 137 
#define  RADEON_EMIT_RE_LINE_PATTERN 136 
#define  RADEON_EMIT_RE_MISC 135 
#define  RADEON_EMIT_SE_CNTL 134 
#define  RADEON_EMIT_SE_CNTL_STATUS 133 
#define  RADEON_EMIT_SE_LINE_WIDTH 132 
#define  RADEON_EMIT_SE_TCL_MATERIAL_EMMISSIVE_RED 131 
#define  RADEON_EMIT_SE_TCL_OUTPUT_VTX_FMT 130 
#define  RADEON_EMIT_SE_VPORT_XSCALE 129 
#define  RADEON_EMIT_SE_ZBIAS_FACTOR 128 
 int RADEON_PP_CNTL ; 
 int RADEON_PP_MISC ; 
 int RADEON_PP_TXFILTER_0 ; 
 int RADEON_PP_TXOFFSET_0 ; 
 int RADEON_RB3D_COLOROFFSET ; 
 int RADEON_RB3D_DEPTHOFFSET ; 
 int /*<<< orphan*/  RADEON_SE_TCL_STATE_FLUSH ; 
 int /*<<< orphan*/  RING_LOCALS ; 
 int /*<<< orphan*/ * drm_buffer_pointer_to_dword (struct drm_buffer*,int) ; 
 int /*<<< orphan*/  radeon_check_and_fixup_offset (TYPE_1__*,struct drm_file*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ int radeon_check_and_fixup_packets(drm_radeon_private_t *
						     dev_priv,
						     struct drm_file *file_priv,
						     int id, struct drm_buffer *buf)
{
	u32 *data;
	switch (id) {

	case RADEON_EMIT_PP_MISC:
		data = drm_buffer_pointer_to_dword(buf,
			(RADEON_RB3D_DEPTHOFFSET - RADEON_PP_MISC) / 4);

		if (radeon_check_and_fixup_offset(dev_priv, file_priv, data)) {
			DRM_ERROR("Invalid depth buffer offset\n");
			return -EINVAL;
		}
		dev_priv->have_z_offset = 1;
		break;

	case RADEON_EMIT_PP_CNTL:
		data = drm_buffer_pointer_to_dword(buf,
			(RADEON_RB3D_COLOROFFSET - RADEON_PP_CNTL) / 4);

		if (radeon_check_and_fixup_offset(dev_priv, file_priv, data)) {
			DRM_ERROR("Invalid colour buffer offset\n");
			return -EINVAL;
		}
		break;

	case R200_EMIT_PP_TXOFFSET_0:
	case R200_EMIT_PP_TXOFFSET_1:
	case R200_EMIT_PP_TXOFFSET_2:
	case R200_EMIT_PP_TXOFFSET_3:
	case R200_EMIT_PP_TXOFFSET_4:
	case R200_EMIT_PP_TXOFFSET_5:
		data = drm_buffer_pointer_to_dword(buf, 0);
		if (radeon_check_and_fixup_offset(dev_priv, file_priv, data)) {
			DRM_ERROR("Invalid R200 texture offset\n");
			return -EINVAL;
		}
		break;

	case RADEON_EMIT_PP_TXFILTER_0:
	case RADEON_EMIT_PP_TXFILTER_1:
	case RADEON_EMIT_PP_TXFILTER_2:
		data = drm_buffer_pointer_to_dword(buf,
			(RADEON_PP_TXOFFSET_0 - RADEON_PP_TXFILTER_0) / 4);
		if (radeon_check_and_fixup_offset(dev_priv, file_priv, data)) {
			DRM_ERROR("Invalid R100 texture offset\n");
			return -EINVAL;
		}
		break;

	case R200_EMIT_PP_CUBIC_OFFSETS_0:
	case R200_EMIT_PP_CUBIC_OFFSETS_1:
	case R200_EMIT_PP_CUBIC_OFFSETS_2:
	case R200_EMIT_PP_CUBIC_OFFSETS_3:
	case R200_EMIT_PP_CUBIC_OFFSETS_4:
	case R200_EMIT_PP_CUBIC_OFFSETS_5:{
			int i;
			for (i = 0; i < 5; i++) {
				data = drm_buffer_pointer_to_dword(buf, i);
				if (radeon_check_and_fixup_offset(dev_priv,
								  file_priv,
								  data)) {
					DRM_ERROR
					    ("Invalid R200 cubic texture offset\n");
					return -EINVAL;
				}
			}
			break;
		}

	case RADEON_EMIT_PP_CUBIC_OFFSETS_T0:
	case RADEON_EMIT_PP_CUBIC_OFFSETS_T1:
	case RADEON_EMIT_PP_CUBIC_OFFSETS_T2:{
			int i;
			for (i = 0; i < 5; i++) {
				data = drm_buffer_pointer_to_dword(buf, i);
				if (radeon_check_and_fixup_offset(dev_priv,
								  file_priv,
								  data)) {
					DRM_ERROR
					    ("Invalid R100 cubic texture offset\n");
					return -EINVAL;
				}
			}
		}
		break;

	case R200_EMIT_VAP_CTL:{
			RING_LOCALS;
			BEGIN_RING(2);
			OUT_RING_REG(RADEON_SE_TCL_STATE_FLUSH, 0);
			ADVANCE_RING();
		}
		break;

	case RADEON_EMIT_RB3D_COLORPITCH:
	case RADEON_EMIT_RE_LINE_PATTERN:
	case RADEON_EMIT_SE_LINE_WIDTH:
	case RADEON_EMIT_PP_LUM_MATRIX:
	case RADEON_EMIT_PP_ROT_MATRIX_0:
	case RADEON_EMIT_RB3D_STENCILREFMASK:
	case RADEON_EMIT_SE_VPORT_XSCALE:
	case RADEON_EMIT_SE_CNTL:
	case RADEON_EMIT_SE_CNTL_STATUS:
	case RADEON_EMIT_RE_MISC:
	case RADEON_EMIT_PP_BORDER_COLOR_0:
	case RADEON_EMIT_PP_BORDER_COLOR_1:
	case RADEON_EMIT_PP_BORDER_COLOR_2:
	case RADEON_EMIT_SE_ZBIAS_FACTOR:
	case RADEON_EMIT_SE_TCL_OUTPUT_VTX_FMT:
	case RADEON_EMIT_SE_TCL_MATERIAL_EMMISSIVE_RED:
	case R200_EMIT_PP_TXCBLEND_0:
	case R200_EMIT_PP_TXCBLEND_1:
	case R200_EMIT_PP_TXCBLEND_2:
	case R200_EMIT_PP_TXCBLEND_3:
	case R200_EMIT_PP_TXCBLEND_4:
	case R200_EMIT_PP_TXCBLEND_5:
	case R200_EMIT_PP_TXCBLEND_6:
	case R200_EMIT_PP_TXCBLEND_7:
	case R200_EMIT_TCL_LIGHT_MODEL_CTL_0:
	case R200_EMIT_TFACTOR_0:
	case R200_EMIT_VTX_FMT_0:
	case R200_EMIT_MATRIX_SELECT_0:
	case R200_EMIT_TEX_PROC_CTL_2:
	case R200_EMIT_TCL_UCP_VERT_BLEND_CTL:
	case R200_EMIT_PP_TXFILTER_0:
	case R200_EMIT_PP_TXFILTER_1:
	case R200_EMIT_PP_TXFILTER_2:
	case R200_EMIT_PP_TXFILTER_3:
	case R200_EMIT_PP_TXFILTER_4:
	case R200_EMIT_PP_TXFILTER_5:
	case R200_EMIT_VTE_CNTL:
	case R200_EMIT_OUTPUT_VTX_COMP_SEL:
	case R200_EMIT_PP_TAM_DEBUG3:
	case R200_EMIT_PP_CNTL_X:
	case R200_EMIT_RB3D_DEPTHXY_OFFSET:
	case R200_EMIT_RE_AUX_SCISSOR_CNTL:
	case R200_EMIT_RE_SCISSOR_TL_0:
	case R200_EMIT_RE_SCISSOR_TL_1:
	case R200_EMIT_RE_SCISSOR_TL_2:
	case R200_EMIT_SE_VAP_CNTL_STATUS:
	case R200_EMIT_SE_VTX_STATE_CNTL:
	case R200_EMIT_RE_POINTSIZE:
	case R200_EMIT_TCL_INPUT_VTX_VECTOR_ADDR_0:
	case R200_EMIT_PP_CUBIC_FACES_0:
	case R200_EMIT_PP_CUBIC_FACES_1:
	case R200_EMIT_PP_CUBIC_FACES_2:
	case R200_EMIT_PP_CUBIC_FACES_3:
	case R200_EMIT_PP_CUBIC_FACES_4:
	case R200_EMIT_PP_CUBIC_FACES_5:
	case RADEON_EMIT_PP_TEX_SIZE_0:
	case RADEON_EMIT_PP_TEX_SIZE_1:
	case RADEON_EMIT_PP_TEX_SIZE_2:
	case R200_EMIT_RB3D_BLENDCOLOR:
	case R200_EMIT_TCL_POINT_SPRITE_CNTL:
	case RADEON_EMIT_PP_CUBIC_FACES_0:
	case RADEON_EMIT_PP_CUBIC_FACES_1:
	case RADEON_EMIT_PP_CUBIC_FACES_2:
	case R200_EMIT_PP_TRI_PERF_CNTL:
	case R200_EMIT_PP_AFS_0:
	case R200_EMIT_PP_AFS_1:
	case R200_EMIT_ATF_TFACTOR:
	case R200_EMIT_PP_TXCTLALL_0:
	case R200_EMIT_PP_TXCTLALL_1:
	case R200_EMIT_PP_TXCTLALL_2:
	case R200_EMIT_PP_TXCTLALL_3:
	case R200_EMIT_PP_TXCTLALL_4:
	case R200_EMIT_PP_TXCTLALL_5:
	case R200_EMIT_VAP_PVS_CNTL:
		/* These packets don't contain memory offsets */
		break;

	default:
		DRM_ERROR("Unknown state packet ID %d\n", id);
		return -EINVAL;
	}

	return 0;
}