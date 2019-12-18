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
typedef  int u32 ;
struct nouveau_grctx {struct nouveau_device* device; } ;
struct nouveau_device {int chipset; } ;

/* Variables and functions */
 scalar_t__ IS_NVA3F (int) ; 
 scalar_t__ IS_NVAAF (int) ; 
 int /*<<< orphan*/  cp_ctx (struct nouveau_grctx*,int,int) ; 
 int /*<<< orphan*/  gr_def (struct nouveau_grctx*,int,int) ; 
 int /*<<< orphan*/  nv50_graph_construct_mmio_ddata (struct nouveau_grctx*) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 

__attribute__((used)) static void
nv50_graph_construct_mmio(struct nouveau_grctx *ctx)
{
	struct nouveau_device *device = ctx->device;
	int i, j;
	int offset, base;
	u32 units = nv_rd32 (ctx->device, 0x1540);

	/* 0800: DISPATCH */
	cp_ctx(ctx, 0x400808, 7);
	gr_def(ctx, 0x400814, 0x00000030);
	cp_ctx(ctx, 0x400834, 0x32);
	if (device->chipset == 0x50) {
		gr_def(ctx, 0x400834, 0xff400040);
		gr_def(ctx, 0x400838, 0xfff00080);
		gr_def(ctx, 0x40083c, 0xfff70090);
		gr_def(ctx, 0x400840, 0xffe806a8);
	}
	gr_def(ctx, 0x400844, 0x00000002);
	if (IS_NVA3F(device->chipset))
		gr_def(ctx, 0x400894, 0x00001000);
	gr_def(ctx, 0x4008e8, 0x00000003);
	gr_def(ctx, 0x4008ec, 0x00001000);
	if (device->chipset == 0x50)
		cp_ctx(ctx, 0x400908, 0xb);
	else if (device->chipset < 0xa0)
		cp_ctx(ctx, 0x400908, 0xc);
	else
		cp_ctx(ctx, 0x400908, 0xe);

	if (device->chipset >= 0xa0)
		cp_ctx(ctx, 0x400b00, 0x1);
	if (IS_NVA3F(device->chipset)) {
		cp_ctx(ctx, 0x400b10, 0x1);
		gr_def(ctx, 0x400b10, 0x0001629d);
		cp_ctx(ctx, 0x400b20, 0x1);
		gr_def(ctx, 0x400b20, 0x0001629d);
	}

	nv50_graph_construct_mmio_ddata(ctx);

	/* 0C00: VFETCH */
	cp_ctx(ctx, 0x400c08, 0x2);
	gr_def(ctx, 0x400c08, 0x0000fe0c);

	/* 1000 */
	if (device->chipset < 0xa0) {
		cp_ctx(ctx, 0x401008, 0x4);
		gr_def(ctx, 0x401014, 0x00001000);
	} else if (!IS_NVA3F(device->chipset)) {
		cp_ctx(ctx, 0x401008, 0x5);
		gr_def(ctx, 0x401018, 0x00001000);
	} else {
		cp_ctx(ctx, 0x401008, 0x5);
		gr_def(ctx, 0x401018, 0x00004000);
	}

	/* 1400 */
	cp_ctx(ctx, 0x401400, 0x8);
	cp_ctx(ctx, 0x401424, 0x3);
	if (device->chipset == 0x50)
		gr_def(ctx, 0x40142c, 0x0001fd87);
	else
		gr_def(ctx, 0x40142c, 0x00000187);
	cp_ctx(ctx, 0x401540, 0x5);
	gr_def(ctx, 0x401550, 0x00001018);

	/* 1800: STREAMOUT */
	cp_ctx(ctx, 0x401814, 0x1);
	gr_def(ctx, 0x401814, 0x000000ff);
	if (device->chipset == 0x50) {
		cp_ctx(ctx, 0x40181c, 0xe);
		gr_def(ctx, 0x401850, 0x00000004);
	} else if (device->chipset < 0xa0) {
		cp_ctx(ctx, 0x40181c, 0xf);
		gr_def(ctx, 0x401854, 0x00000004);
	} else {
		cp_ctx(ctx, 0x40181c, 0x13);
		gr_def(ctx, 0x401864, 0x00000004);
	}

	/* 1C00 */
	cp_ctx(ctx, 0x401c00, 0x1);
	switch (device->chipset) {
	case 0x50:
		gr_def(ctx, 0x401c00, 0x0001005f);
		break;
	case 0x84:
	case 0x86:
	case 0x94:
		gr_def(ctx, 0x401c00, 0x044d00df);
		break;
	case 0x92:
	case 0x96:
	case 0x98:
	case 0xa0:
	case 0xaa:
	case 0xac:
		gr_def(ctx, 0x401c00, 0x042500df);
		break;
	case 0xa3:
	case 0xa5:
	case 0xa8:
	case 0xaf:
		gr_def(ctx, 0x401c00, 0x142500df);
		break;
	}

	/* 2000 */

	/* 2400 */
	cp_ctx(ctx, 0x402400, 0x1);
	if (device->chipset == 0x50)
		cp_ctx(ctx, 0x402408, 0x1);
	else
		cp_ctx(ctx, 0x402408, 0x2);
	gr_def(ctx, 0x402408, 0x00000600);

	/* 2800: CSCHED */
	cp_ctx(ctx, 0x402800, 0x1);
	if (device->chipset == 0x50)
		gr_def(ctx, 0x402800, 0x00000006);

	/* 2C00: ZCULL */
	cp_ctx(ctx, 0x402c08, 0x6);
	if (device->chipset != 0x50)
		gr_def(ctx, 0x402c14, 0x01000000);
	gr_def(ctx, 0x402c18, 0x000000ff);
	if (device->chipset == 0x50)
		cp_ctx(ctx, 0x402ca0, 0x1);
	else
		cp_ctx(ctx, 0x402ca0, 0x2);
	if (device->chipset < 0xa0)
		gr_def(ctx, 0x402ca0, 0x00000400);
	else if (!IS_NVA3F(device->chipset))
		gr_def(ctx, 0x402ca0, 0x00000800);
	else
		gr_def(ctx, 0x402ca0, 0x00000400);
	cp_ctx(ctx, 0x402cac, 0x4);

	/* 3000: ENG2D */
	cp_ctx(ctx, 0x403004, 0x1);
	gr_def(ctx, 0x403004, 0x00000001);

	/* 3400 */
	if (device->chipset >= 0xa0) {
		cp_ctx(ctx, 0x403404, 0x1);
		gr_def(ctx, 0x403404, 0x00000001);
	}

	/* 5000: CCACHE */
	cp_ctx(ctx, 0x405000, 0x1);
	switch (device->chipset) {
	case 0x50:
		gr_def(ctx, 0x405000, 0x00300080);
		break;
	case 0x84:
	case 0xa0:
	case 0xa3:
	case 0xa5:
	case 0xa8:
	case 0xaa:
	case 0xac:
	case 0xaf:
		gr_def(ctx, 0x405000, 0x000e0080);
		break;
	case 0x86:
	case 0x92:
	case 0x94:
	case 0x96:
	case 0x98:
		gr_def(ctx, 0x405000, 0x00000080);
		break;
	}
	cp_ctx(ctx, 0x405014, 0x1);
	gr_def(ctx, 0x405014, 0x00000004);
	cp_ctx(ctx, 0x40501c, 0x1);
	cp_ctx(ctx, 0x405024, 0x1);
	cp_ctx(ctx, 0x40502c, 0x1);

	/* 6000? */
	if (device->chipset == 0x50)
		cp_ctx(ctx, 0x4063e0, 0x1);

	/* 6800: M2MF */
	if (device->chipset < 0x90) {
		cp_ctx(ctx, 0x406814, 0x2b);
		gr_def(ctx, 0x406818, 0x00000f80);
		gr_def(ctx, 0x406860, 0x007f0080);
		gr_def(ctx, 0x40689c, 0x007f0080);
	} else {
		cp_ctx(ctx, 0x406814, 0x4);
		if (device->chipset == 0x98)
			gr_def(ctx, 0x406818, 0x00000f80);
		else
			gr_def(ctx, 0x406818, 0x00001f80);
		if (IS_NVA3F(device->chipset))
			gr_def(ctx, 0x40681c, 0x00000030);
		cp_ctx(ctx, 0x406830, 0x3);
	}

	/* 7000: per-ROP group state */
	for (i = 0; i < 8; i++) {
		if (units & (1<<(i+16))) {
			cp_ctx(ctx, 0x407000 + (i<<8), 3);
			if (device->chipset == 0x50)
				gr_def(ctx, 0x407000 + (i<<8), 0x1b74f820);
			else if (device->chipset != 0xa5)
				gr_def(ctx, 0x407000 + (i<<8), 0x3b74f821);
			else
				gr_def(ctx, 0x407000 + (i<<8), 0x7b74f821);
			gr_def(ctx, 0x407004 + (i<<8), 0x89058001);

			if (device->chipset == 0x50) {
				cp_ctx(ctx, 0x407010 + (i<<8), 1);
			} else if (device->chipset < 0xa0) {
				cp_ctx(ctx, 0x407010 + (i<<8), 2);
				gr_def(ctx, 0x407010 + (i<<8), 0x00001000);
				gr_def(ctx, 0x407014 + (i<<8), 0x0000001f);
			} else {
				cp_ctx(ctx, 0x407010 + (i<<8), 3);
				gr_def(ctx, 0x407010 + (i<<8), 0x00001000);
				if (device->chipset != 0xa5)
					gr_def(ctx, 0x407014 + (i<<8), 0x000000ff);
				else
					gr_def(ctx, 0x407014 + (i<<8), 0x000001ff);
			}

			cp_ctx(ctx, 0x407080 + (i<<8), 4);
			if (device->chipset != 0xa5)
				gr_def(ctx, 0x407080 + (i<<8), 0x027c10fa);
			else
				gr_def(ctx, 0x407080 + (i<<8), 0x827c10fa);
			if (device->chipset == 0x50)
				gr_def(ctx, 0x407084 + (i<<8), 0x000000c0);
			else
				gr_def(ctx, 0x407084 + (i<<8), 0x400000c0);
			gr_def(ctx, 0x407088 + (i<<8), 0xb7892080);

			if (device->chipset < 0xa0)
				cp_ctx(ctx, 0x407094 + (i<<8), 1);
			else if (!IS_NVA3F(device->chipset))
				cp_ctx(ctx, 0x407094 + (i<<8), 3);
			else {
				cp_ctx(ctx, 0x407094 + (i<<8), 4);
				gr_def(ctx, 0x4070a0 + (i<<8), 1);
			}
		}
	}

	cp_ctx(ctx, 0x407c00, 0x3);
	if (device->chipset < 0x90)
		gr_def(ctx, 0x407c00, 0x00010040);
	else if (device->chipset < 0xa0)
		gr_def(ctx, 0x407c00, 0x00390040);
	else
		gr_def(ctx, 0x407c00, 0x003d0040);
	gr_def(ctx, 0x407c08, 0x00000022);
	if (device->chipset >= 0xa0) {
		cp_ctx(ctx, 0x407c10, 0x3);
		cp_ctx(ctx, 0x407c20, 0x1);
		cp_ctx(ctx, 0x407c2c, 0x1);
	}

	if (device->chipset < 0xa0) {
		cp_ctx(ctx, 0x407d00, 0x9);
	} else {
		cp_ctx(ctx, 0x407d00, 0x15);
	}
	if (device->chipset == 0x98)
		gr_def(ctx, 0x407d08, 0x00380040);
	else {
		if (device->chipset < 0x90)
			gr_def(ctx, 0x407d08, 0x00010040);
		else if (device->chipset < 0xa0)
			gr_def(ctx, 0x407d08, 0x00390040);
		else
			gr_def(ctx, 0x407d08, 0x003d0040);
		gr_def(ctx, 0x407d0c, 0x00000022);
	}

	/* 8000+: per-TP state */
	for (i = 0; i < 10; i++) {
		if (units & (1<<i)) {
			if (device->chipset < 0xa0)
				base = 0x408000 + (i<<12);
			else
				base = 0x408000 + (i<<11);
			if (device->chipset < 0xa0)
				offset = base + 0xc00;
			else
				offset = base + 0x80;
			cp_ctx(ctx, offset + 0x00, 1);
			gr_def(ctx, offset + 0x00, 0x0000ff0a);
			cp_ctx(ctx, offset + 0x08, 1);

			/* per-MP state */
			for (j = 0; j < (device->chipset < 0xa0 ? 2 : 4); j++) {
				if (!(units & (1 << (j+24)))) continue;
				if (device->chipset < 0xa0)
					offset = base + 0x200 + (j<<7);
				else
					offset = base + 0x100 + (j<<7);
				cp_ctx(ctx, offset, 0x20);
				gr_def(ctx, offset + 0x00, 0x01800000);
				gr_def(ctx, offset + 0x04, 0x00160000);
				gr_def(ctx, offset + 0x08, 0x01800000);
				gr_def(ctx, offset + 0x18, 0x0003ffff);
				switch (device->chipset) {
				case 0x50:
					gr_def(ctx, offset + 0x1c, 0x00080000);
					break;
				case 0x84:
					gr_def(ctx, offset + 0x1c, 0x00880000);
					break;
				case 0x86:
					gr_def(ctx, offset + 0x1c, 0x018c0000);
					break;
				case 0x92:
				case 0x96:
				case 0x98:
					gr_def(ctx, offset + 0x1c, 0x118c0000);
					break;
				case 0x94:
					gr_def(ctx, offset + 0x1c, 0x10880000);
					break;
				case 0xa0:
				case 0xa5:
					gr_def(ctx, offset + 0x1c, 0x310c0000);
					break;
				case 0xa3:
				case 0xa8:
				case 0xaa:
				case 0xac:
				case 0xaf:
					gr_def(ctx, offset + 0x1c, 0x300c0000);
					break;
				}
				gr_def(ctx, offset + 0x40, 0x00010401);
				if (device->chipset == 0x50)
					gr_def(ctx, offset + 0x48, 0x00000040);
				else
					gr_def(ctx, offset + 0x48, 0x00000078);
				gr_def(ctx, offset + 0x50, 0x000000bf);
				gr_def(ctx, offset + 0x58, 0x00001210);
				if (device->chipset == 0x50)
					gr_def(ctx, offset + 0x5c, 0x00000080);
				else
					gr_def(ctx, offset + 0x5c, 0x08000080);
				if (device->chipset >= 0xa0)
					gr_def(ctx, offset + 0x68, 0x0000003e);
			}

			if (device->chipset < 0xa0)
				cp_ctx(ctx, base + 0x300, 0x4);
			else
				cp_ctx(ctx, base + 0x300, 0x5);
			if (device->chipset == 0x50)
				gr_def(ctx, base + 0x304, 0x00007070);
			else if (device->chipset < 0xa0)
				gr_def(ctx, base + 0x304, 0x00027070);
			else if (!IS_NVA3F(device->chipset))
				gr_def(ctx, base + 0x304, 0x01127070);
			else
				gr_def(ctx, base + 0x304, 0x05127070);

			if (device->chipset < 0xa0)
				cp_ctx(ctx, base + 0x318, 1);
			else
				cp_ctx(ctx, base + 0x320, 1);
			if (device->chipset == 0x50)
				gr_def(ctx, base + 0x318, 0x0003ffff);
			else if (device->chipset < 0xa0)
				gr_def(ctx, base + 0x318, 0x03ffffff);
			else
				gr_def(ctx, base + 0x320, 0x07ffffff);

			if (device->chipset < 0xa0)
				cp_ctx(ctx, base + 0x324, 5);
			else
				cp_ctx(ctx, base + 0x328, 4);

			if (device->chipset < 0xa0) {
				cp_ctx(ctx, base + 0x340, 9);
				offset = base + 0x340;
			} else if (!IS_NVA3F(device->chipset)) {
				cp_ctx(ctx, base + 0x33c, 0xb);
				offset = base + 0x344;
			} else {
				cp_ctx(ctx, base + 0x33c, 0xd);
				offset = base + 0x344;
			}
			gr_def(ctx, offset + 0x0, 0x00120407);
			gr_def(ctx, offset + 0x4, 0x05091507);
			if (device->chipset == 0x84)
				gr_def(ctx, offset + 0x8, 0x05100202);
			else
				gr_def(ctx, offset + 0x8, 0x05010202);
			gr_def(ctx, offset + 0xc, 0x00030201);
			if (device->chipset == 0xa3)
				cp_ctx(ctx, base + 0x36c, 1);

			cp_ctx(ctx, base + 0x400, 2);
			gr_def(ctx, base + 0x404, 0x00000040);
			cp_ctx(ctx, base + 0x40c, 2);
			gr_def(ctx, base + 0x40c, 0x0d0c0b0a);
			gr_def(ctx, base + 0x410, 0x00141210);

			if (device->chipset < 0xa0)
				offset = base + 0x800;
			else
				offset = base + 0x500;
			cp_ctx(ctx, offset, 6);
			gr_def(ctx, offset + 0x0, 0x000001f0);
			gr_def(ctx, offset + 0x4, 0x00000001);
			gr_def(ctx, offset + 0x8, 0x00000003);
			if (device->chipset == 0x50 || IS_NVAAF(device->chipset))
				gr_def(ctx, offset + 0xc, 0x00008000);
			gr_def(ctx, offset + 0x14, 0x00039e00);
			cp_ctx(ctx, offset + 0x1c, 2);
			if (device->chipset == 0x50)
				gr_def(ctx, offset + 0x1c, 0x00000040);
			else
				gr_def(ctx, offset + 0x1c, 0x00000100);
			gr_def(ctx, offset + 0x20, 0x00003800);

			if (device->chipset >= 0xa0) {
				cp_ctx(ctx, base + 0x54c, 2);
				if (!IS_NVA3F(device->chipset))
					gr_def(ctx, base + 0x54c, 0x003fe006);
				else
					gr_def(ctx, base + 0x54c, 0x003fe007);
				gr_def(ctx, base + 0x550, 0x003fe000);
			}

			if (device->chipset < 0xa0)
				offset = base + 0xa00;
			else
				offset = base + 0x680;
			cp_ctx(ctx, offset, 1);
			gr_def(ctx, offset, 0x00404040);

			if (device->chipset < 0xa0)
				offset = base + 0xe00;
			else
				offset = base + 0x700;
			cp_ctx(ctx, offset, 2);
			if (device->chipset < 0xa0)
				gr_def(ctx, offset, 0x0077f005);
			else if (device->chipset == 0xa5)
				gr_def(ctx, offset, 0x6cf7f007);
			else if (device->chipset == 0xa8)
				gr_def(ctx, offset, 0x6cfff007);
			else if (device->chipset == 0xac)
				gr_def(ctx, offset, 0x0cfff007);
			else
				gr_def(ctx, offset, 0x0cf7f007);
			if (device->chipset == 0x50)
				gr_def(ctx, offset + 0x4, 0x00007fff);
			else if (device->chipset < 0xa0)
				gr_def(ctx, offset + 0x4, 0x003f7fff);
			else
				gr_def(ctx, offset + 0x4, 0x02bf7fff);
			cp_ctx(ctx, offset + 0x2c, 1);
			if (device->chipset == 0x50) {
				cp_ctx(ctx, offset + 0x50, 9);
				gr_def(ctx, offset + 0x54, 0x000003ff);
				gr_def(ctx, offset + 0x58, 0x00000003);
				gr_def(ctx, offset + 0x5c, 0x00000003);
				gr_def(ctx, offset + 0x60, 0x000001ff);
				gr_def(ctx, offset + 0x64, 0x0000001f);
				gr_def(ctx, offset + 0x68, 0x0000000f);
				gr_def(ctx, offset + 0x6c, 0x0000000f);
			} else if (device->chipset < 0xa0) {
				cp_ctx(ctx, offset + 0x50, 1);
				cp_ctx(ctx, offset + 0x70, 1);
			} else {
				cp_ctx(ctx, offset + 0x50, 1);
				cp_ctx(ctx, offset + 0x60, 5);
			}
		}
	}
}