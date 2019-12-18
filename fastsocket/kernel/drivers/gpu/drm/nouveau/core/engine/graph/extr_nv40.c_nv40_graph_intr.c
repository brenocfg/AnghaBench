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
struct nv40_graph_priv {int dummy; } ;
struct nouveau_subdev {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_handle {int /*<<< orphan*/  object; } ;
struct nouveau_fifo {int (* chid ) (struct nouveau_fifo*,struct nouveau_object*) ;} ;
struct nouveau_engine {int dummy; } ;

/* Variables and functions */
 int NV03_PGRAPH_INTR ; 
 int NV03_PGRAPH_NSOURCE ; 
 int NV03_PGRAPH_NSOURCE_DMA_VTX_PROTECTION ; 
 int NV03_PGRAPH_NSOURCE_ILLEGAL_MTHD ; 
 int NV03_PGRAPH_NSTATUS ; 
 int NV04_PGRAPH_FIFO ; 
 int NV04_PGRAPH_TRAPPED_ADDR ; 
 int NV04_PGRAPH_TRAPPED_DATA ; 
 int NV_PGRAPH_INTR_ERROR ; 
 int /*<<< orphan*/  nouveau_bitfield_print (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nouveau_client_name (struct nouveau_object*) ; 
 struct nouveau_object* nouveau_engctx_get (struct nouveau_engine*,int) ; 
 int /*<<< orphan*/  nouveau_engctx_put (struct nouveau_object*) ; 
 struct nouveau_fifo* nouveau_fifo (struct nouveau_subdev*) ; 
 struct nouveau_handle* nouveau_handle_get_class (struct nouveau_object*,int) ; 
 int /*<<< orphan*/  nouveau_handle_put (struct nouveau_handle*) ; 
 int /*<<< orphan*/  nv04_graph_nsource ; 
 int /*<<< orphan*/  nv10_graph_intr_name ; 
 int /*<<< orphan*/  nv10_graph_nstatus ; 
 int /*<<< orphan*/  nv_call (int /*<<< orphan*/ ,int,int) ; 
 struct nouveau_engine* nv_engine (struct nouveau_subdev*) ; 
 int /*<<< orphan*/  nv_error (struct nv40_graph_priv*,char*,...) ; 
 int /*<<< orphan*/  nv_mask (struct nv40_graph_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nv_rd32 (struct nv40_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv40_graph_priv*,int,int) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int stub1 (struct nouveau_fifo*,struct nouveau_object*) ; 

__attribute__((used)) static void
nv40_graph_intr(struct nouveau_subdev *subdev)
{
	struct nouveau_fifo *pfifo = nouveau_fifo(subdev);
	struct nouveau_engine *engine = nv_engine(subdev);
	struct nouveau_object *engctx;
	struct nouveau_handle *handle = NULL;
	struct nv40_graph_priv *priv = (void *)subdev;
	u32 stat = nv_rd32(priv, NV03_PGRAPH_INTR);
	u32 nsource = nv_rd32(priv, NV03_PGRAPH_NSOURCE);
	u32 nstatus = nv_rd32(priv, NV03_PGRAPH_NSTATUS);
	u32 inst = nv_rd32(priv, 0x40032c) & 0x000fffff;
	u32 addr = nv_rd32(priv, NV04_PGRAPH_TRAPPED_ADDR);
	u32 subc = (addr & 0x00070000) >> 16;
	u32 mthd = (addr & 0x00001ffc);
	u32 data = nv_rd32(priv, NV04_PGRAPH_TRAPPED_DATA);
	u32 class = nv_rd32(priv, 0x400160 + subc * 4) & 0xffff;
	u32 show = stat;
	int chid;

	engctx = nouveau_engctx_get(engine, inst);
	chid   = pfifo->chid(pfifo, engctx);

	if (stat & NV_PGRAPH_INTR_ERROR) {
		if (nsource & NV03_PGRAPH_NSOURCE_ILLEGAL_MTHD) {
			handle = nouveau_handle_get_class(engctx, class);
			if (handle && !nv_call(handle->object, mthd, data))
				show &= ~NV_PGRAPH_INTR_ERROR;
			nouveau_handle_put(handle);
		}

		if (nsource & NV03_PGRAPH_NSOURCE_DMA_VTX_PROTECTION) {
			nv_mask(priv, 0x402000, 0, 0);
		}
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
			 "ch %d [0x%08x %s] subc %d class 0x%04x mthd 0x%04x data 0x%08x\n",
			 chid, inst << 4, nouveau_client_name(engctx), subc,
			 class, mthd, data);
	}

	nouveau_engctx_put(engctx);
}