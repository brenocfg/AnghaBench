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
nv50_graph_construct_gene_strmout(struct nouveau_grctx *ctx)
{
	struct nouveau_device *device = ctx->device;
	xf_emit(ctx, 1, 0x102);		/* 0000ffff STRMOUT_BUFFER_CTRL */
	xf_emit(ctx, 1, 0);		/* ffffffff STRMOUT_PRIMITIVE_COUNT */
	xf_emit(ctx, 4, 4);		/* 000000ff STRMOUT_NUM_ATTRIBS */
	if (device->chipset >= 0xa0) {
		xf_emit(ctx, 4, 0);	/* ffffffff UNK1A8C */
		xf_emit(ctx, 4, 0);	/* ffffffff UNK1780 */
	}
	xf_emit(ctx, 1, 4);		/* 000000ff GP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 4);		/* 0000007f VP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	if (device->chipset == 0x50)
		xf_emit(ctx, 1, 0x3ff);	/* 000003ff tesla UNK0D68 */
	else
		xf_emit(ctx, 1, 0x7ff);	/* 000007ff tesla UNK0D68 */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
	/* SEEK */
	xf_emit(ctx, 1, 0x102);		/* 0000ffff STRMOUT_BUFFER_CTRL */
	xf_emit(ctx, 1, 0);		/* ffffffff STRMOUT_PRIMITIVE_COUNT */
	xf_emit(ctx, 4, 0);		/* 000000ff STRMOUT_ADDRESS_HIGH */
	xf_emit(ctx, 4, 0);		/* ffffffff STRMOUT_ADDRESS_LOW */
	xf_emit(ctx, 4, 4);		/* 000000ff STRMOUT_NUM_ATTRIBS */
	if (device->chipset >= 0xa0) {
		xf_emit(ctx, 4, 0);	/* ffffffff UNK1A8C */
		xf_emit(ctx, 4, 0);	/* ffffffff UNK1780 */
	}
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_STRMOUT */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_QUERY */
	xf_emit(ctx, 1, 0);		/* 000000ff QUERY_ADDRESS_HIGH */
	xf_emit(ctx, 2, 0);		/* ffffffff QUERY_ADDRESS_LOW QUERY_COUNTER */
	xf_emit(ctx, 2, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
	/* SEEK */
	xf_emit(ctx, 0x20, 0);		/* ffffffff STRMOUT_MAP */
	xf_emit(ctx, 1, 0);		/* 0000000f */
	xf_emit(ctx, 1, 0);		/* 00000000? */
	xf_emit(ctx, 2, 0);		/* ffffffff */
}