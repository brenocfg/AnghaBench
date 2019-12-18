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
struct nv04_graph_priv {int dummy; } ;
struct nv04_graph_chan {int* nv04; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NV04_PGRAPH_CTX_CONTROL ; 
 int /*<<< orphan*/  NV04_PGRAPH_CTX_USER ; 
 int /*<<< orphan*/  NV04_PGRAPH_FFINTFC_ST2 ; 
 int /*<<< orphan*/ * nv04_graph_ctx_regs ; 
 struct nv04_graph_priv* nv04_graph_priv (struct nv04_graph_chan*) ; 
 int /*<<< orphan*/  nv_mask (struct nv04_graph_priv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv04_graph_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
nv04_graph_load_context(struct nv04_graph_chan *chan, int chid)
{
	struct nv04_graph_priv *priv = nv04_graph_priv(chan);
	int i;

	for (i = 0; i < ARRAY_SIZE(nv04_graph_ctx_regs); i++)
		nv_wr32(priv, nv04_graph_ctx_regs[i], chan->nv04[i]);

	nv_wr32(priv, NV04_PGRAPH_CTX_CONTROL, 0x10010100);
	nv_mask(priv, NV04_PGRAPH_CTX_USER, 0xff000000, chid << 24);
	nv_mask(priv, NV04_PGRAPH_FFINTFC_ST2, 0xfff00000, 0x00000000);
	return 0;
}