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
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_engine {int /*<<< orphan*/  lock; int /*<<< orphan*/  contexts; } ;
struct nouveau_device {int /*<<< orphan*/  cfgopt; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NV_ENGINE_CLASS ; 
 int /*<<< orphan*/  nouveau_boolopt (int /*<<< orphan*/ ,char const*,int) ; 
 int nouveau_subdev_create_ (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,char const*,char const*,int,void**) ; 
 struct nouveau_device* nv_device (struct nouveau_object*) ; 
 int /*<<< orphan*/  nv_warn (struct nouveau_engine*,char*,char const*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
nouveau_engine_create_(struct nouveau_object *parent,
		       struct nouveau_object *engobj,
		       struct nouveau_oclass *oclass, bool enable,
		       const char *iname, const char *fname,
		       int length, void **pobject)
{
	struct nouveau_device *device = nv_device(parent);
	struct nouveau_engine *engine;
	int ret;

	ret = nouveau_subdev_create_(parent, engobj, oclass, NV_ENGINE_CLASS,
				     iname, fname, length, pobject);
	engine = *pobject;
	if (ret)
		return ret;

	if (!nouveau_boolopt(device->cfgopt, iname, enable)) {
		if (!enable)
			nv_warn(engine, "disabled, %s=1 to enable\n", iname);
		return -ENODEV;
	}

	INIT_LIST_HEAD(&engine->contexts);
	spin_lock_init(&engine->lock);
	return 0;
}