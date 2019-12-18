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
nvc0_grctx_generate_unk47xx(struct nvc0_graph_priv *priv)
{
	nv_wr32(priv, 0x404700, 0x00000000);
	nv_wr32(priv, 0x404704, 0x00000000);
	nv_wr32(priv, 0x404708, 0x00000000);
	nv_wr32(priv, 0x40470c, 0x00000000);
	nv_wr32(priv, 0x404710, 0x00000000);
	nv_wr32(priv, 0x404714, 0x00000000);
	nv_wr32(priv, 0x404718, 0x00000000);
	nv_wr32(priv, 0x40471c, 0x00000000);
	nv_wr32(priv, 0x404720, 0x00000000);
	nv_wr32(priv, 0x404724, 0x00000000);
	nv_wr32(priv, 0x404728, 0x00000000);
	nv_wr32(priv, 0x40472c, 0x00000000);
	nv_wr32(priv, 0x404730, 0x00000000);
	nv_wr32(priv, 0x404734, 0x00000100);
	nv_wr32(priv, 0x404738, 0x00000000);
	nv_wr32(priv, 0x40473c, 0x00000000);
	nv_wr32(priv, 0x404740, 0x00000000);
	nv_wr32(priv, 0x404744, 0x00000000);
	nv_wr32(priv, 0x404748, 0x00000000);
	nv_wr32(priv, 0x40474c, 0x00000000);
	nv_wr32(priv, 0x404750, 0x00000000);
	nv_wr32(priv, 0x404754, 0x00000000);
}