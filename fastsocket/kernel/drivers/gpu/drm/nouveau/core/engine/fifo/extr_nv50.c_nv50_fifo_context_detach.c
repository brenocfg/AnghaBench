#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nv50_fifo_priv {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  chid; } ;
struct nv50_fifo_chan {TYPE_1__ base; } ;
struct nv50_fifo_base {int /*<<< orphan*/  eng; } ;
struct nouveau_object {scalar_t__ engine; scalar_t__ parent; } ;
struct nouveau_bar {int /*<<< orphan*/  (* flush ) (struct nouveau_bar*) ;} ;
struct TYPE_4__ {int addr; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  NVDEV_ENGINE_GR 130 
#define  NVDEV_ENGINE_MPEG 129 
#define  NVDEV_ENGINE_SW 128 
 struct nouveau_bar* nouveau_bar (struct nouveau_object*) ; 
 int /*<<< orphan*/  nouveau_client_name (struct nv50_fifo_chan*) ; 
 int nv_engidx (scalar_t__) ; 
 int /*<<< orphan*/  nv_error (struct nv50_fifo_priv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* nv_gpuobj (struct nv50_fifo_base*) ; 
 int nv_mask (struct nv50_fifo_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_wait_ne (struct nv50_fifo_priv*,int,int,int) ; 
 int /*<<< orphan*/  nv_wo32 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nv_wr32 (struct nv50_fifo_priv*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_bar*) ; 

__attribute__((used)) static int
nv50_fifo_context_detach(struct nouveau_object *parent, bool suspend,
			 struct nouveau_object *object)
{
	struct nouveau_bar *bar = nouveau_bar(parent);
	struct nv50_fifo_priv *priv = (void *)parent->engine;
	struct nv50_fifo_base *base = (void *)parent->parent;
	struct nv50_fifo_chan *chan = (void *)parent;
	u32 addr, me;
	int ret = 0;

	switch (nv_engidx(object->engine)) {
	case NVDEV_ENGINE_SW   : return 0;
	case NVDEV_ENGINE_GR   : addr = 0x0000; break;
	case NVDEV_ENGINE_MPEG : addr = 0x0060; break;
	default:
		return -EINVAL;
	}

	/* HW bug workaround:
	 *
	 * PFIFO will hang forever if the connected engines don't report
	 * that they've processed the context switch request.
	 *
	 * In order for the kickoff to work, we need to ensure all the
	 * connected engines are in a state where they can answer.
	 *
	 * Newer chipsets don't seem to suffer from this issue, and well,
	 * there's also a "ignore these engines" bitmask reg we can use
	 * if we hit the issue there..
	 */
	me = nv_mask(priv, 0x00b860, 0x00000001, 0x00000001);

	/* do the kickoff... */
	nv_wr32(priv, 0x0032fc, nv_gpuobj(base)->addr >> 12);
	if (!nv_wait_ne(priv, 0x0032fc, 0xffffffff, 0xffffffff)) {
		nv_error(priv, "channel %d [%s] unload timeout\n",
			 chan->base.chid, nouveau_client_name(chan));
		if (suspend)
			ret = -EBUSY;
	}
	nv_wr32(priv, 0x00b860, me);

	if (ret == 0) {
		nv_wo32(base->eng, addr + 0x00, 0x00000000);
		nv_wo32(base->eng, addr + 0x04, 0x00000000);
		nv_wo32(base->eng, addr + 0x08, 0x00000000);
		nv_wo32(base->eng, addr + 0x0c, 0x00000000);
		nv_wo32(base->eng, addr + 0x10, 0x00000000);
		nv_wo32(base->eng, addr + 0x14, 0x00000000);
		bar->flush(bar);
	}

	return ret;
}