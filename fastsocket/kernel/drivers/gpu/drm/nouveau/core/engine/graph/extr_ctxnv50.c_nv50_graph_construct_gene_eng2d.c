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
 int /*<<< orphan*/  xf_emit (struct nouveau_grctx*,int,int) ; 

__attribute__((used)) static void
nv50_graph_construct_gene_eng2d(struct nouveau_grctx *ctx)
{
	struct nouveau_device *device = ctx->device;
	/* middle of strand 1 on pre-NVA0 [after vfetch], middle of strand 6 on NVAx */
	/* SEEK */
	xf_emit(ctx, 2, 0);		/* 0001ffff CLIP_X, CLIP_Y */
	xf_emit(ctx, 2, 0);		/* 0000ffff CLIP_W, CLIP_H */
	xf_emit(ctx, 1, 0);		/* 00000001 CLIP_ENABLE */
	if (device->chipset < 0xa0) {
		/* this is useless on everything but the original NV50,
		 * guess they forgot to nuke it. Or just didn't bother. */
		xf_emit(ctx, 2, 0);	/* 0000ffff IFC_CLIP_X, Y */
		xf_emit(ctx, 2, 1);	/* 0000ffff IFC_CLIP_W, H */
		xf_emit(ctx, 1, 0);	/* 00000001 IFC_CLIP_ENABLE */
	}
	xf_emit(ctx, 1, 1);		/* 00000001 DST_LINEAR */
	xf_emit(ctx, 1, 0x100);		/* 0001ffff DST_WIDTH */
	xf_emit(ctx, 1, 0x100);		/* 0001ffff DST_HEIGHT */
	xf_emit(ctx, 1, 0x11);		/* 3f[NV50]/7f[NV84+] DST_FORMAT */
	xf_emit(ctx, 1, 0);		/* 0001ffff DRAW_POINT_X */
	xf_emit(ctx, 1, 8);		/* 0000000f DRAW_UNK58C */
	xf_emit(ctx, 1, 0);		/* 000fffff SIFC_DST_X_FRACT */
	xf_emit(ctx, 1, 0);		/* 0001ffff SIFC_DST_X_INT */
	xf_emit(ctx, 1, 0);		/* 000fffff SIFC_DST_Y_FRACT */
	xf_emit(ctx, 1, 0);		/* 0001ffff SIFC_DST_Y_INT */
	xf_emit(ctx, 1, 0);		/* 000fffff SIFC_DX_DU_FRACT */
	xf_emit(ctx, 1, 1);		/* 0001ffff SIFC_DX_DU_INT */
	xf_emit(ctx, 1, 0);		/* 000fffff SIFC_DY_DV_FRACT */
	xf_emit(ctx, 1, 1);		/* 0001ffff SIFC_DY_DV_INT */
	xf_emit(ctx, 1, 1);		/* 0000ffff SIFC_WIDTH */
	xf_emit(ctx, 1, 1);		/* 0000ffff SIFC_HEIGHT */
	xf_emit(ctx, 1, 0xcf);		/* 000000ff SIFC_FORMAT */
	xf_emit(ctx, 1, 2);		/* 00000003 SIFC_BITMAP_UNK808 */
	xf_emit(ctx, 1, 0);		/* 00000003 SIFC_BITMAP_LINE_PACK_MODE */
	xf_emit(ctx, 1, 0);		/* 00000001 SIFC_BITMAP_LSB_FIRST */
	xf_emit(ctx, 1, 0);		/* 00000001 SIFC_BITMAP_ENABLE */
	xf_emit(ctx, 1, 0);		/* 0000ffff BLIT_DST_X */
	xf_emit(ctx, 1, 0);		/* 0000ffff BLIT_DST_Y */
	xf_emit(ctx, 1, 0);		/* 000fffff BLIT_DU_DX_FRACT */
	xf_emit(ctx, 1, 1);		/* 0001ffff BLIT_DU_DX_INT */
	xf_emit(ctx, 1, 0);		/* 000fffff BLIT_DV_DY_FRACT */
	xf_emit(ctx, 1, 1);		/* 0001ffff BLIT_DV_DY_INT */
	xf_emit(ctx, 1, 1);		/* 0000ffff BLIT_DST_W */
	xf_emit(ctx, 1, 1);		/* 0000ffff BLIT_DST_H */
	xf_emit(ctx, 1, 0);		/* 000fffff BLIT_SRC_X_FRACT */
	xf_emit(ctx, 1, 0);		/* 0001ffff BLIT_SRC_X_INT */
	xf_emit(ctx, 1, 0);		/* 000fffff BLIT_SRC_Y_FRACT */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK888 */
	xf_emit(ctx, 1, 4);		/* 0000003f UNK884 */
	xf_emit(ctx, 1, 0);		/* 00000007 UNK880 */
	xf_emit(ctx, 1, 1);		/* 0000001f tesla UNK0FB8 */
	xf_emit(ctx, 1, 0x15);		/* 000000ff tesla UNK128C */
	xf_emit(ctx, 2, 0);		/* 00000007, ffff0ff3 */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK260 */
	xf_emit(ctx, 1, 0x4444480);	/* 1fffffff UNK870 */
	/* SEEK */
	xf_emit(ctx, 0x10, 0);
	/* SEEK */
	xf_emit(ctx, 0x27, 0);
}