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
struct nve0_fifo_priv {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_enum {scalar_t__ data2; } ;
struct nouveau_engine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_client_name (struct nouveau_object*) ; 
 struct nouveau_object* nouveau_engctx_get (struct nouveau_engine*,int) ; 
 int /*<<< orphan*/  nouveau_engctx_put (struct nouveau_object*) ; 
 struct nouveau_engine* nouveau_engine (struct nve0_fifo_priv*,scalar_t__) ; 
 struct nouveau_enum* nouveau_enum_print (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv_error (struct nve0_fifo_priv*,char*,char*,int) ; 
 int nv_rd32 (struct nve0_fifo_priv*,int) ; 
 int /*<<< orphan*/  nve0_fifo_fault_gpcclient ; 
 int /*<<< orphan*/  nve0_fifo_fault_hubclient ; 
 int /*<<< orphan*/  nve0_fifo_fault_reason ; 
 int /*<<< orphan*/  nve0_fifo_fault_unit ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static void
nve0_fifo_isr_vm_fault(struct nve0_fifo_priv *priv, int unit)
{
	u32 inst = nv_rd32(priv, 0x2800 + (unit * 0x10));
	u32 valo = nv_rd32(priv, 0x2804 + (unit * 0x10));
	u32 vahi = nv_rd32(priv, 0x2808 + (unit * 0x10));
	u32 stat = nv_rd32(priv, 0x280c + (unit * 0x10));
	u32 client = (stat & 0x00001f00) >> 8;
	const struct nouveau_enum *en;
	struct nouveau_engine *engine;
	struct nouveau_object *engctx = NULL;

	nv_error(priv, "PFIFO: %s fault at 0x%010llx [", (stat & 0x00000080) ?
		       "write" : "read", (u64)vahi << 32 | valo);
	nouveau_enum_print(nve0_fifo_fault_reason, stat & 0x0000000f);
	pr_cont("] from ");
	en = nouveau_enum_print(nve0_fifo_fault_unit, unit);
	if (stat & 0x00000040) {
		pr_cont("/");
		nouveau_enum_print(nve0_fifo_fault_hubclient, client);
	} else {
		pr_cont("/GPC%d/", (stat & 0x1f000000) >> 24);
		nouveau_enum_print(nve0_fifo_fault_gpcclient, client);
	}

	if (en && en->data2) {
		engine = nouveau_engine(priv, en->data2);
		if (engine)
			engctx = nouveau_engctx_get(engine, inst);

	}

	pr_cont(" on channel 0x%010llx [%s]\n", (u64)inst << 12,
			nouveau_client_name(engctx));

	nouveau_engctx_put(engctx);
}