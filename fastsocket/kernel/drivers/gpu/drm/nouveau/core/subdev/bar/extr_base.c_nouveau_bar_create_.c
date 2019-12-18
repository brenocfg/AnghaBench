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
struct nouveau_device {int /*<<< orphan*/  pdev; } ;
struct nouveau_bar {int /*<<< orphan*/  iomem; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nouveau_subdev_create_ (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,char*,char*,int,void**) ; 
 struct nouveau_device* nv_device (struct nouveau_object*) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int) ; 

int
nouveau_bar_create_(struct nouveau_object *parent,
		    struct nouveau_object *engine,
		    struct nouveau_oclass *oclass, int length, void **pobject)
{
	struct nouveau_device *device = nv_device(parent);
	struct nouveau_bar *bar;
	int ret;

	ret = nouveau_subdev_create_(parent, engine, oclass, 0, "BARCTL",
				     "bar", length, pobject);
	bar = *pobject;
	if (ret)
		return ret;

	bar->iomem = ioremap(pci_resource_start(device->pdev, 3),
			     pci_resource_len(device->pdev, 3));
	return 0;
}