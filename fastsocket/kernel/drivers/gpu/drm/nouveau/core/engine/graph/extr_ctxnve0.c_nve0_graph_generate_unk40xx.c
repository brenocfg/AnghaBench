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
nve0_graph_generate_unk40xx(struct nvc0_graph_priv *priv)
{
	nv_wr32(priv, 0x404010, 0x0);
	nv_wr32(priv, 0x404014, 0x0);
	nv_wr32(priv, 0x404018, 0x0);
	nv_wr32(priv, 0x40401c, 0x0);
	nv_wr32(priv, 0x404020, 0x0);
	nv_wr32(priv, 0x404024, 0xe000);
	nv_wr32(priv, 0x404028, 0x0);
	nv_wr32(priv, 0x4040a8, 0x0);
	nv_wr32(priv, 0x4040ac, 0x0);
	nv_wr32(priv, 0x4040b0, 0x0);
	nv_wr32(priv, 0x4040b4, 0x0);
	nv_wr32(priv, 0x4040b8, 0x0);
	nv_wr32(priv, 0x4040bc, 0x0);
	nv_wr32(priv, 0x4040c0, 0x0);
	nv_wr32(priv, 0x4040c4, 0x0);
	nv_wr32(priv, 0x4040c8, 0xf800008f);
	nv_wr32(priv, 0x4040d0, 0x0);
	nv_wr32(priv, 0x4040d4, 0x0);
	nv_wr32(priv, 0x4040d8, 0x0);
	nv_wr32(priv, 0x4040dc, 0x0);
	nv_wr32(priv, 0x4040e0, 0x0);
	nv_wr32(priv, 0x4040e4, 0x0);
	nv_wr32(priv, 0x4040e8, 0x1000);
	nv_wr32(priv, 0x4040f8, 0x0);
	nv_wr32(priv, 0x404130, 0x0);
	nv_wr32(priv, 0x404134, 0x0);
	nv_wr32(priv, 0x404138, 0x20000040);
	nv_wr32(priv, 0x404150, 0x2e);
	nv_wr32(priv, 0x404154, 0x400);
	nv_wr32(priv, 0x404158, 0x200);
	nv_wr32(priv, 0x404164, 0x55);
	nv_wr32(priv, 0x4041a0, 0x0);
	nv_wr32(priv, 0x4041a4, 0x0);
	nv_wr32(priv, 0x4041a8, 0x0);
	nv_wr32(priv, 0x4041ac, 0x0);
	nv_wr32(priv, 0x404200, 0x0);
	nv_wr32(priv, 0x404204, 0x0);
	nv_wr32(priv, 0x404208, 0x0);
	nv_wr32(priv, 0x40420c, 0x0);
}