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
struct nouveau_grctx {struct nouveau_device* device; } ;
struct nouveau_device {int chipset; } ;

/* Variables and functions */
 scalar_t__ IS_NVA3F (int) ; 
 int /*<<< orphan*/  xf_emit (struct nouveau_grctx*,int,int) ; 

__attribute__((used)) static void
nv50_graph_construct_gene_unk1cxx(struct nouveau_grctx *ctx)
{
	struct nouveau_device *device = ctx->device;
	xf_emit(ctx, 2, 0);		/* 00007fff WINDOW_OFFSET_XY */
	xf_emit(ctx, 1, 0x3f800000);	/* ffffffff LINE_WIDTH */
	xf_emit(ctx, 1, 0);		/* 00000001 LINE_SMOOTH_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1658 */
	xf_emit(ctx, 1, 0);		/* 00000001 POLYGON_SMOOTH_ENABLE */
	xf_emit(ctx, 3, 0);		/* 00000001 POLYGON_OFFSET_*_ENABLE */
	xf_emit(ctx, 1, 4);		/* 0000000f CULL_MODE */
	xf_emit(ctx, 1, 0x1a);		/* 0000001f POLYGON_MODE */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FORMAT */
	xf_emit(ctx, 1, 0);		/* 00000001 POINT_SPRITE_ENABLE */
	xf_emit(ctx, 1, 1);		/* 00000001 tesla UNK165C */
	xf_emit(ctx, 0x10, 0);		/* 00000001 SCISSOR_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1534 */
	xf_emit(ctx, 1, 0);		/* 00000001 LINE_STIPPLE_ENABLE */
	xf_emit(ctx, 1, 0x00ffff00);	/* 00ffffff LINE_STIPPLE_PATTERN */
	xf_emit(ctx, 1, 0);		/* ffffffff POLYGON_OFFSET_UNITS */
	xf_emit(ctx, 1, 0);		/* ffffffff POLYGON_OFFSET_FACTOR */
	xf_emit(ctx, 1, 0);		/* 00000003 tesla UNK1668 */
	xf_emit(ctx, 2, 0);		/* 07ffffff SCREEN_SCISSOR */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1900 */
	xf_emit(ctx, 1, 0xf);		/* 0000000f COLOR_MASK */
	xf_emit(ctx, 7, 0);		/* 0000000f COLOR_MASK */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff RT_CONTROL */
	xf_emit(ctx, 1, 0x11);		/* 0000007f RT_FORMAT */
	xf_emit(ctx, 7, 0);		/* 0000007f RT_FORMAT */
	xf_emit(ctx, 8, 0);		/* 00000001 RT_HORIZ_LINEAR */
	xf_emit(ctx, 1, 4);		/* 00000007 FP_CONTROL */
	xf_emit(ctx, 1, 0);		/* 00000001 ALPHA_TEST_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000007 ALPHA_TEST_FUNC */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 3);	/* 00000003 UNK16B4 */
	else if (device->chipset >= 0xa0)
		xf_emit(ctx, 1, 1);	/* 00000001 UNK16B4 */
	xf_emit(ctx, 1, 0);		/* 00000003 MULTISAMPLE_CTRL */
	xf_emit(ctx, 1, 0);		/* 00000003 tesla UNK0F90 */
	xf_emit(ctx, 1, 2);		/* 00000003 tesla UNK143C */
	xf_emit(ctx, 2, 0x04000000);	/* 07ffffff tesla UNK0D6C */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_FRONT_MASK */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WRITE_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 SAMPLECNT_ENABLE */
	xf_emit(ctx, 1, 5);		/* 0000000f UNK1408 */
	xf_emit(ctx, 1, 0x52);		/* 000001ff SEMANTIC_PTSZ */
	xf_emit(ctx, 1, 0);		/* ffffffff POINT_SIZE */
	xf_emit(ctx, 1, 0);		/* 00000001 */
	xf_emit(ctx, 1, 0);		/* 00000007 tesla UNK0FB4 */
	if (device->chipset != 0x50) {
		xf_emit(ctx, 1, 0);	/* 3ff */
		xf_emit(ctx, 1, 1);	/* 00000001 tesla UNK1110 */
	}
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 0);	/* 00000003 tesla UNK1928 */
	xf_emit(ctx, 0x10, 0);		/* ffffffff DEPTH_RANGE_NEAR */
	xf_emit(ctx, 0x10, 0x3f800000);	/* ffffffff DEPTH_RANGE_FAR */
	xf_emit(ctx, 1, 0x10);		/* 000000ff VIEW_VOLUME_CLIP_CTRL */
	xf_emit(ctx, 0x20, 0);		/* 07ffffff VIEWPORT_HORIZ, then VIEWPORT_VERT. (W&0x3fff)<<13 | (X&0x1fff). */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK187C */
	xf_emit(ctx, 1, 0);		/* 00000003 WINDOW_ORIGIN */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_FRONT_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_BACK_ENABLE */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_BACK_MASK */
	xf_emit(ctx, 1, 0x8100c12);	/* 1fffffff FP_INTERPOLANT_CTRL */
	xf_emit(ctx, 1, 5);		/* 0000000f tesla UNK1220 */
	xf_emit(ctx, 1, 0);		/* 00000007 MULTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 1, 0);		/* 000000ff tesla UNK1A20 */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 VERTEX_TWO_SIDE_ENABLE */
	xf_emit(ctx, 4, 0xffff);	/* 0000ffff MSAA_MASK */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 3);	/* 00000003 tesla UNK1100 */
	if (device->chipset < 0xa0)
		xf_emit(ctx, 0x1c, 0);	/* RO */
	else if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 0x9, 0);
	xf_emit(ctx, 1, 0);		/* 00000001 UNK1534 */
	xf_emit(ctx, 1, 0);		/* 00000001 LINE_SMOOTH_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 LINE_STIPPLE_ENABLE */
	xf_emit(ctx, 1, 0x00ffff00);	/* 00ffffff LINE_STIPPLE_PATTERN */
	xf_emit(ctx, 1, 0x1a);		/* 0000001f POLYGON_MODE */
	xf_emit(ctx, 1, 0);		/* 00000003 WINDOW_ORIGIN */
	if (device->chipset != 0x50) {
		xf_emit(ctx, 1, 3);	/* 00000003 tesla UNK1100 */
		xf_emit(ctx, 1, 0);	/* 3ff */
	}
	/* XXX: the following block could belong either to unk1cxx, or
	 * to STRMOUT. Rather hard to tell. */
	if (device->chipset < 0xa0)
		xf_emit(ctx, 0x25, 0);
	else
		xf_emit(ctx, 0x3b, 0);
}