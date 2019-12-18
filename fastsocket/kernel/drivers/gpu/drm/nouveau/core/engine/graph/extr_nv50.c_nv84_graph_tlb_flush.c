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
struct nv50_graph_priv {int /*<<< orphan*/  lock; } ;
struct nouveau_timer {int (* read ) (struct nouveau_timer*) ;} ;
struct nouveau_engine {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  nouveau_bitfield_print (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nouveau_pgraph_vstatus_print (struct nv50_graph_priv*,int,int /*<<< orphan*/ ,int) ; 
 struct nouveau_timer* nouveau_timer (struct nouveau_engine*) ; 
 int /*<<< orphan*/  nv50_pgraph_status ; 
 int /*<<< orphan*/  nv50_pgraph_vstatus_0 ; 
 int /*<<< orphan*/  nv50_pgraph_vstatus_1 ; 
 int /*<<< orphan*/  nv50_pgraph_vstatus_2 ; 
 int /*<<< orphan*/  nv50_vm_flush_engine (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nv_error (struct nv50_graph_priv*,char*,...) ; 
 int /*<<< orphan*/  nv_mask (struct nv50_graph_priv*,int,int,int) ; 
 int nv_rd32 (struct nv50_graph_priv*,int) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct nouveau_timer*) ; 
 int stub2 (struct nouveau_timer*) ; 

__attribute__((used)) static int
nv84_graph_tlb_flush(struct nouveau_engine *engine)
{
	struct nouveau_timer *ptimer = nouveau_timer(engine);
	struct nv50_graph_priv *priv = (void *)engine;
	bool idle, timeout = false;
	unsigned long flags;
	u64 start;
	u32 tmp;

	spin_lock_irqsave(&priv->lock, flags);
	nv_mask(priv, 0x400500, 0x00000001, 0x00000000);

	start = ptimer->read(ptimer);
	do {
		idle = true;

		for (tmp = nv_rd32(priv, 0x400380); tmp && idle; tmp >>= 3) {
			if ((tmp & 7) == 1)
				idle = false;
		}

		for (tmp = nv_rd32(priv, 0x400384); tmp && idle; tmp >>= 3) {
			if ((tmp & 7) == 1)
				idle = false;
		}

		for (tmp = nv_rd32(priv, 0x400388); tmp && idle; tmp >>= 3) {
			if ((tmp & 7) == 1)
				idle = false;
		}
	} while (!idle &&
		 !(timeout = ptimer->read(ptimer) - start > 2000000000));

	if (timeout) {
		nv_error(priv, "PGRAPH TLB flush idle timeout fail\n");

		tmp = nv_rd32(priv, 0x400700);
		nv_error(priv, "PGRAPH_STATUS  : 0x%08x", tmp);
		nouveau_bitfield_print(nv50_pgraph_status, tmp);
		pr_cont("\n");

		nouveau_pgraph_vstatus_print(priv, 0, nv50_pgraph_vstatus_0,
				nv_rd32(priv, 0x400380));
		nouveau_pgraph_vstatus_print(priv, 1, nv50_pgraph_vstatus_1,
				nv_rd32(priv, 0x400384));
		nouveau_pgraph_vstatus_print(priv, 2, nv50_pgraph_vstatus_2,
				nv_rd32(priv, 0x400388));
	}

	nv50_vm_flush_engine(&engine->base, 0x00);

	nv_mask(priv, 0x400500, 0x00000001, 0x00000001);
	spin_unlock_irqrestore(&priv->lock, flags);
	return timeout ? -EBUSY : 0;
}