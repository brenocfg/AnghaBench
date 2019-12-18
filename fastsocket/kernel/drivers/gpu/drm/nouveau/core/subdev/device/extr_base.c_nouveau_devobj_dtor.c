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
struct nouveau_devobj {int /*<<< orphan*/  base; int /*<<< orphan*/ * subdev; } ;

/* Variables and functions */
 int NVDEV_SUBDEV_NR ; 
 int /*<<< orphan*/  nouveau_object_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_parent_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nouveau_devobj_dtor(struct nouveau_object *object)
{
	struct nouveau_devobj *devobj = (void *)object;
	int i;

	for (i = NVDEV_SUBDEV_NR - 1; i >= 0; i--)
		nouveau_object_ref(NULL, &devobj->subdev[i]);

	nouveau_parent_destroy(&devobj->base);
}