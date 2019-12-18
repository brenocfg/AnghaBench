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
struct nvc0_graph_priv {int dummy; } ;

/* Variables and functions */
 int nv_rd32 (struct nvc0_graph_priv*,int) ; 
 int /*<<< orphan*/  nvc0_graph_ctxctl_debug_unit (struct nvc0_graph_priv*,int) ; 

void
nvc0_graph_ctxctl_debug(struct nvc0_graph_priv *priv)
{
	u32 gpcnr = nv_rd32(priv, 0x409604) & 0xffff;
	u32 gpc;

	nvc0_graph_ctxctl_debug_unit(priv, 0x409000);
	for (gpc = 0; gpc < gpcnr; gpc++)
		nvc0_graph_ctxctl_debug_unit(priv, 0x502000 + (gpc * 0x8000));
}