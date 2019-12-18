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
struct nvc0_grctx {int /*<<< orphan*/  chan; struct nvc0_graph_priv* priv; } ;
struct nvc0_graph_priv {int size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_error (struct nvc0_graph_priv*,char*) ; 
 int /*<<< orphan*/  nv_mask (struct nvc0_graph_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_ro32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv_wait (struct nvc0_graph_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int,int) ; 

int
nvc0_grctx_fini(struct nvc0_grctx *info)
{
	struct nvc0_graph_priv *priv = info->priv;
	int i;

	/* trigger a context unload by unsetting the "next channel valid" bit
	 * and faking a context switch interrupt
	 */
	nv_mask(priv, 0x409b04, 0x80000000, 0x00000000);
	nv_wr32(priv, 0x409000, 0x00000100);
	if (!nv_wait(priv, 0x409b00, 0x80000000, 0x00000000)) {
		nv_error(priv, "grctx template channel unload timeout\n");
		return -EBUSY;
	}

	priv->data = kmalloc(priv->size, GFP_KERNEL);
	if (priv->data) {
		for (i = 0; i < priv->size; i += 4)
			priv->data[i / 4] = nv_ro32(info->chan, 0x80000 + i);
	}

	nouveau_gpuobj_ref(NULL, &info->chan);
	return priv->data ? 0 : -ENOMEM;
}