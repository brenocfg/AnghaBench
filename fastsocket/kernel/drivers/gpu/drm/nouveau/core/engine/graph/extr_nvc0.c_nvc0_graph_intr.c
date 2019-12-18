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
struct nvc0_graph_priv {int dummy; } ;
struct nouveau_subdev {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_handle {int /*<<< orphan*/  object; } ;
struct nouveau_fifo {int (* chid ) (struct nouveau_fifo*,struct nouveau_object*) ;} ;
struct nouveau_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_client_name (struct nouveau_object*) ; 
 struct nouveau_object* nouveau_engctx_get (struct nouveau_engine*,int) ; 
 int /*<<< orphan*/  nouveau_engctx_put (struct nouveau_object*) ; 
 int /*<<< orphan*/  nouveau_enum_print (int /*<<< orphan*/ ,int) ; 
 struct nouveau_fifo* nouveau_fifo (struct nouveau_subdev*) ; 
 struct nouveau_handle* nouveau_handle_get_class (struct nouveau_object*,int) ; 
 int /*<<< orphan*/  nouveau_handle_put (struct nouveau_handle*) ; 
 int /*<<< orphan*/  nv50_data_error_names ; 
 scalar_t__ nv_call (int /*<<< orphan*/ ,int,int) ; 
 struct nouveau_engine* nv_engine (struct nouveau_subdev*) ; 
 int /*<<< orphan*/  nv_error (struct nvc0_graph_priv*,char*,...) ; 
 int nv_rd32 (struct nvc0_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nvc0_graph_priv*,int,int) ; 
 int /*<<< orphan*/  nvc0_graph_ctxctl_isr (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  nvc0_graph_trap_intr (struct nvc0_graph_priv*) ; 
 int /*<<< orphan*/  pr_cont (char*,int,int,int /*<<< orphan*/ ,int,int,int,int) ; 
 int stub1 (struct nouveau_fifo*,struct nouveau_object*) ; 

__attribute__((used)) static void
nvc0_graph_intr(struct nouveau_subdev *subdev)
{
	struct nouveau_fifo *pfifo = nouveau_fifo(subdev);
	struct nouveau_engine *engine = nv_engine(subdev);
	struct nouveau_object *engctx;
	struct nouveau_handle *handle;
	struct nvc0_graph_priv *priv = (void *)subdev;
	u64 inst = nv_rd32(priv, 0x409b00) & 0x0fffffff;
	u32 stat = nv_rd32(priv, 0x400100);
	u32 addr = nv_rd32(priv, 0x400704);
	u32 mthd = (addr & 0x00003ffc);
	u32 subc = (addr & 0x00070000) >> 16;
	u32 data = nv_rd32(priv, 0x400708);
	u32 code = nv_rd32(priv, 0x400110);
	u32 class = nv_rd32(priv, 0x404200 + (subc * 4));
	int chid;

	engctx = nouveau_engctx_get(engine, inst);
	chid   = pfifo->chid(pfifo, engctx);

	if (stat & 0x00000010) {
		handle = nouveau_handle_get_class(engctx, class);
		if (!handle || nv_call(handle->object, mthd, data)) {
			nv_error(priv,
				 "ILLEGAL_MTHD ch %d [0x%010llx %s] subc %d class 0x%04x mthd 0x%04x data 0x%08x\n",
				 chid, inst << 12, nouveau_client_name(engctx),
				 subc, class, mthd, data);
		}
		nouveau_handle_put(handle);
		nv_wr32(priv, 0x400100, 0x00000010);
		stat &= ~0x00000010;
	}

	if (stat & 0x00000020) {
		nv_error(priv,
			 "ILLEGAL_CLASS ch %d [0x%010llx %s] subc %d class 0x%04x mthd 0x%04x data 0x%08x\n",
			 chid, inst << 12, nouveau_client_name(engctx), subc,
			 class, mthd, data);
		nv_wr32(priv, 0x400100, 0x00000020);
		stat &= ~0x00000020;
	}

	if (stat & 0x00100000) {
		nv_error(priv, "DATA_ERROR [");
		nouveau_enum_print(nv50_data_error_names, code);
		pr_cont("] ch %d [0x%010llx %s] subc %d class 0x%04x mthd 0x%04x data 0x%08x\n",
			chid, inst << 12, nouveau_client_name(engctx), subc,
			class, mthd, data);
		nv_wr32(priv, 0x400100, 0x00100000);
		stat &= ~0x00100000;
	}

	if (stat & 0x00200000) {
		nv_error(priv, "TRAP ch %d [0x%010llx %s]\n", chid, inst << 12,
			 nouveau_client_name(engctx));
		nvc0_graph_trap_intr(priv);
		nv_wr32(priv, 0x400100, 0x00200000);
		stat &= ~0x00200000;
	}

	if (stat & 0x00080000) {
		nvc0_graph_ctxctl_isr(priv);
		nv_wr32(priv, 0x400100, 0x00080000);
		stat &= ~0x00080000;
	}

	if (stat) {
		nv_error(priv, "unknown stat 0x%08x\n", stat);
		nv_wr32(priv, 0x400100, stat);
	}

	nv_wr32(priv, 0x400500, 0x00010001);
	nouveau_engctx_put(engctx);
}