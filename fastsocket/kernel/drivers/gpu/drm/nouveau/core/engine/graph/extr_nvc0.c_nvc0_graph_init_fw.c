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
typedef  scalar_t__ u32 ;
struct nvc0_graph_priv {int dummy; } ;
struct nvc0_graph_fuc {int size; int* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,scalar_t__,int) ; 

void
nvc0_graph_init_fw(struct nvc0_graph_priv *priv, u32 fuc_base,
		   struct nvc0_graph_fuc *code, struct nvc0_graph_fuc *data)
{
	int i;

	nv_wr32(priv, fuc_base + 0x01c0, 0x01000000);
	for (i = 0; i < data->size / 4; i++)
		nv_wr32(priv, fuc_base + 0x01c4, data->data[i]);

	nv_wr32(priv, fuc_base + 0x0180, 0x01000000);
	for (i = 0; i < code->size / 4; i++) {
		if ((i & 0x3f) == 0)
			nv_wr32(priv, fuc_base + 0x0188, i >> 6);
		nv_wr32(priv, fuc_base + 0x0184, code->data[i]);
	}
}