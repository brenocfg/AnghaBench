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
typedef  int /*<<< orphan*/  u32 ;
struct nv50_mpeg_chan {int dummy; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_bar {int /*<<< orphan*/  (* flush ) (struct nouveau_bar*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NVOBJ_FLAG_ZERO_ALLOC ; 
 struct nouveau_bar* nouveau_bar (struct nouveau_object*) ; 
 int nouveau_mpeg_context_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nv50_mpeg_chan**) ; 
 struct nouveau_object* nv_object (struct nv50_mpeg_chan*) ; 
 int /*<<< orphan*/  nv_wo32 (struct nv50_mpeg_chan*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_bar*) ; 

int
nv50_mpeg_context_ctor(struct nouveau_object *parent,
		       struct nouveau_object *engine,
		       struct nouveau_oclass *oclass, void *data, u32 size,
		       struct nouveau_object **pobject)
{
	struct nouveau_bar *bar = nouveau_bar(parent);
	struct nv50_mpeg_chan *chan;
	int ret;

	ret = nouveau_mpeg_context_create(parent, engine, oclass, NULL, 128 * 4,
					  0, NVOBJ_FLAG_ZERO_ALLOC, &chan);
	*pobject = nv_object(chan);
	if (ret)
		return ret;

	nv_wo32(chan, 0x0070, 0x00801ec1);
	nv_wo32(chan, 0x007c, 0x0000037c);
	bar->flush(bar);
	return 0;
}