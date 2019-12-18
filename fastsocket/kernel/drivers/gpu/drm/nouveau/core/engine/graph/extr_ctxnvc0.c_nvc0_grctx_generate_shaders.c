#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvc0_graph_priv {int dummy; } ;
struct TYPE_2__ {int chipset; } ;

/* Variables and functions */
 TYPE_1__* nv_device (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int,int) ; 

__attribute__((used)) static void
nvc0_grctx_generate_shaders(struct nvc0_graph_priv *priv)
{

	if (nv_device(priv)->chipset == 0xd9) {
		nv_wr32(priv, 0x405800, 0x0f8000bf);
		nv_wr32(priv, 0x405830, 0x02180218);
		nv_wr32(priv, 0x405834, 0x08000000);
	} else
	if (nv_device(priv)->chipset == 0xc1) {
		nv_wr32(priv, 0x405800, 0x0f8000bf);
		nv_wr32(priv, 0x405830, 0x02180218);
		nv_wr32(priv, 0x405834, 0x00000000);
	} else {
		nv_wr32(priv, 0x405800, 0x078000bf);
		nv_wr32(priv, 0x405830, 0x02180000);
		nv_wr32(priv, 0x405834, 0x00000000);
	}
	nv_wr32(priv, 0x405838, 0x00000000);
	nv_wr32(priv, 0x405854, 0x00000000);
	nv_wr32(priv, 0x405870, 0x00000001);
	nv_wr32(priv, 0x405874, 0x00000001);
	nv_wr32(priv, 0x405878, 0x00000001);
	nv_wr32(priv, 0x40587c, 0x00000001);
	nv_wr32(priv, 0x405a00, 0x00000000);
	nv_wr32(priv, 0x405a04, 0x00000000);
	nv_wr32(priv, 0x405a18, 0x00000000);
}