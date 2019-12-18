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
typedef  int /*<<< orphan*/  u32 ;
struct nv20_graph_chan {int chid; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_2__ {int chid; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVOBJ_FLAG_ZERO_ALLOC ; 
 TYPE_1__* nouveau_fifo_chan (struct nouveau_object*) ; 
 int nouveau_graph_context_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,struct nv20_graph_chan**) ; 
 struct nouveau_object* nv_object (struct nv20_graph_chan*) ; 
 int /*<<< orphan*/  nv_wo32 (struct nv20_graph_chan*,int,int) ; 

__attribute__((used)) static int
nv30_graph_context_ctor(struct nouveau_object *parent,
			struct nouveau_object *engine,
			struct nouveau_oclass *oclass, void *data, u32 size,
			struct nouveau_object **pobject)
{
	struct nv20_graph_chan *chan;
	int ret, i;

	ret = nouveau_graph_context_create(parent, engine, oclass, NULL, 0x5f48,
					   16, NVOBJ_FLAG_ZERO_ALLOC, &chan);
	*pobject = nv_object(chan);
	if (ret)
		return ret;

	chan->chid = nouveau_fifo_chan(parent)->chid;

	nv_wo32(chan, 0x0028, 0x00000001 | (chan->chid << 24));
	nv_wo32(chan, 0x0410, 0x00000101);
	nv_wo32(chan, 0x0424, 0x00000111);
	nv_wo32(chan, 0x0428, 0x00000060);
	nv_wo32(chan, 0x0444, 0x00000080);
	nv_wo32(chan, 0x0448, 0xffff0000);
	nv_wo32(chan, 0x044c, 0x00000001);
	nv_wo32(chan, 0x0460, 0x44400000);
	nv_wo32(chan, 0x048c, 0xffff0000);
	for (i = 0x04e0; i < 0x04e8; i += 4)
		nv_wo32(chan, i, 0x0fff0000);
	nv_wo32(chan, 0x04ec, 0x00011100);
	for (i = 0x0508; i < 0x0548; i += 4)
		nv_wo32(chan, i, 0x07ff0000);
	nv_wo32(chan, 0x0550, 0x4b7fffff);
	nv_wo32(chan, 0x058c, 0x00000080);
	nv_wo32(chan, 0x0590, 0x30201000);
	nv_wo32(chan, 0x0594, 0x70605040);
	nv_wo32(chan, 0x0598, 0xb8a89888);
	nv_wo32(chan, 0x059c, 0xf8e8d8c8);
	nv_wo32(chan, 0x05b0, 0xb0000000);
	for (i = 0x0600; i < 0x0640; i += 4)
		nv_wo32(chan, i, 0x00010588);
	for (i = 0x0640; i < 0x0680; i += 4)
		nv_wo32(chan, i, 0x00030303);
	for (i = 0x06c0; i < 0x0700; i += 4)
		nv_wo32(chan, i, 0x0008aae4);
	for (i = 0x0700; i < 0x0740; i += 4)
		nv_wo32(chan, i, 0x01012000);
	for (i = 0x0740; i < 0x0780; i += 4)
		nv_wo32(chan, i, 0x00080008);
	nv_wo32(chan, 0x085c, 0x00040000);
	nv_wo32(chan, 0x0860, 0x00010000);
	for (i = 0x0864; i < 0x0874; i += 4)
		nv_wo32(chan, i, 0x00040004);
	for (i = 0x1f18; i <= 0x3088 ; i += 16) {
		nv_wo32(chan, i + 0, 0x10700ff9);
		nv_wo32(chan, i + 1, 0x0436086c);
		nv_wo32(chan, i + 2, 0x000c001b);
	}
	for (i = 0x30b8; i < 0x30c8; i += 4)
		nv_wo32(chan, i, 0x0000ffff);
	nv_wo32(chan, 0x344c, 0x3f800000);
	nv_wo32(chan, 0x3808, 0x3f800000);
	nv_wo32(chan, 0x381c, 0x3f800000);
	nv_wo32(chan, 0x3848, 0x40000000);
	nv_wo32(chan, 0x384c, 0x3f800000);
	nv_wo32(chan, 0x3850, 0x3f000000);
	nv_wo32(chan, 0x3858, 0x40000000);
	nv_wo32(chan, 0x385c, 0x3f800000);
	nv_wo32(chan, 0x3864, 0xbf800000);
	nv_wo32(chan, 0x386c, 0xbf800000);
	return 0;
}