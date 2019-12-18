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
struct nouveau_subdev {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_fifo {int (* chid ) (struct nouveau_fifo*,struct nouveau_object*) ;} ;
struct nouveau_falcon {int dummy; } ;
struct nouveau_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_client_name (struct nouveau_object*) ; 
 struct nouveau_object* nouveau_engctx_get (struct nouveau_engine*,int) ; 
 int /*<<< orphan*/  nouveau_engctx_put (struct nouveau_object*) ; 
 int /*<<< orphan*/  nouveau_enum_print (int /*<<< orphan*/ ,int) ; 
 struct nouveau_fifo* nouveau_fifo (struct nouveau_subdev*) ; 
 struct nouveau_engine* nv_engine (struct nouveau_subdev*) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_falcon*,char*,...) ; 
 int nv_ro32 (struct nouveau_falcon*,int) ; 
 int /*<<< orphan*/  nv_wo32 (struct nouveau_falcon*,int,int) ; 
 int /*<<< orphan*/  nva3_copy_isr_error_name ; 
 int /*<<< orphan*/  pr_cont (char*,int,int,int /*<<< orphan*/ ,int,int,int) ; 
 int stub1 (struct nouveau_fifo*,struct nouveau_object*) ; 

void
nva3_copy_intr(struct nouveau_subdev *subdev)
{
	struct nouveau_fifo *pfifo = nouveau_fifo(subdev);
	struct nouveau_engine *engine = nv_engine(subdev);
	struct nouveau_falcon *falcon = (void *)subdev;
	struct nouveau_object *engctx;
	u32 dispatch = nv_ro32(falcon, 0x01c);
	u32 stat = nv_ro32(falcon, 0x008) & dispatch & ~(dispatch >> 16);
	u64 inst = nv_ro32(falcon, 0x050) & 0x3fffffff;
	u32 ssta = nv_ro32(falcon, 0x040) & 0x0000ffff;
	u32 addr = nv_ro32(falcon, 0x040) >> 16;
	u32 mthd = (addr & 0x07ff) << 2;
	u32 subc = (addr & 0x3800) >> 11;
	u32 data = nv_ro32(falcon, 0x044);
	int chid;

	engctx = nouveau_engctx_get(engine, inst);
	chid   = pfifo->chid(pfifo, engctx);

	if (stat & 0x00000040) {
		nv_error(falcon, "DISPATCH_ERROR [");
		nouveau_enum_print(nva3_copy_isr_error_name, ssta);
		pr_cont("] ch %d [0x%010llx %s] subc %d mthd 0x%04x data 0x%08x\n",
		       chid, inst << 12, nouveau_client_name(engctx), subc,
		       mthd, data);
		nv_wo32(falcon, 0x004, 0x00000040);
		stat &= ~0x00000040;
	}

	if (stat) {
		nv_error(falcon, "unhandled intr 0x%08x\n", stat);
		nv_wo32(falcon, 0x004, stat);
	}

	nouveau_engctx_put(engctx);
}