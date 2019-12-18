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
struct nv98_crypt_priv {int dummy; } ;
struct nouveau_subdev {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_fifo {int (* chid ) (struct nouveau_fifo*,struct nouveau_object*) ;} ;
struct nouveau_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_client_name (struct nouveau_object*) ; 
 struct nouveau_object* nouveau_engctx_get (struct nouveau_engine*,int) ; 
 int /*<<< orphan*/  nouveau_engctx_put (struct nouveau_object*) ; 
 int /*<<< orphan*/  nouveau_enum_print (int /*<<< orphan*/ ,int) ; 
 struct nouveau_fifo* nouveau_fifo (struct nouveau_subdev*) ; 
 int /*<<< orphan*/  nv98_crypt_isr_error_name ; 
 struct nouveau_engine* nv_engine (struct nouveau_subdev*) ; 
 int /*<<< orphan*/  nv_error (struct nv98_crypt_priv*,char*,...) ; 
 int nv_rd32 (struct nv98_crypt_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv98_crypt_priv*,int,int) ; 
 int /*<<< orphan*/  pr_cont (char*,int,int,int /*<<< orphan*/ ,int,int,int) ; 
 int stub1 (struct nouveau_fifo*,struct nouveau_object*) ; 

__attribute__((used)) static void
nv98_crypt_intr(struct nouveau_subdev *subdev)
{
	struct nouveau_fifo *pfifo = nouveau_fifo(subdev);
	struct nouveau_engine *engine = nv_engine(subdev);
	struct nouveau_object *engctx;
	struct nv98_crypt_priv *priv = (void *)subdev;
	u32 disp = nv_rd32(priv, 0x08701c);
	u32 stat = nv_rd32(priv, 0x087008) & disp & ~(disp >> 16);
	u32 inst = nv_rd32(priv, 0x087050) & 0x3fffffff;
	u32 ssta = nv_rd32(priv, 0x087040) & 0x0000ffff;
	u32 addr = nv_rd32(priv, 0x087040) >> 16;
	u32 mthd = (addr & 0x07ff) << 2;
	u32 subc = (addr & 0x3800) >> 11;
	u32 data = nv_rd32(priv, 0x087044);
	int chid;

	engctx = nouveau_engctx_get(engine, inst);
	chid   = pfifo->chid(pfifo, engctx);

	if (stat & 0x00000040) {
		nv_error(priv, "DISPATCH_ERROR [");
		nouveau_enum_print(nv98_crypt_isr_error_name, ssta);
		pr_cont("] ch %d [0x%010llx %s] subc %d mthd 0x%04x data 0x%08x\n",
		       chid, (u64)inst << 12, nouveau_client_name(engctx),
		       subc, mthd, data);
		nv_wr32(priv, 0x087004, 0x00000040);
		stat &= ~0x00000040;
	}

	if (stat) {
		nv_error(priv, "unhandled intr 0x%08x\n", stat);
		nv_wr32(priv, 0x087004, stat);
	}

	nouveau_engctx_put(engctx);
}