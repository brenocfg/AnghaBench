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
struct nv84_crypt_priv {int dummy; } ;
struct nouveau_subdev {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_fifo {int (* chid ) (struct nouveau_fifo*,struct nouveau_object*) ;} ;
struct nouveau_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_bitfield_print (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nouveau_client_name (struct nouveau_object*) ; 
 struct nouveau_object* nouveau_engctx_get (struct nouveau_engine*,int) ; 
 int /*<<< orphan*/  nouveau_engctx_put (struct nouveau_object*) ; 
 struct nouveau_fifo* nouveau_fifo (struct nouveau_subdev*) ; 
 int /*<<< orphan*/  nv84_crypt_intr_mask ; 
 struct nouveau_engine* nv_engine (struct nouveau_subdev*) ; 
 int /*<<< orphan*/  nv_error (struct nv84_crypt_priv*,char*,char*) ; 
 int nv_rd32 (struct nv84_crypt_priv*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv84_crypt_priv*,int,int) ; 
 int /*<<< orphan*/  pr_cont (char*,int,int,int /*<<< orphan*/ ,int,int) ; 
 int stub1 (struct nouveau_fifo*,struct nouveau_object*) ; 

__attribute__((used)) static void
nv84_crypt_intr(struct nouveau_subdev *subdev)
{
	struct nouveau_fifo *pfifo = nouveau_fifo(subdev);
	struct nouveau_engine *engine = nv_engine(subdev);
	struct nouveau_object *engctx;
	struct nv84_crypt_priv *priv = (void *)subdev;
	u32 stat = nv_rd32(priv, 0x102130);
	u32 mthd = nv_rd32(priv, 0x102190);
	u32 data = nv_rd32(priv, 0x102194);
	u32 inst = nv_rd32(priv, 0x102188) & 0x7fffffff;
	int chid;

	engctx = nouveau_engctx_get(engine, inst);
	chid   = pfifo->chid(pfifo, engctx);

	if (stat) {
		nv_error(priv, "%s", "");
		nouveau_bitfield_print(nv84_crypt_intr_mask, stat);
		pr_cont(" ch %d [0x%010llx %s] mthd 0x%04x data 0x%08x\n",
		       chid, (u64)inst << 12, nouveau_client_name(engctx),
		       mthd, data);
	}

	nv_wr32(priv, 0x102130, stat);
	nv_wr32(priv, 0x10200c, 0x10);

	nouveau_engctx_put(engctx);
}