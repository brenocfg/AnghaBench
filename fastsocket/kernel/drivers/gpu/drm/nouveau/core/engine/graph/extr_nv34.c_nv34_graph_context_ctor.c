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
nv34_graph_context_ctor(struct nouveau_object *parent,
			struct nouveau_object *engine,
			struct nouveau_oclass *oclass, void *data, u32 size,
			struct nouveau_object **pobject)
{
	struct nv20_graph_chan *chan;
	int ret, i;

	ret = nouveau_graph_context_create(parent, engine, oclass, NULL, 0x46dc,
					   16, NVOBJ_FLAG_ZERO_ALLOC, &chan);
	*pobject = nv_object(chan);
	if (ret)
		return ret;

	chan->chid = nouveau_fifo_chan(parent)->chid;

	nv_wo32(chan, 0x0028, 0x00000001 | (chan->chid << 24));
	nv_wo32(chan, 0x040c, 0x01000101);
	nv_wo32(chan, 0x0420, 0x00000111);
	nv_wo32(chan, 0x0424, 0x00000060);
	nv_wo32(chan, 0x0440, 0x00000080);
	nv_wo32(chan, 0x0444, 0xffff0000);
	nv_wo32(chan, 0x0448, 0x00000001);
	nv_wo32(chan, 0x045c, 0x44400000);
	nv_wo32(chan, 0x0480, 0xffff0000);
	for (i = 0x04d4; i < 0x04dc; i += 4)
		nv_wo32(chan, i, 0x0fff0000);
	nv_wo32(chan, 0x04e0, 0x00011100);
	for (i = 0x04fc; i < 0x053c; i += 4)
		nv_wo32(chan, i, 0x07ff0000);
	nv_wo32(chan, 0x0544, 0x4b7fffff);
	nv_wo32(chan, 0x057c, 0x00000080);
	nv_wo32(chan, 0x0580, 0x30201000);
	nv_wo32(chan, 0x0584, 0x70605040);
	nv_wo32(chan, 0x0588, 0xb8a89888);
	nv_wo32(chan, 0x058c, 0xf8e8d8c8);
	nv_wo32(chan, 0x05a0, 0xb0000000);
	for (i = 0x05f0; i < 0x0630; i += 4)
		nv_wo32(chan, i, 0x00010588);
	for (i = 0x0630; i < 0x0670; i += 4)
		nv_wo32(chan, i, 0x00030303);
	for (i = 0x06b0; i < 0x06f0; i += 4)
		nv_wo32(chan, i, 0x0008aae4);
	for (i = 0x06f0; i < 0x0730; i += 4)
		nv_wo32(chan, i, 0x01012000);
	for (i = 0x0730; i < 0x0770; i += 4)
		nv_wo32(chan, i, 0x00080008);
	nv_wo32(chan, 0x0850, 0x00040000);
	nv_wo32(chan, 0x0854, 0x00010000);
	for (i = 0x0858; i < 0x0868; i += 4)
		nv_wo32(chan, i, 0x00040004);
	for (i = 0x15ac; i <= 0x271c ; i += 16) {
		nv_wo32(chan, i + 0, 0x10700ff9);
		nv_wo32(chan, i + 1, 0x0436086c);
		nv_wo32(chan, i + 2, 0x000c001b);
	}
	for (i = 0x274c; i < 0x275c; i += 4)
		nv_wo32(chan, i, 0x0000ffff);
	nv_wo32(chan, 0x2ae0, 0x3f800000);
	nv_wo32(chan, 0x2e9c, 0x3f800000);
	nv_wo32(chan, 0x2eb0, 0x3f800000);
	nv_wo32(chan, 0x2edc, 0x40000000);
	nv_wo32(chan, 0x2ee0, 0x3f800000);
	nv_wo32(chan, 0x2ee4, 0x3f000000);
	nv_wo32(chan, 0x2eec, 0x40000000);
	nv_wo32(chan, 0x2ef0, 0x3f800000);
	nv_wo32(chan, 0x2ef8, 0xbf800000);
	nv_wo32(chan, 0x2f00, 0xbf800000);
	return 0;
}