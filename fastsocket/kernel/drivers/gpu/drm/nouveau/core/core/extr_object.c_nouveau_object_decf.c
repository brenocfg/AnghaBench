#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nouveau_object {scalar_t__ parent; scalar_t__ engine; } ;
struct TYPE_4__ {int (* fini ) (struct nouveau_object*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_object_dec (scalar_t__,int) ; 
 int /*<<< orphan*/  nv_debug (struct nouveau_object*,char*) ; 
 TYPE_2__* nv_ofuncs (struct nouveau_object*) ; 
 TYPE_1__* nv_subdev (scalar_t__) ; 
 int /*<<< orphan*/  nv_trace (struct nouveau_object*,char*) ; 
 int /*<<< orphan*/  nv_warn (struct nouveau_object*,char*,int) ; 
 int stub1 (struct nouveau_object*,int) ; 

__attribute__((used)) static int
nouveau_object_decf(struct nouveau_object *object)
{
	int ret;

	nv_trace(object, "stopping...\n");

	ret = nv_ofuncs(object)->fini(object, false);
	if (ret)
		nv_warn(object, "failed fini, %d\n", ret);

	if (object->engine) {
		mutex_lock(&nv_subdev(object->engine)->mutex);
		nouveau_object_dec(object->engine, false);
		mutex_unlock(&nv_subdev(object->engine)->mutex);
	}

	if (object->parent)
		nouveau_object_dec(object->parent, false);

	nv_debug(object, "stopped\n");
	return 0;
}