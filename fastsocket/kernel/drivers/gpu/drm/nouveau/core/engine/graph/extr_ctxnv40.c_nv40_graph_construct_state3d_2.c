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
 int /*<<< orphan*/  cp_ctx (struct nouveau_grctx*,int,int) ; 
 int /*<<< orphan*/  gr_def (struct nouveau_grctx*,int,int) ; 
 int nv40_graph_vs_count (struct nouveau_device*) ; 

__attribute__((used)) static void
nv40_graph_construct_state3d_2(struct nouveau_grctx *ctx)
{
	struct nouveau_device *device = ctx->device;
	int i;

	cp_ctx(ctx, 0x402000, 1);
	cp_ctx(ctx, 0x402404, device->chipset == 0x40 ? 1 : 2);
	switch (device->chipset) {
	case 0x40:
		gr_def(ctx, 0x402404, 0x00000001);
		break;
	case 0x4c:
	case 0x4e:
	case 0x67:
		gr_def(ctx, 0x402404, 0x00000020);
		break;
	case 0x46:
	case 0x49:
	case 0x4b:
		gr_def(ctx, 0x402404, 0x00000421);
		break;
	default:
		gr_def(ctx, 0x402404, 0x00000021);
	}
	if (device->chipset != 0x40)
		gr_def(ctx, 0x402408, 0x030c30c3);
	switch (device->chipset) {
	case 0x44:
	case 0x46:
	case 0x4a:
	case 0x4c:
	case 0x4e:
	case 0x67:
		cp_ctx(ctx, 0x402440, 1);
		gr_def(ctx, 0x402440, 0x00011001);
		break;
	default:
		break;
	}
	cp_ctx(ctx, 0x402480, device->chipset == 0x40 ? 8 : 9);
	gr_def(ctx, 0x402488, 0x3e020200);
	gr_def(ctx, 0x40248c, 0x00ffffff);
	switch (device->chipset) {
	case 0x40:
		gr_def(ctx, 0x402490, 0x60103f00);
		break;
	case 0x47:
		gr_def(ctx, 0x402490, 0x40103f00);
		break;
	case 0x41:
	case 0x42:
	case 0x49:
	case 0x4b:
		gr_def(ctx, 0x402490, 0x20103f00);
		break;
	default:
		gr_def(ctx, 0x402490, 0x0c103f00);
		break;
	}
	gr_def(ctx, 0x40249c, device->chipset <= 0x43 ?
			      0x00020000 : 0x00040000);
	cp_ctx(ctx, 0x402500, 31);
	gr_def(ctx, 0x402530, 0x00008100);
	if (device->chipset == 0x40)
		cp_ctx(ctx, 0x40257c, 6);
	cp_ctx(ctx, 0x402594, 16);
	cp_ctx(ctx, 0x402800, 17);
	gr_def(ctx, 0x402800, 0x00000001);
	switch (device->chipset) {
	case 0x47:
	case 0x49:
	case 0x4b:
		cp_ctx(ctx, 0x402864, 1);
		gr_def(ctx, 0x402864, 0x00001001);
		cp_ctx(ctx, 0x402870, 3);
		gr_def(ctx, 0x402878, 0x00000003);
		if (device->chipset != 0x47) { /* belong at end!! */
			cp_ctx(ctx, 0x402900, 1);
			cp_ctx(ctx, 0x402940, 1);
			cp_ctx(ctx, 0x402980, 1);
			cp_ctx(ctx, 0x4029c0, 1);
			cp_ctx(ctx, 0x402a00, 1);
			cp_ctx(ctx, 0x402a40, 1);
			cp_ctx(ctx, 0x402a80, 1);
			cp_ctx(ctx, 0x402ac0, 1);
		}
		break;
	case 0x40:
		cp_ctx(ctx, 0x402844, 1);
		gr_def(ctx, 0x402844, 0x00000001);
		cp_ctx(ctx, 0x402850, 1);
		break;
	default:
		cp_ctx(ctx, 0x402844, 1);
		gr_def(ctx, 0x402844, 0x00001001);
		cp_ctx(ctx, 0x402850, 2);
		gr_def(ctx, 0x402854, 0x00000003);
		break;
	}

	cp_ctx(ctx, 0x402c00, 4);
	gr_def(ctx, 0x402c00, device->chipset == 0x40 ?
			      0x80800001 : 0x00888001);
	switch (device->chipset) {
	case 0x47:
	case 0x49:
	case 0x4b:
		cp_ctx(ctx, 0x402c20, 40);
		for (i = 0; i < 32; i++)
			gr_def(ctx, 0x402c40 + (i * 4), 0xffffffff);
		cp_ctx(ctx, 0x4030b8, 13);
		gr_def(ctx, 0x4030dc, 0x00000005);
		gr_def(ctx, 0x4030e8, 0x0000ffff);
		break;
	default:
		cp_ctx(ctx, 0x402c10, 4);
		if (device->chipset == 0x40)
			cp_ctx(ctx, 0x402c20, 36);
		else
		if (device->chipset <= 0x42)
			cp_ctx(ctx, 0x402c20, 24);
		else
		if (device->chipset <= 0x4a)
			cp_ctx(ctx, 0x402c20, 16);
		else
			cp_ctx(ctx, 0x402c20, 8);
		cp_ctx(ctx, 0x402cb0, device->chipset == 0x40 ? 12 : 13);
		gr_def(ctx, 0x402cd4, 0x00000005);
		if (device->chipset != 0x40)
			gr_def(ctx, 0x402ce0, 0x0000ffff);
		break;
	}

	cp_ctx(ctx, 0x403400, device->chipset == 0x40 ? 4 : 3);
	cp_ctx(ctx, 0x403410, device->chipset == 0x40 ? 4 : 3);
	cp_ctx(ctx, 0x403420, nv40_graph_vs_count(ctx->device));
	for (i = 0; i < nv40_graph_vs_count(ctx->device); i++)
		gr_def(ctx, 0x403420 + (i * 4), 0x00005555);

	if (device->chipset != 0x40) {
		cp_ctx(ctx, 0x403600, 1);
		gr_def(ctx, 0x403600, 0x00000001);
	}
	cp_ctx(ctx, 0x403800, 1);

	cp_ctx(ctx, 0x403c18, 1);
	gr_def(ctx, 0x403c18, 0x00000001);
	switch (device->chipset) {
	case 0x46:
	case 0x47:
	case 0x49:
	case 0x4b:
		cp_ctx(ctx, 0x405018, 1);
		gr_def(ctx, 0x405018, 0x08e00001);
		cp_ctx(ctx, 0x405c24, 1);
		gr_def(ctx, 0x405c24, 0x000e3000);
		break;
	}
	if (device->chipset != 0x4e)
		cp_ctx(ctx, 0x405800, 11);
	cp_ctx(ctx, 0x407000, 1);
}