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
nvc0_grctx_generate_macro(struct nvc0_graph_priv *priv)
{
	nv_wr32(priv, 0x404404, 0x00000000);
	nv_wr32(priv, 0x404408, 0x00000000);
	nv_wr32(priv, 0x40440c, 0x00000000);
	nv_wr32(priv, 0x404410, 0x00000000);
	nv_wr32(priv, 0x404414, 0x00000000);
	nv_wr32(priv, 0x404418, 0x00000000);
	nv_wr32(priv, 0x40441c, 0x00000000);
	nv_wr32(priv, 0x404420, 0x00000000);
	nv_wr32(priv, 0x404424, 0x00000000);
	nv_wr32(priv, 0x404428, 0x00000000);
	nv_wr32(priv, 0x40442c, 0x00000000);
	nv_wr32(priv, 0x404430, 0x00000000);
	nv_wr32(priv, 0x404434, 0x00000000);
	nv_wr32(priv, 0x404438, 0x00000000);
	nv_wr32(priv, 0x404460, 0x00000000);
	nv_wr32(priv, 0x404464, 0x00000000);
	nv_wr32(priv, 0x404468, 0x00ffffff);
	nv_wr32(priv, 0x40446c, 0x00000000);
	nv_wr32(priv, 0x404480, 0x00000001);
	nv_wr32(priv, 0x404498, 0x00000001);
}