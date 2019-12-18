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
nv50_graph_construct_gene_csched(struct nouveau_grctx *ctx)
{
	struct nouveau_device *device = ctx->device;
	/* middle of strand 1 on pre-NVA0 [after eng2d], middle of strand 0 on NVAx */
	/* SEEK */
	xf_emit(ctx, 2, 0);		/* 00007fff WINDOW_OFFSET_XY... what is it doing here??? */
	xf_emit(ctx, 1, 0);		/* 00000001 tesla UNK1924 */
	xf_emit(ctx, 1, 0);		/* 00000003 WINDOW_ORIGIN */
	xf_emit(ctx, 1, 0x8100c12);	/* 1fffffff FP_INTERPOLANT_CTRL */
	xf_emit(ctx, 1, 0);		/* 000003ff */
	/* SEEK */
	xf_emit(ctx, 1, 0);		/* ffffffff turing UNK364 */
	xf_emit(ctx, 1, 0);		/* 0000000f turing UNK36C */
	xf_emit(ctx, 1, 0);		/* 0000ffff USER_PARAM_COUNT */
	xf_emit(ctx, 1, 0x100);		/* 00ffffff turing UNK384 */
	xf_emit(ctx, 1, 0);		/* 0000000f turing UNK2A0 */
	xf_emit(ctx, 1, 0);		/* 0000ffff GRIDID */
	xf_emit(ctx, 1, 0x10001);	/* ffffffff GRIDDIM_XY */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0x10001);	/* ffffffff BLOCKDIM_XY */
	xf_emit(ctx, 1, 1);		/* 0000ffff BLOCKDIM_Z */
	xf_emit(ctx, 1, 0x10001);	/* 00ffffff BLOCK_ALLOC */
	xf_emit(ctx, 1, 1);		/* 00000001 LANES32 */
	xf_emit(ctx, 1, 4);		/* 000000ff FP_REG_ALLOC_TEMP */
	xf_emit(ctx, 1, 2);		/* 00000003 REG_MODE */
	/* SEEK */
	xf_emit(ctx, 0x40, 0);		/* ffffffff USER_PARAM */
	switch (device->chipset) {
	case 0x50:
	case 0x92:
		xf_emit(ctx, 8, 0);	/* 7, 0, 0, 0, ... */
		xf_emit(ctx, 0x80, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 0x10*2, 0);	/* ffffffff, 1f */
		break;
	case 0x84:
		xf_emit(ctx, 8, 0);	/* 7, 0, 0, 0, ... */
		xf_emit(ctx, 0x60, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 0xc*2, 0);	/* ffffffff, 1f */
		break;
	case 0x94:
	case 0x96:
		xf_emit(ctx, 8, 0);	/* 7, 0, 0, 0, ... */
		xf_emit(ctx, 0x40, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 8*2, 0);	/* ffffffff, 1f */
		break;
	case 0x86:
	case 0x98:
		xf_emit(ctx, 4, 0);	/* f, 0, 0, 0 */
		xf_emit(ctx, 0x10, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 2*2, 0);	/* ffffffff, 1f */
		break;
	case 0xa0:
		xf_emit(ctx, 8, 0);	/* 7, 0, 0, 0, ... */
		xf_emit(ctx, 0xf0, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 0x1e*2, 0);	/* ffffffff, 1f */
		break;
	case 0xa3:
		xf_emit(ctx, 8, 0);	/* 7, 0, 0, 0, ... */
		xf_emit(ctx, 0x60, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 0xc*2, 0);	/* ffffffff, 1f */
		break;
	case 0xa5:
	case 0xaf:
		xf_emit(ctx, 8, 0);	/* 7, 0, 0, 0, ... */
		xf_emit(ctx, 0x30, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 6*2, 0);	/* ffffffff, 1f */
		break;
	case 0xaa:
		xf_emit(ctx, 0x12, 0);
		break;
	case 0xa8:
	case 0xac:
		xf_emit(ctx, 4, 0);	/* f, 0, 0, 0 */
		xf_emit(ctx, 0x10, 0);	/* fff */
		xf_emit(ctx, 2, 0);	/* ff, fff */
		xf_emit(ctx, 2*2, 0);	/* ffffffff, 1f */
		break;
	}
	xf_emit(ctx, 1, 0);		/* 0000000f */
	xf_emit(ctx, 1, 0);		/* 00000000 */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 0000001f */
	xf_emit(ctx, 4, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 00000003 turing UNK35C */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 4, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 00000003 turing UNK35C */
	xf_emit(ctx, 1, 0);		/* ffffffff */
	xf_emit(ctx, 1, 0);		/* 000000ff */
}