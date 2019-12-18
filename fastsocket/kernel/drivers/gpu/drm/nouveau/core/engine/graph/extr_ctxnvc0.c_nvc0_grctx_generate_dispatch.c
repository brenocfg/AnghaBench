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
struct nvc0_graph_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int,int) ; 

__attribute__((used)) static void
nvc0_grctx_generate_dispatch(struct nvc0_graph_priv *priv)
{
	int i;

	nv_wr32(priv, 0x404004, 0x00000000);
	nv_wr32(priv, 0x404008, 0x00000000);
	nv_wr32(priv, 0x40400c, 0x00000000);
	nv_wr32(priv, 0x404010, 0x00000000);
	nv_wr32(priv, 0x404014, 0x00000000);
	nv_wr32(priv, 0x404018, 0x00000000);
	nv_wr32(priv, 0x40401c, 0x00000000);
	nv_wr32(priv, 0x404020, 0x00000000);
	nv_wr32(priv, 0x404024, 0x00000000);
	nv_wr32(priv, 0x404028, 0x00000000);
	nv_wr32(priv, 0x40402c, 0x00000000);
	nv_wr32(priv, 0x404044, 0x00000000);
	nv_wr32(priv, 0x404094, 0x00000000);
	nv_wr32(priv, 0x404098, 0x00000000);
	nv_wr32(priv, 0x40409c, 0x00000000);
	nv_wr32(priv, 0x4040a0, 0x00000000);
	nv_wr32(priv, 0x4040a4, 0x00000000);
	nv_wr32(priv, 0x4040a8, 0x00000000);
	nv_wr32(priv, 0x4040ac, 0x00000000);
	nv_wr32(priv, 0x4040b0, 0x00000000);
	nv_wr32(priv, 0x4040b4, 0x00000000);
	nv_wr32(priv, 0x4040b8, 0x00000000);
	nv_wr32(priv, 0x4040bc, 0x00000000);
	nv_wr32(priv, 0x4040c0, 0x00000000);
	nv_wr32(priv, 0x4040c4, 0x00000000);
	nv_wr32(priv, 0x4040c8, 0xf0000087);
	nv_wr32(priv, 0x4040d4, 0x00000000);
	nv_wr32(priv, 0x4040d8, 0x00000000);
	nv_wr32(priv, 0x4040dc, 0x00000000);
	nv_wr32(priv, 0x4040e0, 0x00000000);
	nv_wr32(priv, 0x4040e4, 0x00000000);
	nv_wr32(priv, 0x4040e8, 0x00001000);
	nv_wr32(priv, 0x4040f8, 0x00000000);
	nv_wr32(priv, 0x404130, 0x00000000);
	nv_wr32(priv, 0x404134, 0x00000000);
	nv_wr32(priv, 0x404138, 0x20000040);
	nv_wr32(priv, 0x404150, 0x0000002e);
	nv_wr32(priv, 0x404154, 0x00000400);
	nv_wr32(priv, 0x404158, 0x00000200);
	nv_wr32(priv, 0x404164, 0x00000055);
	nv_wr32(priv, 0x404168, 0x00000000);
	nv_wr32(priv, 0x404174, 0x00000000);
	nv_wr32(priv, 0x404178, 0x00000000);
	nv_wr32(priv, 0x40417c, 0x00000000);
	for (i = 0; i < 8; i++)
		nv_wr32(priv, 0x404200 + (i * 4), 0x00000000); /* subc */
}