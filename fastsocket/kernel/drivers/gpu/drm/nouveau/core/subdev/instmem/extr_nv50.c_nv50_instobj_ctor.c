#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int size; int /*<<< orphan*/  addr; } ;
struct nv50_instobj_priv {TYPE_3__* mem; TYPE_2__ base; } ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_4__ {int (* get ) (struct nouveau_fb*,int,int,int /*<<< orphan*/ ,int,TYPE_3__**) ;} ;
struct nouveau_fb {TYPE_1__ ram; } ;
struct TYPE_6__ {int size; int page_shift; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int max (int,int) ; 
 struct nouveau_fb* nouveau_fb (struct nouveau_object*) ; 
 int nouveau_instobj_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,struct nv50_instobj_priv**) ; 
 struct nouveau_object* nv_object (struct nv50_instobj_priv*) ; 
 int stub1 (struct nouveau_fb*,int,int,int /*<<< orphan*/ ,int,TYPE_3__**) ; 

__attribute__((used)) static int
nv50_instobj_ctor(struct nouveau_object *parent, struct nouveau_object *engine,
		  struct nouveau_oclass *oclass, void *data, u32 size,
		  struct nouveau_object **pobject)
{
	struct nouveau_fb *pfb = nouveau_fb(parent);
	struct nv50_instobj_priv *node;
	u32 align = (unsigned long)data;
	int ret;

	size  = max((size  + 4095) & ~4095, (u32)4096);
	align = max((align + 4095) & ~4095, (u32)4096);

	ret = nouveau_instobj_create(parent, engine, oclass, &node);
	*pobject = nv_object(node);
	if (ret)
		return ret;

	ret = pfb->ram.get(pfb, size, align, 0, 0x800, &node->mem);
	if (ret)
		return ret;

	node->base.addr = node->mem->offset;
	node->base.size = node->mem->size << 12;
	node->mem->page_shift = 12;
	return 0;
}