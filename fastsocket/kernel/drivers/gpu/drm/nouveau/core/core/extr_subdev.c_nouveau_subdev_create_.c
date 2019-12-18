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
typedef  int u32 ;
struct nouveau_subdev {char const* name; int /*<<< orphan*/  mmio; int /*<<< orphan*/  debug; int /*<<< orphan*/  mutex; } ;
struct nouveau_oclass {int /*<<< orphan*/  lock_class_key; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_device {void** subdev; int /*<<< orphan*/  dbgopt; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmio; } ;

/* Variables and functions */
 int NV_SUBDEV_CLASS ; 
 int /*<<< orphan*/  __mutex_init (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_dbgopt (int /*<<< orphan*/ ,char const*) ; 
 int nouveau_object_create_ (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int,int,void**) ; 
 struct nouveau_device* nv_device (struct nouveau_object*) ; 
 int nv_hclass (struct nouveau_subdev*) ; 
 TYPE_1__* nv_subdev (struct nouveau_device*) ; 

int
nouveau_subdev_create_(struct nouveau_object *parent,
		       struct nouveau_object *engine,
		       struct nouveau_oclass *oclass, u32 pclass,
		       const char *subname, const char *sysname,
		       int size, void **pobject)
{
	struct nouveau_subdev *subdev;
	int ret;

	ret = nouveau_object_create_(parent, engine, oclass, pclass |
				     NV_SUBDEV_CLASS, size, pobject);
	subdev = *pobject;
	if (ret)
		return ret;

	__mutex_init(&subdev->mutex, subname, &oclass->lock_class_key);
	subdev->name = subname;

	if (parent) {
		struct nouveau_device *device = nv_device(parent);
		int subidx = nv_hclass(subdev) & 0xff;

		subdev->debug = nouveau_dbgopt(device->dbgopt, subname);
		subdev->mmio  = nv_subdev(device)->mmio;
		device->subdev[subidx] = *pobject;
	}

	return 0;
}