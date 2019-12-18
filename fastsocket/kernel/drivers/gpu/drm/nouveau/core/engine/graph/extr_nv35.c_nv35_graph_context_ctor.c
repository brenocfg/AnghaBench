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
nv35_graph_context_ctor(struct nouveau_object *parent,
			struct nouveau_object *engine,
			struct nouveau_oclass *oclass, void *data, u32 size,
			struct nouveau_object **pobject)
{
	struct nv20_graph_chan *chan;
	int ret, i;

	ret = nouveau_graph_context_create(parent, engine, oclass, NULL, 0x577c,
					   16, NVOBJ_FLAG_ZERO_ALLOC, &chan);
	*pobject = nv_object(chan);
	if (ret)
		return ret;

	chan->chid = nouveau_fifo_chan(parent)->chid;

	nv_wo32(chan, 0x0028, 0x00000001 | (chan->chid << 24));
	nv_wo32(chan, 0x040c, 0x00000101);
	nv_wo32(chan, 0x0420, 0x00000111);
	nv_wo32(chan, 0x0424, 0x00000060);
	nv_wo32(chan, 0x0440, 0x00000080);
	nv_wo32(chan, 0x0444, 0xffff0000);
	nv_wo32(chan, 0x0448, 0x00000001);
	nv_wo32(chan, 0x045c, 0x44400000);
	nv_wo32(chan, 0x0488, 0xffff0000);
	for (i = 0x04dc; i < 0x04e4; i += 4)
		nv_wo32(chan, i, 0x0fff0000);
	nv_wo32(chan, 0x04e8, 0x00011100);
	for (i = 0x0504; i < 0x0544; i += 4)
		nv_wo32(chan, i, 0x07ff0000);
	nv_wo32(chan, 0x054c, 0x4b7fffff);
	nv_wo32(chan, 0x0588, 0x00000080);
	nv_wo32(chan, 0x058c, 0x30201000);
	nv_wo32(chan, 0x0590, 0x70605040);
	nv_wo32(chan, 0x0594, 0xb8a89888);
	nv_wo32(chan, 0x0598, 0xf8e8d8c8);
	nv_wo32(chan, 0x05ac, 0xb0000000);
	for (i = 0x0604; i < 0x0644; i += 4)
		nv_wo32(chan, i, 0x00010588);
	for (i = 0x0644; i < 0x0684; i += 4)
		nv_wo32(chan, i, 0x00030303);
	for (i = 0x06c4; i < 0x0704; i += 4)
		nv_wo32(chan, i, 0x0008aae4);
	for (i = 0x0704; i < 0x0744; i += 4)
		nv_wo32(chan, i, 0x01012000);
	for (i = 0x0744; i < 0x0784; i += 4)
		nv_wo32(chan, i, 0x00080008);
	nv_wo32(chan, 0x0860, 0x00040000);
	nv_wo32(chan, 0x0864, 0x00010000);
	for (i = 0x0868; i < 0x0878; i += 4)
		nv_wo32(chan, i, 0x00040004);
	for (i = 0x1f1c; i <= 0x308c ; i += 16) {
		nv_wo32(chan, i + 0, 0x10700ff9);
		nv_wo32(chan, i + 4, 0x0436086c);
		nv_wo32(chan, i + 8, 0x000c001b);
	}
	for (i = 0x30bc; i < 0x30cc; i += 4)
		nv_wo32(chan, i, 0x0000ffff);
	nv_wo32(chan, 0x3450, 0x3f800000);
	nv_wo32(chan, 0x380c, 0x3f800000);
	nv_wo32(chan, 0x3820, 0x3f800000);
	nv_wo32(chan, 0x384c, 0x40000000);
	nv_wo32(chan, 0x3850, 0x3f800000);
	nv_wo32(chan, 0x3854, 0x3f000000);
	nv_wo32(chan, 0x385c, 0x40000000);
	nv_wo32(chan, 0x3860, 0x3f800000);
	nv_wo32(chan, 0x3868, 0xbf800000);
	nv_wo32(chan, 0x3870, 0xbf800000);
	return 0;
}