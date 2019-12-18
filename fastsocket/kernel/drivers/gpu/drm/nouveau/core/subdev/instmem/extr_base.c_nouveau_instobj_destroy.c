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
struct nouveau_subdev {int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  engine; } ;
struct nouveau_instobj {TYPE_1__ base; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void nouveau_object_destroy (TYPE_1__*) ; 
 struct nouveau_subdev* nv_subdev (int /*<<< orphan*/ ) ; 

void
nouveau_instobj_destroy(struct nouveau_instobj *iobj)
{
	struct nouveau_subdev *subdev = nv_subdev(iobj->base.engine);

	mutex_lock(&subdev->mutex);
	list_del(&iobj->head);
	mutex_unlock(&subdev->mutex);

	return nouveau_object_destroy(&iobj->base);
}