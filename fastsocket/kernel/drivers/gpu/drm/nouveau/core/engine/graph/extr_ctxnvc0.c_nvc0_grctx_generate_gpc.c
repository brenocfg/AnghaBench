#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvc0_graph_priv {int dummy; } ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 TYPE_1__* nv_device (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int,int) ; 

__attribute__((used)) static void
nvc0_grctx_generate_gpc(struct nvc0_graph_priv *priv)
{
	int chipset = nv_device(priv)->chipset;
	int i;

	/* GPC_BROADCAST */
	nv_wr32(priv, 0x418380, 0x00000016);
	nv_wr32(priv, 0x418400, 0x38004e00);
	nv_wr32(priv, 0x418404, 0x71e0ffff);
	nv_wr32(priv, 0x418408, 0x00000000);
	nv_wr32(priv, 0x41840c, 0x00001008);
	nv_wr32(priv, 0x418410, 0x0fff0fff);
	nv_wr32(priv, 0x418414, chipset != 0xd9 ? 0x00200fff : 0x02200fff);
	nv_wr32(priv, 0x418450, 0x00000000);
	nv_wr32(priv, 0x418454, 0x00000000);
	nv_wr32(priv, 0x418458, 0x00000000);
	nv_wr32(priv, 0x41845c, 0x00000000);
	nv_wr32(priv, 0x418460, 0x00000000);
	nv_wr32(priv, 0x418464, 0x00000000);
	nv_wr32(priv, 0x418468, 0x00000001);
	nv_wr32(priv, 0x41846c, 0x00000000);
	nv_wr32(priv, 0x418470, 0x00000000);
	nv_wr32(priv, 0x418600, 0x0000001f);
	nv_wr32(priv, 0x418684, 0x0000000f);
	nv_wr32(priv, 0x418700, 0x00000002);
	nv_wr32(priv, 0x418704, 0x00000080);
	nv_wr32(priv, 0x418708, 0x00000000);
	nv_wr32(priv, 0x41870c, chipset != 0xd9 ? 0x07c80000 : 0x00000000);
	nv_wr32(priv, 0x418710, 0x00000000);
	nv_wr32(priv, 0x418800, chipset != 0xd9 ? 0x0006860a : 0x7006860a);
	nv_wr32(priv, 0x418808, 0x00000000);
	nv_wr32(priv, 0x41880c, 0x00000000);
	nv_wr32(priv, 0x418810, 0x00000000);
	nv_wr32(priv, 0x418828, 0x00008442);
	if (chipset == 0xc1 || chipset == 0xd9)
		nv_wr32(priv, 0x418830, 0x10000001);
	else
		nv_wr32(priv, 0x418830, 0x00000001);
	nv_wr32(priv, 0x4188d8, 0x00000008);
	nv_wr32(priv, 0x4188e0, 0x01000000);
	nv_wr32(priv, 0x4188e8, 0x00000000);
	nv_wr32(priv, 0x4188ec, 0x00000000);
	nv_wr32(priv, 0x4188f0, 0x00000000);
	nv_wr32(priv, 0x4188f4, 0x00000000);
	nv_wr32(priv, 0x4188f8, 0x00000000);
	if (chipset == 0xd9)
		nv_wr32(priv, 0x4188fc, 0x20100008);
	else if (chipset == 0xc1)
		nv_wr32(priv, 0x4188fc, 0x00100018);
	else
		nv_wr32(priv, 0x4188fc, 0x00100000);
	nv_wr32(priv, 0x41891c, 0x00ff00ff);
	nv_wr32(priv, 0x418924, 0x00000000);
	nv_wr32(priv, 0x418928, 0x00ffff00);
	nv_wr32(priv, 0x41892c, 0x0000ff00);
	for (i = 0; i < 8; i++) {
		nv_wr32(priv, 0x418a00 + (i * 0x20), 0x00000000);
		nv_wr32(priv, 0x418a04 + (i * 0x20), 0x00000000);
		nv_wr32(priv, 0x418a08 + (i * 0x20), 0x00000000);
		nv_wr32(priv, 0x418a0c + (i * 0x20), 0x00010000);
		nv_wr32(priv, 0x418a10 + (i * 0x20), 0x00000000);
		nv_wr32(priv, 0x418a14 + (i * 0x20), 0x00000000);
		nv_wr32(priv, 0x418a18 + (i * 0x20), 0x00000000);
	}
	nv_wr32(priv, 0x418b00, chipset != 0xd9 ? 0x00000000 : 0x00000006);
	nv_wr32(priv, 0x418b08, 0x0a418820);
	nv_wr32(priv, 0x418b0c, 0x062080e6);
	nv_wr32(priv, 0x418b10, 0x020398a4);
	nv_wr32(priv, 0x418b14, 0x0e629062);
	nv_wr32(priv, 0x418b18, 0x0a418820);
	nv_wr32(priv, 0x418b1c, 0x000000e6);
	nv_wr32(priv, 0x418bb8, 0x00000103);
	nv_wr32(priv, 0x418c08, 0x00000001);
	nv_wr32(priv, 0x418c10, 0x00000000);
	nv_wr32(priv, 0x418c14, 0x00000000);
	nv_wr32(priv, 0x418c18, 0x00000000);
	nv_wr32(priv, 0x418c1c, 0x00000000);
	nv_wr32(priv, 0x418c20, 0x00000000);
	nv_wr32(priv, 0x418c24, 0x00000000);
	nv_wr32(priv, 0x418c28, 0x00000000);
	nv_wr32(priv, 0x418c2c, 0x00000000);
	if (chipset == 0xc1 || chipset == 0xd9)
		nv_wr32(priv, 0x418c6c, 0x00000001);
	nv_wr32(priv, 0x418c80, 0x20200004);
	nv_wr32(priv, 0x418c8c, 0x00000001);
	nv_wr32(priv, 0x419000, 0x00000780);
	nv_wr32(priv, 0x419004, 0x00000000);
	nv_wr32(priv, 0x419008, 0x00000000);
	nv_wr32(priv, 0x419014, 0x00000004);
}