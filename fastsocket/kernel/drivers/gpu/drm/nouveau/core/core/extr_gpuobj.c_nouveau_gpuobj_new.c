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
struct nouveau_object {struct nouveau_object* engine; } ;
struct nouveau_gpuobj_class {int /*<<< orphan*/  flags; int /*<<< orphan*/  align; int /*<<< orphan*/  size; struct nouveau_object* pargpu; } ;
struct nouveau_gpuobj {int dummy; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_SUBDEV_CLASS ; 
 int /*<<< orphan*/  _nouveau_gpuobj_oclass ; 
 int nouveau_object_ctor (struct nouveau_object*,struct nouveau_object*,int /*<<< orphan*/ *,struct nouveau_gpuobj_class*,int,struct nouveau_object**) ; 
 int /*<<< orphan*/  nv_iclass (struct nouveau_object*,int /*<<< orphan*/ ) ; 

int
nouveau_gpuobj_new(struct nouveau_object *parent, struct nouveau_object *pargpu,
		   u32 size, u32 align, u32 flags,
		   struct nouveau_gpuobj **pgpuobj)
{
	struct nouveau_object *engine = parent;
	struct nouveau_gpuobj_class args = {
		.pargpu = pargpu,
		.size = size,
		.align = align,
		.flags = flags,
	};

	if (!nv_iclass(engine, NV_SUBDEV_CLASS))
		engine = engine->engine;
	BUG_ON(engine == NULL);

	return nouveau_object_ctor(parent, engine, &_nouveau_gpuobj_oclass,
				   &args, sizeof(args),
				   (struct nouveau_object **)pgpuobj);
}