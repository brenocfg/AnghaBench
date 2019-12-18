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
typedef  scalar_t__ u32 ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct TYPE_2__ {scalar_t__ offset; } ;
struct nouveau_barobj {TYPE_1__ vma; scalar_t__ iomem; } ;
struct nouveau_bar {int (* kmap ) (struct nouveau_bar*,void*,int /*<<< orphan*/ ,TYPE_1__*) ;scalar_t__ iomem; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_MEM_ACCESS_RW ; 
 int nouveau_object_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,struct nouveau_barobj**) ; 
 struct nouveau_object* nv_object (struct nouveau_barobj*) ; 
 int stub1 (struct nouveau_bar*,void*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
nouveau_barobj_ctor(struct nouveau_object *parent,
		    struct nouveau_object *engine,
		    struct nouveau_oclass *oclass, void *mem, u32 size,
		    struct nouveau_object **pobject)
{
	struct nouveau_bar *bar = (void *)engine;
	struct nouveau_barobj *barobj;
	int ret;

	ret = nouveau_object_create(parent, engine, oclass, 0, &barobj);
	*pobject = nv_object(barobj);
	if (ret)
		return ret;

	ret = bar->kmap(bar, mem, NV_MEM_ACCESS_RW, &barobj->vma);
	if (ret)
		return ret;

	barobj->iomem = bar->iomem + (u32)barobj->vma.offset;
	return 0;
}