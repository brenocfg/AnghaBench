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
typedef  int u64 ;
typedef  int u32 ;
struct nvc0_grctx {int addr; struct nouveau_gpuobj* chan; scalar_t__ buffer_nr; struct nvc0_graph_priv* priv; int /*<<< orphan*/  mmio; int /*<<< orphan*/  data; } ;
struct nvc0_graph_priv {int size; scalar_t__ firmware; int /*<<< orphan*/  mmio_list; int /*<<< orphan*/  mmio_data; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_gpuobj {int addr; } ;
struct nouveau_bar {int /*<<< orphan*/  (* flush ) (struct nouveau_bar*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  NVOBJ_FLAG_ZERO_ALLOC ; 
 int lower_32_bits (int) ; 
 struct nouveau_bar* nouveau_bar (struct nvc0_graph_priv*) ; 
 int nouveau_gpuobj_new (struct nouveau_object*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,struct nouveau_gpuobj**) ; 
 int /*<<< orphan*/  nouveau_gpuobj_ref (int /*<<< orphan*/ *,struct nouveau_gpuobj**) ; 
 int /*<<< orphan*/  nv_error (struct nvc0_graph_priv*,char*,...) ; 
 struct nouveau_object* nv_object (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nv_wait (struct nvc0_graph_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_gpuobj*,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int,int) ; 
 int /*<<< orphan*/  nvc0_graph_ctxctl_debug (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_bar*) ; 
 int /*<<< orphan*/  stub2 (struct nouveau_bar*) ; 
 int upper_32_bits (int) ; 

int
nvc0_grctx_init(struct nvc0_graph_priv *priv, struct nvc0_grctx *info)
{
	struct nouveau_bar *bar = nouveau_bar(priv);
	struct nouveau_object *parent = nv_object(priv);
	struct nouveau_gpuobj *chan;
	u32 size = (0x80000 + priv->size + 4095) & ~4095;
	int ret, i;

	/* allocate memory to for a "channel", which we'll use to generate
	 * the default context values
	 */
	ret = nouveau_gpuobj_new(parent, NULL, size, 0x1000,
				 NVOBJ_FLAG_ZERO_ALLOC, &info->chan);
	chan = info->chan;
	if (ret) {
		nv_error(priv, "failed to allocate channel memory, %d\n", ret);
		return ret;
	}

	/* PGD pointer */
	nv_wo32(chan, 0x0200, lower_32_bits(chan->addr + 0x1000));
	nv_wo32(chan, 0x0204, upper_32_bits(chan->addr + 0x1000));
	nv_wo32(chan, 0x0208, 0xffffffff);
	nv_wo32(chan, 0x020c, 0x000000ff);

	/* PGT[0] pointer */
	nv_wo32(chan, 0x1000, 0x00000000);
	nv_wo32(chan, 0x1004, 0x00000001 | (chan->addr + 0x2000) >> 8);

	/* identity-map the whole "channel" into its own vm */
	for (i = 0; i < size / 4096; i++) {
		u64 addr = ((chan->addr + (i * 4096)) >> 8) | 1;
		nv_wo32(chan, 0x2000 + (i * 8), lower_32_bits(addr));
		nv_wo32(chan, 0x2004 + (i * 8), upper_32_bits(addr));
	}

	/* context pointer (virt) */
	nv_wo32(chan, 0x0210, 0x00080004);
	nv_wo32(chan, 0x0214, 0x00000000);

	bar->flush(bar);

	nv_wr32(priv, 0x100cb8, (chan->addr + 0x1000) >> 8);
	nv_wr32(priv, 0x100cbc, 0x80000001);
	nv_wait(priv, 0x100c80, 0x00008000, 0x00008000);

	/* setup default state for mmio list construction */
	info->data = priv->mmio_data;
	info->mmio = priv->mmio_list;
	info->addr = 0x2000 + (i * 8);
	info->priv = priv;
	info->buffer_nr = 0;

	if (priv->firmware) {
		nv_wr32(priv, 0x409840, 0x00000030);
		nv_wr32(priv, 0x409500, 0x80000000 | chan->addr >> 12);
		nv_wr32(priv, 0x409504, 0x00000003);
		if (!nv_wait(priv, 0x409800, 0x00000010, 0x00000010))
			nv_error(priv, "load_ctx timeout\n");

		nv_wo32(chan, 0x8001c, 1);
		nv_wo32(chan, 0x80020, 0);
		nv_wo32(chan, 0x80028, 0);
		nv_wo32(chan, 0x8002c, 0);
		bar->flush(bar);
		return 0;
	}

	/* HUB_FUC(SET_CHAN) */
	nv_wr32(priv, 0x409840, 0x80000000);
	nv_wr32(priv, 0x409500, 0x80000000 | chan->addr >> 12);
	nv_wr32(priv, 0x409504, 0x00000001);
	if (!nv_wait(priv, 0x409800, 0x80000000, 0x80000000)) {
		nv_error(priv, "HUB_SET_CHAN timeout\n");
		nvc0_graph_ctxctl_debug(priv);
		nouveau_gpuobj_ref(NULL, &info->chan);
		return -EBUSY;
	}

	return 0;
}