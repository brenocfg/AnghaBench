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
struct nouveau_grctx {int ctxvals_pos; struct nouveau_device* device; } ;
struct nouveau_device {int chipset; } ;

/* Variables and functions */
 scalar_t__ IS_NVA3F (int) ; 
 int /*<<< orphan*/  cp_ctx (struct nouveau_grctx*,int,int) ; 
 int /*<<< orphan*/  dd_emit (struct nouveau_grctx*,int,int) ; 

__attribute__((used)) static void
nv50_graph_construct_mmio_ddata(struct nouveau_grctx *ctx)
{
	struct nouveau_device *device = ctx->device;
	int base, num;
	base = ctx->ctxvals_pos;

	/* tesla state */
	dd_emit(ctx, 1, 0);	/* 00000001 UNK0F90 */
	dd_emit(ctx, 1, 0);	/* 00000001 UNK135C */

	/* SRC_TIC state */
	dd_emit(ctx, 1, 0);	/* 00000007 SRC_TILE_MODE_Z */
	dd_emit(ctx, 1, 2);	/* 00000007 SRC_TILE_MODE_Y */
	dd_emit(ctx, 1, 1);	/* 00000001 SRC_LINEAR #1 */
	dd_emit(ctx, 1, 0);	/* 000000ff SRC_ADDRESS_HIGH */
	dd_emit(ctx, 1, 0);	/* 00000001 SRC_SRGB */
	if (device->chipset >= 0x94)
		dd_emit(ctx, 1, 0);	/* 00000003 eng2d UNK0258 */
	dd_emit(ctx, 1, 1);	/* 00000fff SRC_DEPTH */
	dd_emit(ctx, 1, 0x100);	/* 0000ffff SRC_HEIGHT */

	/* turing state */
	dd_emit(ctx, 1, 0);		/* 0000000f TEXTURES_LOG2 */
	dd_emit(ctx, 1, 0);		/* 0000000f SAMPLERS_LOG2 */
	dd_emit(ctx, 1, 0);		/* 000000ff CB_DEF_ADDRESS_HIGH */
	dd_emit(ctx, 1, 0);		/* ffffffff CB_DEF_ADDRESS_LOW */
	dd_emit(ctx, 1, 0);		/* ffffffff SHARED_SIZE */
	dd_emit(ctx, 1, 2);		/* ffffffff REG_MODE */
	dd_emit(ctx, 1, 1);		/* 0000ffff BLOCK_ALLOC_THREADS */
	dd_emit(ctx, 1, 1);		/* 00000001 LANES32 */
	dd_emit(ctx, 1, 0);		/* 000000ff UNK370 */
	dd_emit(ctx, 1, 0);		/* 000000ff USER_PARAM_UNK */
	dd_emit(ctx, 1, 0);		/* 000000ff USER_PARAM_COUNT */
	dd_emit(ctx, 1, 1);		/* 000000ff UNK384 bits 8-15 */
	dd_emit(ctx, 1, 0x3fffff);	/* 003fffff TIC_LIMIT */
	dd_emit(ctx, 1, 0x1fff);	/* 000fffff TSC_LIMIT */
	dd_emit(ctx, 1, 0);		/* 0000ffff CB_ADDR_INDEX */
	dd_emit(ctx, 1, 1);		/* 000007ff BLOCKDIM_X */
	dd_emit(ctx, 1, 1);		/* 000007ff BLOCKDIM_XMY */
	dd_emit(ctx, 1, 0);		/* 00000001 BLOCKDIM_XMY_OVERFLOW */
	dd_emit(ctx, 1, 1);		/* 0003ffff BLOCKDIM_XMYMZ */
	dd_emit(ctx, 1, 1);		/* 000007ff BLOCKDIM_Y */
	dd_emit(ctx, 1, 1);		/* 0000007f BLOCKDIM_Z */
	dd_emit(ctx, 1, 4);		/* 000000ff CP_REG_ALLOC_TEMP */
	dd_emit(ctx, 1, 1);		/* 00000001 BLOCKDIM_DIRTY */
	if (IS_NVA3F(device->chipset))
		dd_emit(ctx, 1, 0);	/* 00000003 UNK03E8 */
	dd_emit(ctx, 1, 1);		/* 0000007f BLOCK_ALLOC_HALFWARPS */
	dd_emit(ctx, 1, 1);		/* 00000007 LOCAL_WARPS_NO_CLAMP */
	dd_emit(ctx, 1, 7);		/* 00000007 LOCAL_WARPS_LOG_ALLOC */
	dd_emit(ctx, 1, 1);		/* 00000007 STACK_WARPS_NO_CLAMP */
	dd_emit(ctx, 1, 7);		/* 00000007 STACK_WARPS_LOG_ALLOC */
	dd_emit(ctx, 1, 1);		/* 00001fff BLOCK_ALLOC_REGSLOTS_PACKED */
	dd_emit(ctx, 1, 1);		/* 00001fff BLOCK_ALLOC_REGSLOTS_STRIDED */
	dd_emit(ctx, 1, 1);		/* 000007ff BLOCK_ALLOC_THREADS */

	/* compat 2d state */
	if (device->chipset == 0x50) {
		dd_emit(ctx, 4, 0);		/* 0000ffff clip X, Y, W, H */

		dd_emit(ctx, 1, 1);		/* ffffffff chroma COLOR_FORMAT */

		dd_emit(ctx, 1, 1);		/* ffffffff pattern COLOR_FORMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff pattern SHAPE */
		dd_emit(ctx, 1, 1);		/* ffffffff pattern PATTERN_SELECT */

		dd_emit(ctx, 1, 0xa);		/* ffffffff surf2d SRC_FORMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff surf2d DMA_SRC */
		dd_emit(ctx, 1, 0);		/* 000000ff surf2d SRC_ADDRESS_HIGH */
		dd_emit(ctx, 1, 0);		/* ffffffff surf2d SRC_ADDRESS_LOW */
		dd_emit(ctx, 1, 0x40);		/* 0000ffff surf2d SRC_PITCH */
		dd_emit(ctx, 1, 0);		/* 0000000f surf2d SRC_TILE_MODE_Z */
		dd_emit(ctx, 1, 2);		/* 0000000f surf2d SRC_TILE_MODE_Y */
		dd_emit(ctx, 1, 0x100);		/* ffffffff surf2d SRC_HEIGHT */
		dd_emit(ctx, 1, 1);		/* 00000001 surf2d SRC_LINEAR */
		dd_emit(ctx, 1, 0x100);		/* ffffffff surf2d SRC_WIDTH */

		dd_emit(ctx, 1, 0);		/* 0000ffff gdirect CLIP_B_X */
		dd_emit(ctx, 1, 0);		/* 0000ffff gdirect CLIP_B_Y */
		dd_emit(ctx, 1, 0);		/* 0000ffff gdirect CLIP_C_X */
		dd_emit(ctx, 1, 0);		/* 0000ffff gdirect CLIP_C_Y */
		dd_emit(ctx, 1, 0);		/* 0000ffff gdirect CLIP_D_X */
		dd_emit(ctx, 1, 0);		/* 0000ffff gdirect CLIP_D_Y */
		dd_emit(ctx, 1, 1);		/* ffffffff gdirect COLOR_FORMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff gdirect OPERATION */
		dd_emit(ctx, 1, 0);		/* 0000ffff gdirect POINT_X */
		dd_emit(ctx, 1, 0);		/* 0000ffff gdirect POINT_Y */

		dd_emit(ctx, 1, 0);		/* 0000ffff blit SRC_Y */
		dd_emit(ctx, 1, 0);		/* ffffffff blit OPERATION */

		dd_emit(ctx, 1, 0);		/* ffffffff ifc OPERATION */

		dd_emit(ctx, 1, 0);		/* ffffffff iifc INDEX_FORMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff iifc LUT_OFFSET */
		dd_emit(ctx, 1, 4);		/* ffffffff iifc COLOR_FORMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff iifc OPERATION */
	}

	/* m2mf state */
	dd_emit(ctx, 1, 0);		/* ffffffff m2mf LINE_COUNT */
	dd_emit(ctx, 1, 0);		/* ffffffff m2mf LINE_LENGTH_IN */
	dd_emit(ctx, 2, 0);		/* ffffffff m2mf OFFSET_IN, OFFSET_OUT */
	dd_emit(ctx, 1, 1);		/* ffffffff m2mf TILING_DEPTH_OUT */
	dd_emit(ctx, 1, 0x100);		/* ffffffff m2mf TILING_HEIGHT_OUT */
	dd_emit(ctx, 1, 0);		/* ffffffff m2mf TILING_POSITION_OUT_Z */
	dd_emit(ctx, 1, 1);		/* 00000001 m2mf LINEAR_OUT */
	dd_emit(ctx, 2, 0);		/* 0000ffff m2mf TILING_POSITION_OUT_X, Y */
	dd_emit(ctx, 1, 0x100);		/* ffffffff m2mf TILING_PITCH_OUT */
	dd_emit(ctx, 1, 1);		/* ffffffff m2mf TILING_DEPTH_IN */
	dd_emit(ctx, 1, 0x100);		/* ffffffff m2mf TILING_HEIGHT_IN */
	dd_emit(ctx, 1, 0);		/* ffffffff m2mf TILING_POSITION_IN_Z */
	dd_emit(ctx, 1, 1);		/* 00000001 m2mf LINEAR_IN */
	dd_emit(ctx, 2, 0);		/* 0000ffff m2mf TILING_POSITION_IN_X, Y */
	dd_emit(ctx, 1, 0x100);		/* ffffffff m2mf TILING_PITCH_IN */

	/* more compat 2d state */
	if (device->chipset == 0x50) {
		dd_emit(ctx, 1, 1);		/* ffffffff line COLOR_FORMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff line OPERATION */

		dd_emit(ctx, 1, 1);		/* ffffffff triangle COLOR_FORMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff triangle OPERATION */

		dd_emit(ctx, 1, 0);		/* 0000000f sifm TILE_MODE_Z */
		dd_emit(ctx, 1, 2);		/* 0000000f sifm TILE_MODE_Y */
		dd_emit(ctx, 1, 0);		/* 000000ff sifm FORMAT_FILTER */
		dd_emit(ctx, 1, 1);		/* 000000ff sifm FORMAT_ORIGIN */
		dd_emit(ctx, 1, 0);		/* 0000ffff sifm SRC_PITCH */
		dd_emit(ctx, 1, 1);		/* 00000001 sifm SRC_LINEAR */
		dd_emit(ctx, 1, 0);		/* 000000ff sifm SRC_OFFSET_HIGH */
		dd_emit(ctx, 1, 0);		/* ffffffff sifm SRC_OFFSET */
		dd_emit(ctx, 1, 0);		/* 0000ffff sifm SRC_HEIGHT */
		dd_emit(ctx, 1, 0);		/* 0000ffff sifm SRC_WIDTH */
		dd_emit(ctx, 1, 3);		/* ffffffff sifm COLOR_FORMAT */
		dd_emit(ctx, 1, 0);		/* ffffffff sifm OPERATION */

		dd_emit(ctx, 1, 0);		/* ffffffff sifc OPERATION */
	}

	/* tesla state */
	dd_emit(ctx, 1, 0);		/* 0000000f GP_TEXTURES_LOG2 */
	dd_emit(ctx, 1, 0);		/* 0000000f GP_SAMPLERS_LOG2 */
	dd_emit(ctx, 1, 0);		/* 000000ff */
	dd_emit(ctx, 1, 0);		/* ffffffff */
	dd_emit(ctx, 1, 4);		/* 000000ff UNK12B0_0 */
	dd_emit(ctx, 1, 0x70);		/* 000000ff UNK12B0_1 */
	dd_emit(ctx, 1, 0x80);		/* 000000ff UNK12B0_3 */
	dd_emit(ctx, 1, 0);		/* 000000ff UNK12B0_2 */
	dd_emit(ctx, 1, 0);		/* 0000000f FP_TEXTURES_LOG2 */
	dd_emit(ctx, 1, 0);		/* 0000000f FP_SAMPLERS_LOG2 */
	if (IS_NVA3F(device->chipset)) {
		dd_emit(ctx, 1, 0);	/* ffffffff */
		dd_emit(ctx, 1, 0);	/* 0000007f MULTISAMPLE_SAMPLES_LOG2 */
	} else {
		dd_emit(ctx, 1, 0);	/* 0000000f MULTISAMPLE_SAMPLES_LOG2 */
	}
	dd_emit(ctx, 1, 0xc);		/* 000000ff SEMANTIC_COLOR.BFC0_ID */
	if (device->chipset != 0x50)
		dd_emit(ctx, 1, 0);	/* 00000001 SEMANTIC_COLOR.CLMP_EN */
	dd_emit(ctx, 1, 8);		/* 000000ff SEMANTIC_COLOR.COLR_NR */
	dd_emit(ctx, 1, 0x14);		/* 000000ff SEMANTIC_COLOR.FFC0_ID */
	if (device->chipset == 0x50) {
		dd_emit(ctx, 1, 0);	/* 000000ff SEMANTIC_LAYER */
		dd_emit(ctx, 1, 0);	/* 00000001 */
	} else {
		dd_emit(ctx, 1, 0);	/* 00000001 SEMANTIC_PTSZ.ENABLE */
		dd_emit(ctx, 1, 0x29);	/* 000000ff SEMANTIC_PTSZ.PTSZ_ID */
		dd_emit(ctx, 1, 0x27);	/* 000000ff SEMANTIC_PRIM */
		dd_emit(ctx, 1, 0x26);	/* 000000ff SEMANTIC_LAYER */
		dd_emit(ctx, 1, 8);	/* 0000000f SMENATIC_CLIP.CLIP_HIGH */
		dd_emit(ctx, 1, 4);	/* 000000ff SEMANTIC_CLIP.CLIP_LO */
		dd_emit(ctx, 1, 0x27);	/* 000000ff UNK0FD4 */
		dd_emit(ctx, 1, 0);	/* 00000001 UNK1900 */
	}
	dd_emit(ctx, 1, 0);		/* 00000007 RT_CONTROL_MAP0 */
	dd_emit(ctx, 1, 1);		/* 00000007 RT_CONTROL_MAP1 */
	dd_emit(ctx, 1, 2);		/* 00000007 RT_CONTROL_MAP2 */
	dd_emit(ctx, 1, 3);		/* 00000007 RT_CONTROL_MAP3 */
	dd_emit(ctx, 1, 4);		/* 00000007 RT_CONTROL_MAP4 */
	dd_emit(ctx, 1, 5);		/* 00000007 RT_CONTROL_MAP5 */
	dd_emit(ctx, 1, 6);		/* 00000007 RT_CONTROL_MAP6 */
	dd_emit(ctx, 1, 7);		/* 00000007 RT_CONTROL_MAP7 */
	dd_emit(ctx, 1, 1);		/* 0000000f RT_CONTROL_COUNT */
	dd_emit(ctx, 8, 0);		/* 00000001 RT_HORIZ_UNK */
	dd_emit(ctx, 8, 0);		/* ffffffff RT_ADDRESS_LOW */
	dd_emit(ctx, 1, 0xcf);		/* 000000ff RT_FORMAT */
	dd_emit(ctx, 7, 0);		/* 000000ff RT_FORMAT */
	if (device->chipset != 0x50)
		dd_emit(ctx, 3, 0);	/* 1, 1, 1 */
	else
		dd_emit(ctx, 2, 0);	/* 1, 1 */
	dd_emit(ctx, 1, 0);		/* ffffffff GP_ENABLE */
	dd_emit(ctx, 1, 0x80);		/* 0000ffff GP_VERTEX_OUTPUT_COUNT*/
	dd_emit(ctx, 1, 4);		/* 000000ff GP_REG_ALLOC_RESULT */
	dd_emit(ctx, 1, 4);		/* 000000ff GP_RESULT_MAP_SIZE */
	if (IS_NVA3F(device->chipset)) {
		dd_emit(ctx, 1, 3);	/* 00000003 */
		dd_emit(ctx, 1, 0);	/* 00000001 UNK1418. Alone. */
	}
	if (device->chipset != 0x50)
		dd_emit(ctx, 1, 3);	/* 00000003 UNK15AC */
	dd_emit(ctx, 1, 1);		/* ffffffff RASTERIZE_ENABLE */
	dd_emit(ctx, 1, 0);		/* 00000001 FP_CONTROL.EXPORTS_Z */
	if (device->chipset != 0x50)
		dd_emit(ctx, 1, 0);	/* 00000001 FP_CONTROL.MULTIPLE_RESULTS */
	dd_emit(ctx, 1, 0x12);		/* 000000ff FP_INTERPOLANT_CTRL.COUNT */
	dd_emit(ctx, 1, 0x10);		/* 000000ff FP_INTERPOLANT_CTRL.COUNT_NONFLAT */
	dd_emit(ctx, 1, 0xc);		/* 000000ff FP_INTERPOLANT_CTRL.OFFSET */
	dd_emit(ctx, 1, 1);		/* 00000001 FP_INTERPOLANT_CTRL.UMASK.W */
	dd_emit(ctx, 1, 0);		/* 00000001 FP_INTERPOLANT_CTRL.UMASK.X */
	dd_emit(ctx, 1, 0);		/* 00000001 FP_INTERPOLANT_CTRL.UMASK.Y */
	dd_emit(ctx, 1, 0);		/* 00000001 FP_INTERPOLANT_CTRL.UMASK.Z */
	dd_emit(ctx, 1, 4);		/* 000000ff FP_RESULT_COUNT */
	dd_emit(ctx, 1, 2);		/* ffffffff REG_MODE */
	dd_emit(ctx, 1, 4);		/* 000000ff FP_REG_ALLOC_TEMP */
	if (device->chipset >= 0xa0)
		dd_emit(ctx, 1, 0);	/* ffffffff */
	dd_emit(ctx, 1, 0);		/* 00000001 GP_BUILTIN_RESULT_EN.LAYER_IDX */
	dd_emit(ctx, 1, 0);		/* ffffffff STRMOUT_ENABLE */
	dd_emit(ctx, 1, 0x3fffff);	/* 003fffff TIC_LIMIT */
	dd_emit(ctx, 1, 0x1fff);	/* 000fffff TSC_LIMIT */
	dd_emit(ctx, 1, 0);		/* 00000001 VERTEX_TWO_SIDE_ENABLE*/
	if (device->chipset != 0x50)
		dd_emit(ctx, 8, 0);	/* 00000001 */
	if (device->chipset >= 0xa0) {
		dd_emit(ctx, 1, 1);	/* 00000007 VTX_ATTR_DEFINE.COMP */
		dd_emit(ctx, 1, 1);	/* 00000007 VTX_ATTR_DEFINE.SIZE */
		dd_emit(ctx, 1, 2);	/* 00000007 VTX_ATTR_DEFINE.TYPE */
		dd_emit(ctx, 1, 0);	/* 000000ff VTX_ATTR_DEFINE.ATTR */
	}
	dd_emit(ctx, 1, 4);		/* 0000007f VP_RESULT_MAP_SIZE */
	dd_emit(ctx, 1, 0x14);		/* 0000001f ZETA_FORMAT */
	dd_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABLE */
	dd_emit(ctx, 1, 0);		/* 0000000f VP_TEXTURES_LOG2 */
	dd_emit(ctx, 1, 0);		/* 0000000f VP_SAMPLERS_LOG2 */
	if (IS_NVA3F(device->chipset))
		dd_emit(ctx, 1, 0);	/* 00000001 */
	dd_emit(ctx, 1, 2);		/* 00000003 POLYGON_MODE_BACK */
	if (device->chipset >= 0xa0)
		dd_emit(ctx, 1, 0);	/* 00000003 VTX_ATTR_DEFINE.SIZE - 1 */
	dd_emit(ctx, 1, 0);		/* 0000ffff CB_ADDR_INDEX */
	if (device->chipset >= 0xa0)
		dd_emit(ctx, 1, 0);	/* 00000003 */
	dd_emit(ctx, 1, 0);		/* 00000001 CULL_FACE_ENABLE */
	dd_emit(ctx, 1, 1);		/* 00000003 CULL_FACE */
	dd_emit(ctx, 1, 0);		/* 00000001 FRONT_FACE */
	dd_emit(ctx, 1, 2);		/* 00000003 POLYGON_MODE_FRONT */
	dd_emit(ctx, 1, 0x1000);	/* 00007fff UNK141C */
	if (device->chipset != 0x50) {
		dd_emit(ctx, 1, 0xe00);		/* 7fff */
		dd_emit(ctx, 1, 0x1000);	/* 7fff */
		dd_emit(ctx, 1, 0x1e00);	/* 7fff */
	}
	dd_emit(ctx, 1, 0);		/* 00000001 BEGIN_END_ACTIVE */
	dd_emit(ctx, 1, 1);		/* 00000001 POLYGON_MODE_??? */
	dd_emit(ctx, 1, 1);		/* 000000ff GP_REG_ALLOC_TEMP / 4 rounded up */
	dd_emit(ctx, 1, 1);		/* 000000ff FP_REG_ALLOC_TEMP... without /4? */
	dd_emit(ctx, 1, 1);		/* 000000ff VP_REG_ALLOC_TEMP / 4 rounded up */
	dd_emit(ctx, 1, 1);		/* 00000001 */
	dd_emit(ctx, 1, 0);		/* 00000001 */
	dd_emit(ctx, 1, 0);		/* 00000001 VTX_ATTR_MASK_UNK0 nonempty */
	dd_emit(ctx, 1, 0);		/* 00000001 VTX_ATTR_MASK_UNK1 nonempty */
	dd_emit(ctx, 1, 0x200);		/* 0003ffff GP_VERTEX_OUTPUT_COUNT*GP_REG_ALLOC_RESULT */
	if (IS_NVA3F(device->chipset))
		dd_emit(ctx, 1, 0x200);
	dd_emit(ctx, 1, 0);		/* 00000001 */
	if (device->chipset < 0xa0) {
		dd_emit(ctx, 1, 1);	/* 00000001 */
		dd_emit(ctx, 1, 0x70);	/* 000000ff */
		dd_emit(ctx, 1, 0x80);	/* 000000ff */
		dd_emit(ctx, 1, 0);	/* 000000ff */
		dd_emit(ctx, 1, 0);	/* 00000001 */
		dd_emit(ctx, 1, 1);	/* 00000001 */
		dd_emit(ctx, 1, 0x70);	/* 000000ff */
		dd_emit(ctx, 1, 0x80);	/* 000000ff */
		dd_emit(ctx, 1, 0);	/* 000000ff */
	} else {
		dd_emit(ctx, 1, 1);	/* 00000001 */
		dd_emit(ctx, 1, 0xf0);	/* 000000ff */
		dd_emit(ctx, 1, 0xff);	/* 000000ff */
		dd_emit(ctx, 1, 0);	/* 000000ff */
		dd_emit(ctx, 1, 0);	/* 00000001 */
		dd_emit(ctx, 1, 1);	/* 00000001 */
		dd_emit(ctx, 1, 0xf0);	/* 000000ff */
		dd_emit(ctx, 1, 0xff);	/* 000000ff */
		dd_emit(ctx, 1, 0);	/* 000000ff */
		dd_emit(ctx, 1, 9);	/* 0000003f UNK114C.COMP,SIZE */
	}

	/* eng2d state */
	dd_emit(ctx, 1, 0);		/* 00000001 eng2d COLOR_KEY_ENABLE */
	dd_emit(ctx, 1, 0);		/* 00000007 eng2d COLOR_KEY_FORMAT */
	dd_emit(ctx, 1, 1);		/* ffffffff eng2d DST_DEPTH */
	dd_emit(ctx, 1, 0xcf);		/* 000000ff eng2d DST_FORMAT */
	dd_emit(ctx, 1, 0);		/* ffffffff eng2d DST_LAYER */
	dd_emit(ctx, 1, 1);		/* 00000001 eng2d DST_LINEAR */
	dd_emit(ctx, 1, 0);		/* 00000007 eng2d PATTERN_COLOR_FORMAT */
	dd_emit(ctx, 1, 0);		/* 00000007 eng2d OPERATION */
	dd_emit(ctx, 1, 0);		/* 00000003 eng2d PATTERN_SELECT */
	dd_emit(ctx, 1, 0xcf);		/* 000000ff eng2d SIFC_FORMAT */
	dd_emit(ctx, 1, 0);		/* 00000001 eng2d SIFC_BITMAP_ENABLE */
	dd_emit(ctx, 1, 2);		/* 00000003 eng2d SIFC_BITMAP_UNK808 */
	dd_emit(ctx, 1, 0);		/* ffffffff eng2d BLIT_DU_DX_FRACT */
	dd_emit(ctx, 1, 1);		/* ffffffff eng2d BLIT_DU_DX_INT */
	dd_emit(ctx, 1, 0);		/* ffffffff eng2d BLIT_DV_DY_FRACT */
	dd_emit(ctx, 1, 1);		/* ffffffff eng2d BLIT_DV_DY_INT */
	dd_emit(ctx, 1, 0);		/* 00000001 eng2d BLIT_CONTROL_FILTER */
	dd_emit(ctx, 1, 0xcf);		/* 000000ff eng2d DRAW_COLOR_FORMAT */
	dd_emit(ctx, 1, 0xcf);		/* 000000ff eng2d SRC_FORMAT */
	dd_emit(ctx, 1, 1);		/* 00000001 eng2d SRC_LINEAR #2 */

	num = ctx->ctxvals_pos - base;
	ctx->ctxvals_pos = base;
	if (IS_NVA3F(device->chipset))
		cp_ctx(ctx, 0x404800, num);
	else
		cp_ctx(ctx, 0x405400, num);
}