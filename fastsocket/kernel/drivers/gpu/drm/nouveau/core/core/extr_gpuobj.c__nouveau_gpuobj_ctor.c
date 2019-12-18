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
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_gpuobj_class {int /*<<< orphan*/  flags; int /*<<< orphan*/  align; int /*<<< orphan*/  size; int /*<<< orphan*/  pargpu; } ;
struct nouveau_gpuobj {int dummy; } ;

/* Variables and functions */
 int nouveau_gpuobj_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nouveau_gpuobj**) ; 
 struct nouveau_object* nv_object (struct nouveau_gpuobj*) ; 

__attribute__((used)) static int
_nouveau_gpuobj_ctor(struct nouveau_object *parent,
		     struct nouveau_object *engine,
		     struct nouveau_oclass *oclass, void *data, u32 size,
		     struct nouveau_object **pobject)
{
	struct nouveau_gpuobj_class *args = data;
	struct nouveau_gpuobj *object;
	int ret;

	ret = nouveau_gpuobj_create(parent, engine, oclass, 0, args->pargpu,
				    args->size, args->align, args->flags,
				    &object);
	*pobject = nv_object(object);
	if (ret)
		return ret;

	return 0;
}