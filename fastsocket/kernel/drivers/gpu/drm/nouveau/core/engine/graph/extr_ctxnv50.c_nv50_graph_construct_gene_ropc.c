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
 int /*<<< orphan*/  IS_NVAAF (int) ; 
 int /*<<< orphan*/  xf_emit (struct nouveau_grctx*,int,int) ; 

__attribute__((used)) static void
nv50_graph_construct_gene_ropc(struct nouveau_grctx *ctx)
{
	struct nouveau_device *device = ctx->device;
	int magic2;
	if (device->chipset == 0x50) {
		magic2 = 0x00003e60;
	} else if (!IS_NVA3F(device->chipset)) {
		magic2 = 0x001ffe67;
	} else {
		magic2 = 0x00087e67;
	}
	xf_emit(ctx, 1, 0);		/* f/7 MUTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1534 */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIL_BACK_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_BACK_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_BACK_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIL_BACK_OP_FAIL, ZFAIL, ZPASS */
	xf_emit(ctx, 1, 2);		/* 00000003 tesla UNK143C */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, magic2);	/* 001fffff tesla UNK0F78 */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000007 DEPTH_TEST_FUNC */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WRITE_ENABLE */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 1, 1);	/* 0000001f tesla UNK169C */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIL_FRONT_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_FRONT_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_FRONT_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIL_FRONT_OP_FAIL, ZFAIL, ZPASS */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_FRONT_ENABLE */
	if (device->chipset >= 0xa0 && !IS_NVAAF(device->chipset))
		xf_emit(ctx, 1, 0x15);	/* 000000ff */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_BACK_ENABLE */
	xf_emit(ctx, 1, 1);		/* 00000001 tesla UNK15B4 */
	xf_emit(ctx, 1, 0x10);		/* 3ff/ff VIEW_VOLUME_CLIP_CTRL */
	xf_emit(ctx, 1, 0);		/* ffffffff CLEAR_DEPTH */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FORMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABLE */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A3C */
	if (device->chipset == 0x86 || device->chipset == 0x92 || device->chipset == 0x98 || device->chipset >= 0xa0) {
		xf_emit(ctx, 3, 0);	/* ff, ffffffff, ffffffff */
		xf_emit(ctx, 1, 4);	/* 7 */
		xf_emit(ctx, 1, 0x400);	/* fffffff */
		xf_emit(ctx, 1, 0x300);	/* ffff */
		xf_emit(ctx, 1, 0x1001);	/* 1fff */
		if (device->chipset != 0xa0) {
			if (IS_NVA3F(device->chipset))
				xf_emit(ctx, 1, 0);	/* 0000000f UNK15C8 */
			else
				xf_emit(ctx, 1, 0x15);	/* ff */
		}
	}
	xf_emit(ctx, 1, 0);		/* 00000007 MULTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1534 */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIL_BACK_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_BACK_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* ffff0ff3 */
	xf_emit(ctx, 1, 2);		/* 00000003 tesla UNK143C */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000007 DEPTH_TEST_FUNC */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WRITE_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIL_FRONT_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_FRONT_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_FRONT_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_BACK_ENABLE */
	xf_emit(ctx, 1, 1);		/* 00000001 tesla UNK15B4 */
	xf_emit(ctx, 1, 0x10);		/* 7f/ff VIEW_VOLUME_CLIP_CTRL */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FORMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABLE */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A3C */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1534 */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1900 */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIL_BACK_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_BACK_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_BACK_FUNC_REF */
	xf_emit(ctx, 2, 0);		/* ffffffff DEPTH_BOUNDS */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000007 DEPTH_TEST_FUNC */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WRITE_ENABLE */
	xf_emit(ctx, 1, 0);		/* 0000000f */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK0FB0 */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIL_FRONT_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_FRONT_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_FRONT_FUNC_REF */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_FRONT_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_BACK_ENABLE */
	xf_emit(ctx, 1, 0x10);		/* 7f/ff VIEW_VOLUME_CLIP_CTRL */
	xf_emit(ctx, 0x10, 0);		/* ffffffff DEPTH_RANGE_NEAR */
	xf_emit(ctx, 0x10, 0x3f800000);	/* ffffffff DEPTH_RANGE_FAR */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FORMAT */
	xf_emit(ctx, 1, 0);		/* 00000007 MULTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIL_BACK_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_BACK_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_BACK_FUNC_REF */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_BACK_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIL_BACK_OP_FAIL, ZFAIL, ZPASS */
	xf_emit(ctx, 2, 0);		/* ffffffff DEPTH_BOUNDS */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_BOUNDS_EN */
	xf_emit(ctx, 1, 0);		/* 00000007 DEPTH_TEST_FUNC */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_TEST_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 DEPTH_WRITE_ENABLE */
	xf_emit(ctx, 1, 0);		/* 000000ff CLEAR_STENCIL */
	xf_emit(ctx, 1, 0);		/* 00000007 STENCIL_FRONT_FUNC_FUNC */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_FRONT_FUNC_MASK */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_FRONT_FUNC_REF */
	xf_emit(ctx, 1, 0);		/* 000000ff STENCIL_FRONT_MASK */
	xf_emit(ctx, 3, 0);		/* 00000007 STENCIL_FRONT_OP_FAIL, ZFAIL, ZPASS */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_FRONT_ENABLE */
	xf_emit(ctx, 1, 0);		/* 00000001 STENCIL_BACK_ENABLE */
	xf_emit(ctx, 1, 0x10);		/* 7f/ff VIEW_VOLUME_CLIP_CTRL */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FORMAT */
	xf_emit(ctx, 1, 0x3f);		/* 0000003f UNK1590 */
	xf_emit(ctx, 1, 0);		/* 00000007 MULTISAMPLE_SAMPLES_LOG2 */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1534 */
	xf_emit(ctx, 2, 0);		/* ffff0ff3, ffff */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK0FB0 */
	xf_emit(ctx, 1, 0);		/* 0001ffff GP_BUILTIN_RESULT_EN */
	xf_emit(ctx, 1, 1);		/* 00000001 tesla UNK15B4 */
	xf_emit(ctx, 1, 0);		/* 0000000f ZETA_FORMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 ZETA_ENABLE */
	xf_emit(ctx, 1, 0);		/* ffffffff CLEAR_DEPTH */
	xf_emit(ctx, 1, 1);		/* 00000001 tesla UNK19CC */
	if (device->chipset >= 0xa0) {
		xf_emit(ctx, 2, 0);
		xf_emit(ctx, 1, 0x1001);
		xf_emit(ctx, 0xb, 0);
	} else {
		xf_emit(ctx, 1, 0);	/* 00000007 */
		xf_emit(ctx, 1, 0);	/* 00000001 tesla UNK1534 */
		xf_emit(ctx, 1, 0);	/* 00000007 MULTISAMPLE_SAMPLES_LOG2 */
		xf_emit(ctx, 8, 0);	/* 00000001 BLEND_ENABLE */
		xf_emit(ctx, 1, 0);	/* ffff0ff3 */
	}
	xf_emit(ctx, 1, 0x11);		/* 3f/7f RT_FORMAT */
	xf_emit(ctx, 7, 0);		/* 3f/7f RT_FORMAT */
	xf_emit(ctx, 1, 0xf);		/* 0000000f COLOR_MASK */
	xf_emit(ctx, 7, 0);		/* 0000000f COLOR_MASK */
	xf_emit(ctx, 1, 0x11);		/* 3f/7f */
	xf_emit(ctx, 1, 0);		/* 00000001 LOGIC_OP_ENABLE */
	if (device->chipset != 0x50) {
		xf_emit(ctx, 1, 0);	/* 0000000f LOGIC_OP */
		xf_emit(ctx, 1, 0);	/* 000000ff */
	}
	xf_emit(ctx, 1, 0);		/* 00000007 OPERATION */
	xf_emit(ctx, 1, 0);		/* ff/3ff */
	xf_emit(ctx, 1, 0);		/* 00000003 UNK0F90 */
	xf_emit(ctx, 2, 1);		/* 00000007 BLEND_EQUATION_RGB, ALPHA */
	xf_emit(ctx, 1, 1);		/* 00000001 UNK133C */
	xf_emit(ctx, 1, 2);		/* 0000001f BLEND_FUNC_SRC_RGB */
	xf_emit(ctx, 1, 1);		/* 0000001f BLEND_FUNC_DST_RGB */
	xf_emit(ctx, 1, 2);		/* 0000001f BLEND_FUNC_SRC_ALPHA */
	xf_emit(ctx, 1, 1);		/* 0000001f BLEND_FUNC_DST_ALPHA */
	xf_emit(ctx, 1, 0);		/* 00000001 */
	xf_emit(ctx, 1, magic2);	/* 001fffff tesla UNK0F78 */
	xf_emit(ctx, 1, 0);		/* ffffffff tesla UNK1A3C */
	xf_emit(ctx, 1, 0x0fac6881);	/* 0fffffff RT_CONTROL */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 1, 0);	/* 00000001 tesla UNK12E4 */
		xf_emit(ctx, 8, 1);	/* 00000007 IBLEND_EQUATION_RGB */
		xf_emit(ctx, 8, 1);	/* 00000007 IBLEND_EQUATION_ALPHA */
		xf_emit(ctx, 8, 1);	/* 00000001 IBLEND_UNK00 */
		xf_emit(ctx, 8, 2);	/* 0000001f IBLEND_FUNC_SRC_RGB */
		xf_emit(ctx, 8, 1);	/* 0000001f IBLEND_FUNC_DST_RGB */
		xf_emit(ctx, 8, 2);	/* 0000001f IBLEND_FUNC_SRC_ALPHA */
		xf_emit(ctx, 8, 1);	/* 0000001f IBLEND_FUNC_DST_ALPHA */
		xf_emit(ctx, 1, 0);	/* 00000001 tesla UNK1140 */
		xf_emit(ctx, 2, 0);	/* 00000001 */
		xf_emit(ctx, 1, 1);	/* 0000001f tesla UNK169C */
		xf_emit(ctx, 1, 0);	/* 0000000f */
		xf_emit(ctx, 1, 0);	/* 00000003 */
		xf_emit(ctx, 1, 0);	/* ffffffff */
		xf_emit(ctx, 2, 0);	/* 00000001 */
		xf_emit(ctx, 1, 1);	/* 0000001f tesla UNK169C */
		xf_emit(ctx, 1, 0);	/* 00000001 */
		xf_emit(ctx, 1, 0);	/* 000003ff */
	} else if (device->chipset >= 0xa0) {
		xf_emit(ctx, 2, 0);	/* 00000001 */
		xf_emit(ctx, 1, 0);	/* 00000007 */
		xf_emit(ctx, 1, 0);	/* 00000003 */
		xf_emit(ctx, 1, 0);	/* ffffffff */
		xf_emit(ctx, 2, 0);	/* 00000001 */
	} else {
		xf_emit(ctx, 1, 0);	/* 00000007 MULTISAMPLE_SAMPLES_LOG2 */
		xf_emit(ctx, 1, 0);	/* 00000003 tesla UNK1430 */
		xf_emit(ctx, 1, 0);	/* ffffffff tesla UNK1A3C */
	}
	xf_emit(ctx, 4, 0);		/* ffffffff CLEAR_COLOR */
	xf_emit(ctx, 4, 0);		/* ffffffff BLEND_COLOR A R G B */
	xf_emit(ctx, 1, 0);		/* 00000fff eng2d UNK2B0 */
	if (device->chipset >= 0xa0)
		xf_emit(ctx, 2, 0);	/* 00000001 */
	xf_emit(ctx, 1, 0);		/* 000003ff */
	xf_emit(ctx, 8, 0);		/* 00000001 BLEND_ENABLE */
	xf_emit(ctx, 1, 1);		/* 00000001 UNK133C */
	xf_emit(ctx, 1, 2);		/* 0000001f BLEND_FUNC_SRC_RGB */
	xf_emit(ctx, 1, 1);		/* 0000001f BLEND_FUNC_DST_RGB */
	xf_emit(ctx, 1, 1);		/* 00000007 BLEND_EQUATION_RGB */
	xf_emit(ctx, 1, 2);		/* 0000001f BLEND_FUNC_SRC_ALPHA */
	xf_emit(ctx, 1, 1);		/* 0000001f BLEND_FUNC_DST_ALPHA */
	xf_emit(ctx, 1, 1);		/* 00000007 BLEND_EQUATION_ALPHA */
	xf_emit(ctx, 1, 0);		/* 00000001 UNK19C0 */
	xf_emit(ctx, 1, 0);		/* 00000001 LOGIC_OP_ENABLE */
	xf_emit(ctx, 1, 0);		/* 0000000f LOGIC_OP */
	if (device->chipset >= 0xa0)
		xf_emit(ctx, 1, 0);	/* 00000001 UNK12E4? NVA3+ only? */
	if (IS_NVA3F(device->chipset)) {
		xf_emit(ctx, 8, 1);	/* 00000001 IBLEND_UNK00 */
		xf_emit(ctx, 8, 1);	/* 00000007 IBLEND_EQUATION_RGB */
		xf_emit(ctx, 8, 2);	/* 0000001f IBLEND_FUNC_SRC_RGB */
		xf_emit(ctx, 8, 1);	/* 0000001f IBLEND_FUNC_DST_RGB */
		xf_emit(ctx, 8, 1);	/* 00000007 IBLEND_EQUATION_ALPHA */
		xf_emit(ctx, 8, 2);	/* 0000001f IBLEND_FUNC_SRC_ALPHA */
		xf_emit(ctx, 8, 1);	/* 0000001f IBLEND_FUNC_DST_ALPHA */
		xf_emit(ctx, 1, 0);	/* 00000001 tesla UNK15C4 */
		xf_emit(ctx, 1, 0);	/* 00000001 */
		xf_emit(ctx, 1, 0);	/* 00000001 tesla UNK1140 */
	}
	xf_emit(ctx, 1, 0x11);		/* 3f/7f DST_FORMAT */
	xf_emit(ctx, 1, 1);		/* 00000001 DST_LINEAR */
	xf_emit(ctx, 1, 0);		/* 00000007 PATTERN_COLOR_FORMAT */
	xf_emit(ctx, 2, 0);		/* ffffffff PATTERN_MONO_COLOR */
	xf_emit(ctx, 1, 0);		/* 00000001 PATTERN_MONO_FORMAT */
	xf_emit(ctx, 2, 0);		/* ffffffff PATTERN_MONO_BITMAP */
	xf_emit(ctx, 1, 0);		/* 00000003 PATTERN_SELECT */
	xf_emit(ctx, 1, 0);		/* 000000ff ROP */
	xf_emit(ctx, 1, 0);		/* ffffffff BETA1 */
	xf_emit(ctx, 1, 0);		/* ffffffff BETA4 */
	xf_emit(ctx, 1, 0);		/* 00000007 OPERATION */
	xf_emit(ctx, 0x50, 0);		/* 10x ffffff, ffffff, ffffff, ffffff, 3 PATTERN */
}