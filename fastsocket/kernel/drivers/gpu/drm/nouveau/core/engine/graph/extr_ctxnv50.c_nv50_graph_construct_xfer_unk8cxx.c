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
struct nouveau_device {int /*<<< orphan*/  chipset; } ;

/* Variables and functions */
 scalar_t__ IS_NVA3F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xf_emit (struct nouveau_grctx*,int,int) ; 

__attribute__((used)) static void
nv50_graph_construct_xfer_unk8cxx(struct nouveau_grctx *ctx)
{
	struct nouveau_device *device = ctx->device;
	xf_emit(ctx, 1, 0);		/* 00000001 UNK1534 */
	xf_emit(ctx, 1, 0);		/* 7/f MULTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 2, 0);		/* 7, ffff0ff3 */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WRITE */
	xf_emit(ctx, 1, 0x04e3bfdf);	/* ffffffff UNK0D64 */
	xf_emit(ctx, 1, 0x04e3bfdf);	/* ffffffff UNK0DF4 */
	xf_emit(ctx, 1, 1);		/* 00000001 UNK15B4 */
	xf_emit(ctx, 1, 0);		/* 00000001 LINE_STIPPLE_ENABLE */
	xf_emit(ctx, 1, 0x00ffff00);	/* 00ffffff LINE_STIPPLE_PATTERN */
	xf_emit(ctx, 1, 1);		/* 00000001 tesla UNK0F98 */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);	/* 0000001f tesla UNK169C */
	xf_emit(ctx, 1, 0);		/* 00000003 tesla UNK1668 */
	xf_emit(ctx, 1, 0);		/* 00000001 LINE_STIPPLE_ENABLE */
	xf_emit(ctx, 1, 0x00ffff00);	/* 00ffffff LINE_STIPPLE_PATTERN */
	xf_emit(ctx, 1, 0);		/* 00000001 POLYGON_SMOOTH_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK1534 */
	xf_emit(ctx, 1, 0);		/* 7/f MULTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1658 */
	xf_emit(ctx, 1, 0);		/* 00000001 LINE_SMOOTH_ENABLE */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WRITE */
	xf_emit(ctx, 1, 1);		/* 00000001 UNK15B4 */
	xf_emit(ctx, 1, 0);		/* 00000001 POINT_SPRITE_ENABLE */
	xf_emit(ctx, 1, 1);		/* 00000001 tesla UNK165C */
	xf_emit(ctx, 1, 0x30201000);	/* ffffffff tesla UNK1670 */
	xf_emit(ctx, 1, 0x70605040);	/* ffffffff tesla UNK1670 */
	xf_emit(ctx, 1, 0xb8a89888);	/* ffffffff tesla UNK1670 */
	xf_emit(ctx, 1, 0xf8e8d8c8);	/* ffffffff tesla UNK1670 */
	xf_emit(ctx, 1, 0);		/* 00000001 VERTEX_TWO_SIDE_ENABLE */
	xf_emit(ctx, 1, 0x1a);		/* 0000001f POLYGON_MODE */
}