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
nvc0_grctx_generate_rop(struct nvc0_graph_priv *priv)
{
	int chipset = nv_device(priv)->chipset;

	/* ROPC_BROADCAST */
	nv_wr32(priv, 0x408800, 0x02802a3c);
	nv_wr32(priv, 0x408804, 0x00000040);
	if (chipset == 0xd9) {
		nv_wr32(priv, 0x408808, 0x1043e005);
		nv_wr32(priv, 0x408900, 0x3080b801);
		nv_wr32(priv, 0x408904, 0x1043e005);
		nv_wr32(priv, 0x408908, 0x00c8102f);
	} else
	if (chipset == 0xc1) {
		nv_wr32(priv, 0x408808, 0x1003e005);
		nv_wr32(priv, 0x408900, 0x3080b801);
		nv_wr32(priv, 0x408904, 0x62000001);
		nv_wr32(priv, 0x408908, 0x00c80929);
	} else {
		nv_wr32(priv, 0x408808, 0x0003e00d);
		nv_wr32(priv, 0x408900, 0x3080b801);
		nv_wr32(priv, 0x408904, 0x02000001);
		nv_wr32(priv, 0x408908, 0x00c80929);
	}
	nv_wr32(priv, 0x40890c, 0x00000000);
	nv_wr32(priv, 0x408980, 0x0000011d);
}