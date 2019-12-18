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
struct nv50_graph_priv {int dummy; } ;
struct nouveau_subdev {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_handle {int /*<<< orphan*/  object; } ;
struct nouveau_fifo {int (* chid ) (struct nouveau_fifo*,struct nouveau_object*) ;} ;
struct nouveau_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_bitfield_print (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nouveau_client_name (struct nouveau_object*) ; 
 struct nouveau_object* nouveau_engctx_get (struct nouveau_engine*,int) ; 
 int /*<<< orphan*/  nouveau_engctx_put (struct nouveau_object*) ; 
 int /*<<< orphan*/  nouveau_enum_print (int /*<<< orphan*/ ,int) ; 
 struct nouveau_fifo* nouveau_fifo (struct nouveau_subdev*) ; 
 struct nouveau_handle* nouveau_handle_get_class (struct nouveau_object*,int) ; 
 int /*<<< orphan*/  nouveau_handle_put (struct nouveau_handle*) ; 
 int /*<<< orphan*/  nv50_data_error_names ; 
 int /*<<< orphan*/  nv50_graph_intr_name ; 
 int /*<<< orphan*/  nv50_graph_trap_handler (struct nv50_graph_priv*,int,int,int,struct nouveau_object*) ; 
 int /*<<< orphan*/  nv_call (int /*<<< orphan*/ ,int,int) ; 
 struct nouveau_engine* nv_engine (struct nouveau_subdev*) ; 
 int /*<<< orphan*/  nv_error (struct nv50_graph_priv*,char*,...) ; 
 int nv_rd32 (struct nv50_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_graph_priv*,int,int) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int stub1 (struct nouveau_fifo*,struct nouveau_object*) ; 

__attribute__((used)) static void
nv50_graph_intr(struct nouveau_subdev *subdev)
{
	struct nouveau_fifo *pfifo = nouveau_fifo(subdev);
	struct nouveau_engine *engine = nv_engine(subdev);
	struct nouveau_object *engctx;
	struct nouveau_handle *handle = NULL;
	struct nv50_graph_priv *priv = (void *)subdev;
	u32 stat = nv_rd32(priv, 0x400100);
	u32 inst = nv_rd32(priv, 0x40032c) & 0x0fffffff;
	u32 addr = nv_rd32(priv, 0x400704);
	u32 subc = (addr & 0x00070000) >> 16;
	u32 mthd = (addr & 0x00001ffc);
	u32 data = nv_rd32(priv, 0x400708);
	u32 class = nv_rd32(priv, 0x400814);
	u32 show = stat;
	int chid;

	engctx = nouveau_engctx_get(engine, inst);
	chid   = pfifo->chid(pfifo, engctx);

	if (stat & 0x00000010) {
		handle = nouveau_handle_get_class(engctx, class);
		if (handle && !nv_call(handle->object, mthd, data))
			show &= ~0x00000010;
		nouveau_handle_put(handle);
	}

	if (show & 0x00100000) {
		u32 ecode = nv_rd32(priv, 0x400110);
		nv_error(priv, "DATA_ERROR ");
		nouveau_enum_print(nv50_data_error_names, ecode);
		pr_cont("\n");
	}

	if (stat & 0x00200000) {
		if (!nv50_graph_trap_handler(priv, show, chid, (u64)inst << 12,
				engctx))
			show &= ~0x00200000;
	}

	nv_wr32(priv, 0x400100, stat);
	nv_wr32(priv, 0x400500, 0x00010001);

	if (show) {
		nv_error(priv, "%s", "");
		nouveau_bitfield_print(nv50_graph_intr_name, show);
		pr_cont("\n");
		nv_error(priv,
			 "ch %d [0x%010llx %s] subc %d class 0x%04x mthd 0x%04x data 0x%08x\n",
			 chid, (u64)inst << 12, nouveau_client_name(engctx),
			 subc, class, mthd, data);
	}

	if (nv_rd32(priv, 0x400824) & (1 << 31))
		nv_wr32(priv, 0x400824, nv_rd32(priv, 0x400824) & ~(1 << 31));

	nouveau_engctx_put(engctx);
}