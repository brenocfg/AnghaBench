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
struct nouveau_object {int /*<<< orphan*/  usecount; struct nouveau_object* parent; struct nouveau_object* engine; } ;
struct TYPE_4__ {int (* init ) (struct nouveau_object*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_object_dec (struct nouveau_object*,int) ; 
 int /*<<< orphan*/  nv_debug (struct nouveau_object*,char*) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_object*,char*,int) ; 
 TYPE_2__* nv_ofuncs (struct nouveau_object*) ; 
 TYPE_1__* nv_subdev (struct nouveau_object*) ; 
 int /*<<< orphan*/  nv_trace (struct nouveau_object*,char*,...) ; 
 int stub1 (struct nouveau_object*) ; 

int
nouveau_object_inc(struct nouveau_object *object)
{
	int ref = atomic_add_return(1, &object->usecount);
	int ret;

	nv_trace(object, "use(+1) == %d\n", atomic_read(&object->usecount));
	if (ref != 1)
		return 0;

	nv_trace(object, "initialising...\n");
	if (object->parent) {
		ret = nouveau_object_inc(object->parent);
		if (ret) {
			nv_error(object, "parent failed, %d\n", ret);
			goto fail_parent;
		}
	}

	if (object->engine) {
		mutex_lock(&nv_subdev(object->engine)->mutex);
		ret = nouveau_object_inc(object->engine);
		mutex_unlock(&nv_subdev(object->engine)->mutex);
		if (ret) {
			nv_error(object, "engine failed, %d\n", ret);
			goto fail_engine;
		}
	}

	ret = nv_ofuncs(object)->init(object);
	if (ret) {
		nv_error(object, "init failed, %d\n", ret);
		goto fail_self;
	}

	nv_debug(object, "initialised\n");
	return 0;

fail_self:
	if (object->engine) {
		mutex_lock(&nv_subdev(object->engine)->mutex);
		nouveau_object_dec(object->engine, false);
		mutex_unlock(&nv_subdev(object->engine)->mutex);
	}
fail_engine:
	if (object->parent)
		 nouveau_object_dec(object->parent, false);
fail_parent:
	atomic_dec(&object->usecount);
	return ret;
}