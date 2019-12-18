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
struct nouveau_devinit {int /*<<< orphan*/  post; } ;
struct nouveau_device {int /*<<< orphan*/  cfgopt; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_boolopt (int /*<<< orphan*/ ,char*,int) ; 
 int nouveau_subdev_create_ (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,char*,char*,int,void**) ; 
 struct nouveau_device* nv_device (struct nouveau_object*) ; 

int
nouveau_devinit_create_(struct nouveau_object *parent,
			struct nouveau_object *engine,
			struct nouveau_oclass *oclass,
			int size, void **pobject)
{
	struct nouveau_device *device = nv_device(parent);
	struct nouveau_devinit *devinit;
	int ret;

	ret = nouveau_subdev_create_(parent, engine, oclass, 0, "DEVINIT",
				     "init", size, pobject);
	devinit = *pobject;
	if (ret)
		return ret;

	devinit->post = nouveau_boolopt(device->cfgopt, "NvForcePost", false);
	return 0;
}