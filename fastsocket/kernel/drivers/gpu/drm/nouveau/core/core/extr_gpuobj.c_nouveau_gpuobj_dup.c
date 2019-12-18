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
struct nouveau_object {int /*<<< orphan*/  engine; } ;
struct nouveau_gpuobj {int /*<<< orphan*/  size; int /*<<< orphan*/  addr; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_gpudup_oclass ; 
 int nouveau_object_create (struct nouveau_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nouveau_gpuobj**) ; 
 int /*<<< orphan*/  nouveau_object_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_object (struct nouveau_gpuobj*) ; 

int
nouveau_gpuobj_dup(struct nouveau_object *parent, struct nouveau_gpuobj *base,
		   struct nouveau_gpuobj **pgpuobj)
{
	struct nouveau_gpuobj *gpuobj;
	int ret;

	ret = nouveau_object_create(parent, parent->engine,
				   &nouveau_gpudup_oclass, 0, &gpuobj);
	*pgpuobj = gpuobj;
	if (ret)
		return ret;

	nouveau_object_ref(nv_object(base), &gpuobj->parent);
	gpuobj->addr = base->addr;
	gpuobj->size = base->size;
	return 0;
}