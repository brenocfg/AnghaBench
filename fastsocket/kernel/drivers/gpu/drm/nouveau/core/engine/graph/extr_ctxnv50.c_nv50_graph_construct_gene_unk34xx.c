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
nv50_graph_construct_gene_unk34xx(struct nouveau_grctx *ctx)
{
	struct nouveau_device *device = ctx->device;
	/* end of area 2 on pre-NVA0, area 1 on NVAx */
	xf_emit(ctx, 1, 0);		/* 00000001 VIEWPORT_CLIP_RECTS_EN */
	xf_emit(ctx, 1, 0);		/* 00000003 VIEWPORT_CLIP_MODE */
	xf_emit(ctx, 0x10, 0x04000000);	/* 07ffffff VIEWPORT_CLIP_HORIZ*8, VIEWPORT_CLIP_VERT*8 */
	xf_emit(ctx, 1, 0);		/* 00000001 POLYGON_STIPPLE_ENABLE */
	xf_emit(ctx, 0x20, 0);		/* ffffffff POLYGON_STIPPLE */
	xf_emit(ctx, 2, 0);		/* 00007fff WINDOW_OFFSET_XY */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 0x04e3bfdf);	/* ffffffff UNK0D64 */
	xf_emit(ctx, 1, 0x04e3bfdf);	/* ffffffff UNK0DF4 */
	xf_emit(ctx, 1, 0);		/* 00000003 WINDOW_ORIGIN */
	xf_emit(ctx, 1, 0);		/* 00000007 */
	xf_emit(ctx, 1, 0x1fe21);	/* 0001ffff tesla UNK0FAC */
	if (device->chipset >= 0xa0)
		xf_emit(ctx, 1, 0x0fac6881);
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 1, 1);
		xf_emit(ctx, 3, 0);
	}
}