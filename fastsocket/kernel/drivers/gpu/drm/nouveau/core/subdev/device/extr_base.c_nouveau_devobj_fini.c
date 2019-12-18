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
struct nouveau_object {int dummy; } ;
struct nouveau_devobj {struct nouveau_object** subdev; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int NVDEV_SUBDEV_NR ; 
 int /*<<< orphan*/  NV_ENGINE_CLASS ; 
 int nouveau_object_dec (struct nouveau_object*,int) ; 
 int nouveau_object_inc (struct nouveau_object*) ; 
 int nouveau_parent_fini (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nv_iclass (struct nouveau_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nouveau_devobj_fini(struct nouveau_object *object, bool suspend)
{
	struct nouveau_devobj *devobj = (void *)object;
	struct nouveau_object *subdev;
	int ret, i;

	for (i = NVDEV_SUBDEV_NR - 1; i >= 0; i--) {
		if ((subdev = devobj->subdev[i])) {
			if (!nv_iclass(subdev, NV_ENGINE_CLASS)) {
				ret = nouveau_object_dec(subdev, suspend);
				if (ret && suspend)
					goto fail;
			}
		}
	}

	ret = nouveau_parent_fini(&devobj->base, suspend);
fail:
	for (; ret && suspend && i < NVDEV_SUBDEV_NR; i++) {
		if ((subdev = devobj->subdev[i])) {
			if (!nv_iclass(subdev, NV_ENGINE_CLASS)) {
				ret = nouveau_object_inc(subdev);
				if (ret) {
					/* XXX */
				}
			}
		}
	}

	return ret;
}