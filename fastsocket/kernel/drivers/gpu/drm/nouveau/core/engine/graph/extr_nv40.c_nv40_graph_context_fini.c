#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nv40_graph_priv {int dummy; } ;
struct nv40_graph_chan {int dummy; } ;
struct nouveau_object {scalar_t__ engine; } ;
struct TYPE_2__ {int addr; } ;

/* Variables and functions */
 int EBUSY ; 
 TYPE_1__* nv_gpuobj (struct nv40_graph_chan*) ; 
 int /*<<< orphan*/  nv_mask (struct nv40_graph_priv*,int,int,int) ; 
 int nv_rd32 (struct nv40_graph_priv*,int) ; 
 int /*<<< orphan*/  nv_wait (struct nv40_graph_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_warn (struct nv40_graph_priv*,char*,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv40_graph_priv*,int,int) ; 

__attribute__((used)) static int
nv40_graph_context_fini(struct nouveau_object *object, bool suspend)
{
	struct nv40_graph_priv *priv = (void *)object->engine;
	struct nv40_graph_chan *chan = (void *)object;
	u32 inst = 0x01000000 | nv_gpuobj(chan)->addr >> 4;
	int ret = 0;

	nv_mask(priv, 0x400720, 0x00000001, 0x00000000);

	if (nv_rd32(priv, 0x40032c) == inst) {
		if (suspend) {
			nv_wr32(priv, 0x400720, 0x00000000);
			nv_wr32(priv, 0x400784, inst);
			nv_mask(priv, 0x400310, 0x00000020, 0x00000020);
			nv_mask(priv, 0x400304, 0x00000001, 0x00000001);
			if (!nv_wait(priv, 0x400300, 0x00000001, 0x00000000)) {
				u32 insn = nv_rd32(priv, 0x400308);
				nv_warn(priv, "ctxprog timeout 0x%08x\n", insn);
				ret = -EBUSY;
			}
		}

		nv_mask(priv, 0x40032c, 0x01000000, 0x00000000);
	}

	if (nv_rd32(priv, 0x400330) == inst)
		nv_mask(priv, 0x400330, 0x01000000, 0x00000000);

	nv_mask(priv, 0x400720, 0x00000001, 0x00000001);
	return ret;
}