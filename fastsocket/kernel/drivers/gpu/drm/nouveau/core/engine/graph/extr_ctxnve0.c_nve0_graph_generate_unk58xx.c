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
nve0_graph_generate_unk58xx(struct nvc0_graph_priv *priv)
{
	nv_wr32(priv, 0x405800, 0xf8000bf);
	nv_wr32(priv, 0x405830, 0x2180648);
	nv_wr32(priv, 0x405834, 0x8000000);
	nv_wr32(priv, 0x405838, 0x0);
	nv_wr32(priv, 0x405854, 0x0);
	nv_wr32(priv, 0x405870, 0x1);
	nv_wr32(priv, 0x405874, 0x1);
	nv_wr32(priv, 0x405878, 0x1);
	nv_wr32(priv, 0x40587c, 0x1);
	nv_wr32(priv, 0x405a00, 0x0);
	nv_wr32(priv, 0x405a04, 0x0);
	nv_wr32(priv, 0x405a18, 0x0);
	nv_wr32(priv, 0x405b00, 0x0);
	nv_wr32(priv, 0x405b10, 0x1000);
}