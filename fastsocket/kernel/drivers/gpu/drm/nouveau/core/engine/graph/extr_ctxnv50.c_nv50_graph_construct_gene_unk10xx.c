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
nv50_graph_construct_gene_unk10xx(struct nouveau_grctx *ctx)
{
	struct nouveau_device *device = ctx->device;
	int i;
	/* end of area 2 on pre-NVA0, area 1 on NVAx */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 4);		/* 0000007f VP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 0x80);		/* 0000ffff GP_VERTEX_OUTPUT_COUNT */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_REG_ALLOC_RESULT */
	xf_emit(ctx, 1, 0x80c14);	/* 01ffffff SEMANTIC_COLOR */
	xf_emit(ctx, 1, 0);		/* 00000001 VERTEX_TWO_SIDE_ENABLE */
	if (device->chipset == 0x50)
		xf_emit(ctx, 1, 0x3ff);
	else
		xf_emit(ctx, 1, 0x7ff);	/* 000007ff */
	xf_emit(ctx, 1, 0);		/* 111/113 */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
	for (i = 0; i < 8; i++) {
		switch (device->chipset) {
		case 0x50:
		case 0x86:
		case 0x98:
		case 0xaa:
		case 0xac:
			xf_emit(ctx, 0xa0, 0);	/* ffffffff */
			break;
		case 0x84:
		case 0x92:
		case 0x94:
		case 0x96:
			xf_emit(ctx, 0x120, 0);
			break;
		case 0xa5:
		case 0xa8:
			xf_emit(ctx, 0x100, 0);	/* ffffffff */
			break;
		case 0xa0:
		case 0xa3:
		case 0xaf:
			xf_emit(ctx, 0x400, 0);	/* ffffffff */
			break;
		}
		xf_emit(ctx, 4, 0);	/* 3f, 0, 0, 0 */
		xf_emit(ctx, 4, 0);	/* ffffffff */
	}
	xf_emit(ctx, 1, 4);		/* 000000ff GP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 4);		/* 0000007f VP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 0x80);		/* 0000ffff GP_VERTEX_OUTPUT_COUNT */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_REG_ALLOC_TEMP */
	xf_emit(ctx, 1, 1);		/* 00000001 RASTERIZE_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1900 */
	xf_emit(ctx, 1, 0x27);		/* 000000ff UNK0FD4 */
	xf_emit(ctx, 1, 0);		/* 0001ffff GP_BUILTIN_RESULT_EN */
	xf_emit(ctx, 1, 0x26);		/* 000000ff SEMANTIC_LAYER */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
}