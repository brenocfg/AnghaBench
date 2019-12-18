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
struct nv10_graph_priv {int /*<<< orphan*/  lock; struct nv10_graph_chan** chan; } ;
struct nv10_graph_chan {int dummy; } ;
struct nouveau_subdev {int dummy; } ;
struct nouveau_namedb {int dummy; } ;
struct nouveau_handle {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int NV03_PGRAPH_INTR ; 
 int NV03_PGRAPH_NSOURCE ; 
 int NV03_PGRAPH_NSOURCE_ILLEGAL_MTHD ; 
 int NV03_PGRAPH_NSTATUS ; 
 int NV04_PGRAPH_FIFO ; 
 int NV04_PGRAPH_TRAPPED_ADDR ; 
 int NV04_PGRAPH_TRAPPED_DATA ; 
 int /*<<< orphan*/  NV_NAMEDB_CLASS ; 
 int NV_PGRAPH_INTR_CONTEXT_SWITCH ; 
 int NV_PGRAPH_INTR_ERROR ; 
 int /*<<< orphan*/  nouveau_bitfield_print (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nouveau_client_name (struct nv10_graph_chan*) ; 
 struct nouveau_handle* nouveau_namedb_get_class (struct nouveau_namedb*,int) ; 
 int /*<<< orphan*/  nouveau_namedb_put (struct nouveau_handle*) ; 
 int /*<<< orphan*/  nv04_graph_nsource ; 
 int /*<<< orphan*/  nv10_graph_context_switch (struct nv10_graph_priv*) ; 
 int /*<<< orphan*/  nv10_graph_intr_name ; 
 int /*<<< orphan*/  nv10_graph_nstatus ; 
 int /*<<< orphan*/  nv_call (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nv_error (struct nv10_graph_priv*,char*,...) ; 
 int /*<<< orphan*/  nv_object (struct nv10_graph_chan*) ; 
 scalar_t__ nv_pclass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nv_rd32 (struct nv10_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv10_graph_priv*,int,int) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
nv10_graph_intr(struct nouveau_subdev *subdev)
{
	struct nv10_graph_priv *priv = (void *)subdev;
	struct nv10_graph_chan *chan = NULL;
	struct nouveau_namedb *namedb = NULL;
	struct nouveau_handle *handle = NULL;
	u32 stat = nv_rd32(priv, NV03_PGRAPH_INTR);
	u32 nsource = nv_rd32(priv, NV03_PGRAPH_NSOURCE);
	u32 nstatus = nv_rd32(priv, NV03_PGRAPH_NSTATUS);
	u32 addr = nv_rd32(priv, NV04_PGRAPH_TRAPPED_ADDR);
	u32 chid = (addr & 0x01f00000) >> 20;
	u32 subc = (addr & 0x00070000) >> 16;
	u32 mthd = (addr & 0x00001ffc);
	u32 data = nv_rd32(priv, NV04_PGRAPH_TRAPPED_DATA);
	u32 class = nv_rd32(priv, 0x400160 + subc * 4) & 0xfff;
	u32 show = stat;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	chan = priv->chan[chid];
	if (chan)
		namedb = (void *)nv_pclass(nv_object(chan), NV_NAMEDB_CLASS);
	spin_unlock_irqrestore(&priv->lock, flags);

	if (stat & NV_PGRAPH_INTR_ERROR) {
		if (chan && (nsource & NV03_PGRAPH_NSOURCE_ILLEGAL_MTHD)) {
			handle = nouveau_namedb_get_class(namedb, class);
			if (handle && !nv_call(handle->object, mthd, data))
				show &= ~NV_PGRAPH_INTR_ERROR;
		}
	}

	if (stat & NV_PGRAPH_INTR_CONTEXT_SWITCH) {
		nv_wr32(priv, NV03_PGRAPH_INTR, NV_PGRAPH_INTR_CONTEXT_SWITCH);
		stat &= ~NV_PGRAPH_INTR_CONTEXT_SWITCH;
		show &= ~NV_PGRAPH_INTR_CONTEXT_SWITCH;
		nv10_graph_context_switch(priv);
	}

	nv_wr32(priv, NV03_PGRAPH_INTR, stat);
	nv_wr32(priv, NV04_PGRAPH_FIFO, 0x00000001);

	if (show) {
		nv_error(priv, "%s", "");
		nouveau_bitfield_print(nv10_graph_intr_name, show);
		pr_cont(" nsource:");
		nouveau_bitfield_print(nv04_graph_nsource, nsource);
		pr_cont(" nstatus:");
		nouveau_bitfield_print(nv10_graph_nstatus, nstatus);
		pr_cont("\n");
		nv_error(priv,
			 "ch %d [%s] subc %d class 0x%04x mthd 0x%04x data 0x%08x\n",
			 chid, nouveau_client_name(chan), subc, class, mthd,
			 data);
	}

	nouveau_namedb_put(handle);
}