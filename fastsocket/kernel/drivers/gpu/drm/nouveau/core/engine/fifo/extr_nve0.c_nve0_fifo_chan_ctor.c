#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  offset; } ;
struct TYPE_7__ {struct nve0_fifo_base* mem; TYPE_1__ bar; } ;
struct nve0_fifo_priv {TYPE_2__ user; } ;
struct TYPE_8__ {int chid; } ;
struct nve0_fifo_chan {int engine; TYPE_3__ base; } ;
struct nve0_fifo_base {int addr; } ;
struct nve0_channel_ind_class {int engine; int ioffset; int ilength; int /*<<< orphan*/  pushbuf; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_bar {int /*<<< orphan*/  (* flush ) (struct nouveau_bar*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  subdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  context_detach; int /*<<< orphan*/  context_attach; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int FIFO_ENGINE_NR ; 
 TYPE_5__* fifo_engine ; 
 int log2i (int) ; 
 int lower_32_bits (int) ; 
 struct nouveau_bar* nouveau_bar (struct nouveau_object*) ; 
 scalar_t__ nouveau_engine (struct nouveau_object*,int /*<<< orphan*/ ) ; 
 int nouveau_fifo_channel_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nve0_fifo_chan**) ; 
 struct nouveau_object* nv_object (struct nve0_fifo_chan*) ; 
 TYPE_4__* nv_parent (struct nve0_fifo_chan*) ; 
 int /*<<< orphan*/  nv_wo32 (struct nve0_fifo_base*,int,int) ; 
 int /*<<< orphan*/  nve0_fifo_context_attach ; 
 int /*<<< orphan*/  nve0_fifo_context_detach ; 
 int /*<<< orphan*/  stub1 (struct nouveau_bar*) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static int
nve0_fifo_chan_ctor(struct nouveau_object *parent,
		    struct nouveau_object *engine,
		    struct nouveau_oclass *oclass, void *data, u32 size,
		    struct nouveau_object **pobject)
{
	struct nouveau_bar *bar = nouveau_bar(parent);
	struct nve0_fifo_priv *priv = (void *)engine;
	struct nve0_fifo_base *base = (void *)parent;
	struct nve0_fifo_chan *chan;
	struct nve0_channel_ind_class *args = data;
	u64 usermem, ioffset, ilength;
	int ret, i;

	if (size < sizeof(*args))
		return -EINVAL;

	for (i = 0; i < FIFO_ENGINE_NR; i++) {
		if (args->engine & (1 << i)) {
			if (nouveau_engine(parent, fifo_engine[i].subdev)) {
				args->engine = (1 << i);
				break;
			}
		}
	}

	if (i == FIFO_ENGINE_NR)
		return -ENODEV;

	ret = nouveau_fifo_channel_create(parent, engine, oclass, 1,
					  priv->user.bar.offset, 0x200,
					  args->pushbuf,
					  fifo_engine[i].mask, &chan);
	*pobject = nv_object(chan);
	if (ret)
		return ret;

	nv_parent(chan)->context_attach = nve0_fifo_context_attach;
	nv_parent(chan)->context_detach = nve0_fifo_context_detach;
	chan->engine = i;

	usermem = chan->base.chid * 0x200;
	ioffset = args->ioffset;
	ilength = log2i(args->ilength / 8);

	for (i = 0; i < 0x200; i += 4)
		nv_wo32(priv->user.mem, usermem + i, 0x00000000);

	nv_wo32(base, 0x08, lower_32_bits(priv->user.mem->addr + usermem));
	nv_wo32(base, 0x0c, upper_32_bits(priv->user.mem->addr + usermem));
	nv_wo32(base, 0x10, 0x0000face);
	nv_wo32(base, 0x30, 0xfffff902);
	nv_wo32(base, 0x48, lower_32_bits(ioffset));
	nv_wo32(base, 0x4c, upper_32_bits(ioffset) | (ilength << 16));
	nv_wo32(base, 0x84, 0x20400000);
	nv_wo32(base, 0x94, 0x30000001);
	nv_wo32(base, 0x9c, 0x00000100);
	nv_wo32(base, 0xac, 0x0000001f);
	nv_wo32(base, 0xe8, chan->base.chid);
	nv_wo32(base, 0xb8, 0xf8000000);
	nv_wo32(base, 0xf8, 0x10003080); /* 0x002310 */
	nv_wo32(base, 0xfc, 0x10000010); /* 0x002350 */
	bar->flush(bar);
	return 0;
}