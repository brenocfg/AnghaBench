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
 int /*<<< orphan*/  IS_NVAAF (int) ; 
 int /*<<< orphan*/  xf_emit (struct nouveau_grctx*,int,int) ; 

__attribute__((used)) static void
nv50_graph_construct_xfer_tex(struct nouveau_grctx *ctx)
{
	struct nouveau_device *device = ctx->device;
	xf_emit(ctx, 2, 0);		/* 1 LINKED_TSC. yes, 2. */
	if (device->chipset != 0x50)
		xf_emit(ctx, 1, 0);	/* 3 */
	xf_emit(ctx, 1, 1);		/* 1ffff BLIT_DU_DX_INT */
	xf_emit(ctx, 1, 0);		/* fffff BLIT_DU_DX_FRACT */
	xf_emit(ctx, 1, 1);		/* 1ffff BLIT_DV_DY_INT */
	xf_emit(ctx, 1, 0);		/* fffff BLIT_DV_DY_FRACT */
	if (device->chipset == 0x50)
		xf_emit(ctx, 1, 0);	/* 3 BLIT_CONTROL */
	else
		xf_emit(ctx, 2, 0);	/* 3ff, 1 */
	xf_emit(ctx, 1, 0x2a712488);	/* ffffffff SRC_TIC_0 */
	xf_emit(ctx, 1, 0);		/* ffffffff SRC_TIC_1 */
	xf_emit(ctx, 1, 0x4085c000);	/* ffffffff SRC_TIC_2 */
	xf_emit(ctx, 1, 0x40);		/* ffffffff SRC_TIC_3 */
	xf_emit(ctx, 1, 0x100);		/* ffffffff SRC_TIC_4 */
	xf_emit(ctx, 1, 0x10100);	/* ffffffff SRC_TIC_5 */
	xf_emit(ctx, 1, 0x02800000);	/* ffffffff SRC_TIC_6 */
	xf_emit(ctx, 1, 0);		/* ffffffff SRC_TIC_7 */
	if (device->chipset == 0x50) {
		xf_emit(ctx, 1, 0);	/* 00000001 turing UNK358 */
		xf_emit(ctx, 1, 0);	/* ffffffff tesla UNK1A34? */
		xf_emit(ctx, 1, 0);	/* 00000003 turing UNK37C tesla UNK1690 */
		xf_emit(ctx, 1, 0);	/* 00000003 BLIT_CONTROL */
		xf_emit(ctx, 1, 0);	/* 00000001 turing UNK32C tesla UNK0F94 */
	} else if (!IS_NVAAF(device->chipset)) {
		xf_emit(ctx, 1, 0);	/* ffffffff tesla UNK1A34? */
		xf_emit(ctx, 1, 0);	/* 00000003 */
		xf_emit(ctx, 1, 0);	/* 000003ff */
		xf_emit(ctx, 1, 0);	/* 00000003 */
		xf_emit(ctx, 1, 0);	/* 000003ff */
		xf_emit(ctx, 1, 0);	/* 00000003 tesla UNK1664 / turing UNK03E8 */
		xf_emit(ctx, 1, 0);	/* 00000003 */
		xf_emit(ctx, 1, 0);	/* 000003ff */
	} else {
		xf_emit(ctx, 0x6, 0);
	}
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A34 */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_TEXTURE */
	xf_emit(ctx, 1, 0);		/* 0000ffff DMA_SRC */
}