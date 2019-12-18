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
nv50_graph_construct_xfer_unk84xx(struct nouveau_grctx *ctx)
{
	struct nouveau_device *device = ctx->device;
	int magic3;
	switch (device->chipset) {
	case 0x50:
		magic3 = 0x1000;
		break;
	case 0x86:
	case 0x98:
	case 0xa8:
	case 0xaa:
	case 0xac:
	case 0xaf:
		magic3 = 0x1e00;
		break;
	default:
		magic3 = 0;
	}
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 4);		/* 7f/ff[NVA0+] VP_REG_ALLOC_RESULT */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
	xf_emit(ctx, 1, 0);		/* 111/113[NVA0+] */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 0x1f, 0);	/* ffffffff */
	else if (device->chipset >= 0xa0)
		xf_emit(ctx, 0x0f, 0);	/* ffffffff */
	else
		xf_emit(ctx, 0x10, 0);	/* fffffff VP_RESULT_MAP_1 up */
	xf_emit(ctx, 2, 0);		/* f/1f[NVA3], fffffff/ffffffff[NVA0+] */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_REG_ALLOC_RESULT */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_RESULT_MAP_SIZE */
	if (device->chipset >= 0xa0)
		xf_emit(ctx, 1, 0x03020100);	/* ffffffff */
	else
		xf_emit(ctx, 1, 0x00608080);	/* fffffff VP_RESULT_MAP_0 */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
	xf_emit(ctx, 2, 0);		/* 111/113, 7f/ff */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_REG_ALLOC_RESULT */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 0x80);		/* 0000ffff GP_VERTEX_OUTPUT_COUNT */
	if (magic3)
		xf_emit(ctx, 1, magic3);	/* 00007fff tesla UNK141C */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
	xf_emit(ctx, 1, 0);		/* 111/113 */
	xf_emit(ctx, 0x1f, 0);		/* ffffffff GP_RESULT_MAP_1 up */
	xf_emit(ctx, 1, 0);		/* 0000001f */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_REG_ALLOC_RESULT */
	xf_emit(ctx, 1, 0x80);		/* 0000ffff GP_VERTEX_OUTPUT_COUNT */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 0x03020100);	/* ffffffff GP_RESULT_MAP_0 */
	xf_emit(ctx, 1, 3);		/* 00000003 GP_OUTPUT_PRIMITIVE_TYPE */
	if (magic3)
		xf_emit(ctx, 1, magic3);	/* 7fff tesla UNK141C */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 0);		/* 00000001 PROVOKING_VERTEX_LAST */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
	xf_emit(ctx, 1, 0);		/* 111/113 */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 3);		/* 00000003 GP_OUTPUT_PRIMITIVE_TYPE */
	xf_emit(ctx, 1, 0);		/* 00000001 PROVOKING_VERTEX_LAST */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
	xf_emit(ctx, 1, 0);		/* 00000003 tesla UNK13A0 */
	xf_emit(ctx, 1, 4);		/* 7f/ff VP_REG_ALLOC_RESULT */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
	xf_emit(ctx, 1, 0);		/* 111/113 */
	if (device->chipset == 0x94 || device->chipset == 0x96)
		xf_emit(ctx, 0x1020, 0);	/* 4 x (0x400 x 0xffffffff, ff, 0, 0, 0, 4 x ffffffff) */
	else if (device->chipset < 0xa0)
		xf_emit(ctx, 0xa20, 0);	/* 4 x (0x280 x 0xffffffff, ff, 0, 0, 0, 4 x ffffffff) */
	else if (!IS_NVA3F(device->chipset))
		xf_emit(ctx, 0x210, 0);	/* ffffffff */
	else
		xf_emit(ctx, 0x410, 0);	/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
	xf_emit(ctx, 1, 4);		/* 000000ff GP_RESULT_MAP_SIZE */
	xf_emit(ctx, 1, 3);		/* 00000003 GP_OUTPUT_PRIMITIVE_TYPE */
	xf_emit(ctx, 1, 0);		/* 00000001 PROVOKING_VERTEX_LAST */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
}