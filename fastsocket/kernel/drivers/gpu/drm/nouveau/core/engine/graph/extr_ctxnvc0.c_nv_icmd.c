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
typedef  int /*<<< orphan*/  u32 ;
struct nvc0_graph_priv {int dummy; } ;

/* Variables and functions */
 int nv_rd32 (struct nvc0_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int,int /*<<< orphan*/ ) ; 

void
nv_icmd(struct nvc0_graph_priv *priv, u32 icmd, u32 data)
{
	nv_wr32(priv, 0x400204, data);
	nv_wr32(priv, 0x400200, icmd);
	while (nv_rd32(priv, 0x400700) & 2) {}
}