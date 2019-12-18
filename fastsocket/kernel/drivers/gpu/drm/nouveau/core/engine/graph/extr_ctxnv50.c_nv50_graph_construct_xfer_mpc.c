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
 scalar_t__ IS_NVAAF (int) ; 
 int /*<<< orphan*/  xf_emit (struct nouveau_grctx*,int,int) ; 

__attribute__((used)) static void
nv50_graph_construct_xfer_mpc(struct nouveau_grctx *ctx)
{
	struct nouveau_device *device = ctx->device;
	int i, mpcnt = 2;
	switch (device->chipset) {
		case 0x98:
		case 0xaa:
			mpcnt = 1;
			break;
		case 0x50:
		case 0x84:
		case 0x86:
		case 0x92:
		case 0x94:
		case 0x96:
		case 0xa8:
		case 0xac:
			mpcnt = 2;
			break;
		case 0xa0:
		case 0xa3:
		case 0xa5:
		case 0xaf:
			mpcnt = 3;
			break;
	}
	for (i = 0; i < mpcnt; i++) {
		xf_emit(ctx, 1, 0);		/* ff */
		xf_emit(ctx, 1, 0x80);		/* ffffffff tesla UNK1404 */
		xf_emit(ctx, 1, 0x80007004);	/* ffffffff tesla UNK12B0 */
		xf_emit(ctx, 1, 0x04000400);	/* ffffffff */
		if (device->chipset >= 0xa0)
			xf_emit(ctx, 1, 0xc0);	/* 00007fff tesla UNK152C */
		xf_emit(ctx, 1, 0x1000);	/* 0000ffff tesla UNK0D60 */
		xf_emit(ctx, 1, 0);		/* ff/3ff */
		xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A30 */
		if (device->chipset == 0x86 || device->chipset == 0x98 || device->chipset == 0xa8 || IS_NVAAF(device->chipset)) {
			xf_emit(ctx, 1, 0xe00);		/* 7fff */
			xf_emit(ctx, 1, 0x1e00);	/* 7fff */
		}
		xf_emit(ctx, 1, 1);		/* 000000ff VP_REG_ALLOC_TEMP */
		xf_emit(ctx, 1, 0);		/* 00000001 LINKED_TSC */
		xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
		if (device->chipset == 0x50)
			xf_emit(ctx, 2, 0x1000);	/* 7fff tesla UNK141C */
		xf_emit(ctx, 1, 1);		/* 000000ff GP_REG_ALLOC_TEMP */
		xf_emit(ctx, 1, 0);		/* 00000001 GP_ENABLE */
		xf_emit(ctx, 1, 4);		/* 000000ff FP_REG_ALLOC_TEMP */
		xf_emit(ctx, 1, 2);		/* 00000003 REG_MODE */
		if (IS_NVAAF(device->chipset))
			xf_emit(ctx, 0xb, 0);	/* RO */
		else if (device->chipset >= 0xa0)
			xf_emit(ctx, 0xc, 0);	/* RO */
		else
			xf_emit(ctx, 0xa, 0);	/* RO */
	}
	xf_emit(ctx, 1, 0x08100c12);		/* 1fffffff FP_INTERPOLANT_CTRL */
	xf_emit(ctx, 1, 0);			/* ff/3ff */
	if (device->chipset >= 0xa0) {
		xf_emit(ctx, 1, 0x1fe21);	/* 0003ffff tesla UNK0FAC */
	}
	xf_emit(ctx, 3, 0);			/* 7fff, 0, 0 */
	xf_emit(ctx, 1, 0);			/* 00000001 tesla UNK1534 */
	xf_emit(ctx, 1, 0);			/* 7/f MULTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 4, 0xffff);		/* 0000ffff MSAA_MASK */
	xf_emit(ctx, 1, 1);			/* 00000001 LANES32 */
	xf_emit(ctx, 1, 0x10001);		/* 00ffffff BLOCK_ALLOC */
	xf_emit(ctx, 1, 0x10001);		/* ffffffff BLOCKDIM_XY */
	xf_emit(ctx, 1, 1);			/* 0000ffff BLOCKDIM_Z */
	xf_emit(ctx, 1, 0);			/* ffffffff SHARED_SIZE */
	xf_emit(ctx, 1, 0x1fe21);		/* 1ffff/3ffff[NVA0+] tesla UNk0FAC */
	xf_emit(ctx, 1, 0);			/* ffffffff tesla UNK1A34 */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);		/* 0000001f tesla UNK169C */
	xf_emit(ctx, 1, 0);			/* ff/3ff */
	xf_emit(ctx, 1, 0);			/* 1 LINKED_TSC */
	xf_emit(ctx, 1, 0);			/* ff FP_ADDRESS_HIGH */
	xf_emit(ctx, 1, 0);			/* ffffffff FP_ADDRESS_LOW */
	xf_emit(ctx, 1, 0x08100c12);		/* 1fffffff FP_INTERPOLANT_CTRL */
	xf_emit(ctx, 1, 4);			/* 00000007 FP_CONTROL */
	xf_emit(ctx, 1, 0);			/* 000000ff FRAG_COLOR_CLAMP_EN */
	xf_emit(ctx, 1, 2);			/* 00000003 REG_MODE */
	xf_emit(ctx, 1, 0x11);			/* 0000007f RT_FORMAT */
	xf_emit(ctx, 7, 0);			/* 0000007f RT_FORMAT */
	xf_emit(ctx, 1, 0);			/* 00000007 */
	xf_emit(ctx, 1, 0xfac6881);		/* 0fffffff RT_CONTROL */
	xf_emit(ctx, 1, 0);			/* 00000003 MULTISAMPLE_CTRL */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 3);		/* 00000003 tesla UNK16B4 */
	xf_emit(ctx, 1, 0);			/* 00000001 ALPHA_TEST_ENABLE */
	xf_emit(ctx, 1, 0);			/* 00000007 ALPHA_TEST_FUNC */
	xf_emit(ctx, 1, 0);			/* 00000001 FRAMEBUFFER_SRGB */
	xf_emit(ctx, 1, 4);			/* ffffffff tesla UNK1400 */
	xf_emit(ctx, 8, 0);			/* 00000001 BLEND_ENABLE */
	xf_emit(ctx, 1, 0);			/* 00000001 LOGIC_OP_ENABLE */
	xf_emit(ctx, 1, 2);			/* 0000001f BLEND_FUNC_SRC_RGB */
	xf_emit(ctx, 1, 1);			/* 0000001f BLEND_FUNC_DST_RGB */
	xf_emit(ctx, 1, 1);			/* 00000007 BLEND_EQUATION_RGB */
	xf_emit(ctx, 1, 2);			/* 0000001f BLEND_FUNC_SRC_ALPHA */
	xf_emit(ctx, 1, 1);			/* 0000001f BLEND_FUNC_DST_ALPHA */
	xf_emit(ctx, 1, 1);			/* 00000007 BLEND_EQUATION_ALPHA */
	xf_emit(ctx, 1, 1);			/* 00000001 UNK133C */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 1, 0);		/* 00000001 UNK12E4 */
		xf_emit(ctx, 8, 2);		/* 0000001f IBLEND_FUNC_SRC_RGB */
		xf_emit(ctx, 8, 1);		/* 0000001f IBLEND_FUNC_DST_RGB */
		xf_emit(ctx, 8, 1);		/* 00000007 IBLEND_EQUATION_RGB */
		xf_emit(ctx, 8, 2);		/* 0000001f IBLEND_FUNC_SRC_ALPHA */
		xf_emit(ctx, 8, 1);		/* 0000001f IBLEND_FUNC_DST_ALPHA */
		xf_emit(ctx, 8, 1);		/* 00000007 IBLEND_EQUATION_ALPHA */
		xf_emit(ctx, 8, 1);		/* 00000001 IBLEND_UNK00 */
		xf_emit(ctx, 1, 0);		/* 00000003 tesla UNK1928 */
		xf_emit(ctx, 1, 0);		/* 00000001 UNK1140 */
	}
	xf_emit(ctx, 1, 0);			/* 00000003 tesla UNK0F90 */
	xf_emit(ctx, 1, 4);			/* 000000ff FP_RESULT_COUNT */
	/* XXX: demagic this part some day */
	if (device->chipset == 0x50)
		xf_emit(ctx, 0x3a0, 0);
	else if (device->chipset < 0x94)
		xf_emit(ctx, 0x3a2, 0);
	else if (device->chipset == 0x98 || device->chipset == 0xaa)
		xf_emit(ctx, 0x39f, 0);
	else
		xf_emit(ctx, 0x3a3, 0);
	xf_emit(ctx, 1, 0x11);			/* 3f/7f DST_FORMAT */
	xf_emit(ctx, 1, 0);			/* 7 OPERATION */
	xf_emit(ctx, 1, 1);			/* 1 DST_LINEAR */
	xf_emit(ctx, 0x2d, 0);
}