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
nve0_graph_init_regs(struct nvc0_graph_priv *priv)
{
	nv_wr32(priv, 0x400080, 0x003083c2);
	nv_wr32(priv, 0x400088, 0x0001ffe7);
	nv_wr32(priv, 0x40008c, 0x00000000);
	nv_wr32(priv, 0x400090, 0x00000030);
	nv_wr32(priv, 0x40013c, 0x003901f7);
	nv_wr32(priv, 0x400140, 0x00000100);
	nv_wr32(priv, 0x400144, 0x00000000);
	nv_wr32(priv, 0x400148, 0x00000110);
	nv_wr32(priv, 0x400138, 0x00000000);
	nv_wr32(priv, 0x400130, 0x00000000);
	nv_wr32(priv, 0x400134, 0x00000000);
	nv_wr32(priv, 0x400124, 0x00000002);
}