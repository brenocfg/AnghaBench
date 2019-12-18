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
nve0_graph_generate_unk64xx(struct nvc0_graph_priv *priv)
{
	nv_wr32(priv, 0x4064a8, 0x0);
	nv_wr32(priv, 0x4064ac, 0x3fff);
	nv_wr32(priv, 0x4064b4, 0x0);
	nv_wr32(priv, 0x4064b8, 0x0);
	nv_wr32(priv, 0x4064c0, 0x801a00f0);
	nv_wr32(priv, 0x4064c4, 0x192ffff);
	nv_wr32(priv, 0x4064c8, 0x1800600);
	nv_wr32(priv, 0x4064cc, 0x0);
	nv_wr32(priv, 0x4064d0, 0x0);
	nv_wr32(priv, 0x4064d4, 0x0);
	nv_wr32(priv, 0x4064d8, 0x0);
	nv_wr32(priv, 0x4064dc, 0x0);
	nv_wr32(priv, 0x4064e0, 0x0);
	nv_wr32(priv, 0x4064e4, 0x0);
	nv_wr32(priv, 0x4064e8, 0x0);
	nv_wr32(priv, 0x4064ec, 0x0);
	nv_wr32(priv, 0x4064fc, 0x22a);
}