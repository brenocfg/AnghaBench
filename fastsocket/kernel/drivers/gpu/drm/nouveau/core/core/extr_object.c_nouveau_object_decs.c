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
struct nouveau_object {scalar_t__ engine; scalar_t__ parent; } ;
struct TYPE_4__ {int (* fini ) (struct nouveau_object*,int) ;int (* init ) (struct nouveau_object*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nouveau_object_dec (scalar_t__,int) ; 
 int nouveau_object_inc (scalar_t__) ; 
 int /*<<< orphan*/  nv_debug (struct nouveau_object*,char*) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_object*,char*,int) ; 
 int /*<<< orphan*/  nv_fatal (struct nouveau_object*,char*,int) ; 
 TYPE_2__* nv_ofuncs (struct nouveau_object*) ; 
 TYPE_1__* nv_subdev (scalar_t__) ; 
 int /*<<< orphan*/  nv_trace (struct nouveau_object*,char*) ; 
 int /*<<< orphan*/  nv_warn (struct nouveau_object*,char*,int) ; 
 int stub1 (struct nouveau_object*,int) ; 
 int stub2 (struct nouveau_object*) ; 

__attribute__((used)) static int
nouveau_object_decs(struct nouveau_object *object)
{
	int ret, rret;

	nv_trace(object, "suspending...\n");

	ret = nv_ofuncs(object)->fini(object, true);
	if (ret) {
		nv_error(object, "failed suspend, %d\n", ret);
		return ret;
	}

	if (object->engine) {
		mutex_lock(&nv_subdev(object->engine)->mutex);
		ret = nouveau_object_dec(object->engine, true);
		mutex_unlock(&nv_subdev(object->engine)->mutex);
		if (ret) {
			nv_warn(object, "engine failed suspend, %d\n", ret);
			goto fail_engine;
		}
	}

	if (object->parent) {
		ret = nouveau_object_dec(object->parent, true);
		if (ret) {
			nv_warn(object, "parent failed suspend, %d\n", ret);
			goto fail_parent;
		}
	}

	nv_debug(object, "suspended\n");
	return 0;

fail_parent:
	if (object->engine) {
		mutex_lock(&nv_subdev(object->engine)->mutex);
		rret = nouveau_object_inc(object->engine);
		mutex_unlock(&nv_subdev(object->engine)->mutex);
		if (rret)
			nv_fatal(object, "engine failed to reinit, %d\n", rret);
	}

fail_engine:
	rret = nv_ofuncs(object)->init(object);
	if (rret)
		nv_fatal(object, "failed to reinit, %d\n", rret);

	return ret;
}