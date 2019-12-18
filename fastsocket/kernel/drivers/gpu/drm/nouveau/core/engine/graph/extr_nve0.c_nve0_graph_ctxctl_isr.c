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
 int /*<<< orphan*/  nv_error (struct nvc0_graph_priv*,char*,...) ; 
 int nv_rd32 (struct nvc0_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int,int) ; 
 int /*<<< orphan*/  nvc0_graph_ctxctl_debug (struct nvc0_graph_priv*) ; 

__attribute__((used)) static void
nve0_graph_ctxctl_isr(struct nvc0_graph_priv *priv)
{
	u32 ustat = nv_rd32(priv, 0x409c18);

	if (ustat & 0x00000001)
		nv_error(priv, "CTXCTRL ucode error\n");
	if (ustat & 0x00080000)
		nv_error(priv, "CTXCTRL watchdog timeout\n");
	if (ustat & ~0x00080001)
		nv_error(priv, "CTXCTRL 0x%08x\n", ustat);

	nvc0_graph_ctxctl_debug(priv);
	nv_wr32(priv, 0x409c20, ustat);
}