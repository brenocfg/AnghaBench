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
 int /*<<< orphan*/  xf_emit (struct nouveau_grctx*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nv50_graph_construct_gene_dispatch(struct nouveau_grctx *ctx)
{
	/* start of strand 0 */
	struct nouveau_device *device = ctx->device;
	/* SEEK */
	if (device->chipset == 0x50)
		xf_emit(ctx, 5, 0);
	else if (!IS_NVA3F(device->chipset))
		xf_emit(ctx, 6, 0);
	else
		xf_emit(ctx, 4, 0);
	/* SEEK */
	/* the PGRAPH's internal FIFO */
	if (device->chipset == 0x50)
		xf_emit(ctx, 8*3, 0);
	else
		xf_emit(ctx, 0x100*3, 0);
	/* and another bonus slot?!? */
	xf_emit(ctx, 3, 0);
	/* and YET ANOTHER bonus slot? */
	if (IS_NVA3F(device->chipset))
		xf_emit(ctx, 3, 0);
	/* SEEK */
	/* CTX_SWITCH: caches of gr objects bound to subchannels. 8 values, last used index */
	xf_emit(ctx, 9, 0);
	/* SEEK */
	xf_emit(ctx, 9, 0);
	/* SEEK */
	xf_emit(ctx, 9, 0);
	/* SEEK */
	xf_emit(ctx, 9, 0);
	/* SEEK */
	if (device->chipset < 0x90)
		xf_emit(ctx, 4, 0);
	/* SEEK */
	xf_emit(ctx, 2, 0);
	/* SEEK */
	xf_emit(ctx, 6*2, 0);
	xf_emit(ctx, 2, 0);
	/* SEEK */
	xf_emit(ctx, 2, 0);
	/* SEEK */
	xf_emit(ctx, 6*2, 0);
	xf_emit(ctx, 2, 0);
	/* SEEK */
	if (device->chipset == 0x50)
		xf_emit(ctx, 0x1c, 0);
	else if (device->chipset < 0xa0)
		xf_emit(ctx, 0x1e, 0);
	else
		xf_emit(ctx, 0x22, 0);
	/* SEEK */
	xf_emit(ctx, 0x15, 0);
}