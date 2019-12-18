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
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_ofuncs {int (* ctor ) (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,void*,int /*<<< orphan*/ ,struct nouveau_object**) ;int /*<<< orphan*/  (* dtor ) (struct nouveau_object*) ;} ;
struct nouveau_oclass {int /*<<< orphan*/  handle; struct nouveau_ofuncs* ofuncs; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  nv_debug (struct nouveau_object*,char*) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_object*,char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,void*,int /*<<< orphan*/ ,struct nouveau_object**) ; 
 int /*<<< orphan*/  stub2 (struct nouveau_object*) ; 

int
nouveau_object_ctor(struct nouveau_object *parent,
		    struct nouveau_object *engine,
		    struct nouveau_oclass *oclass, void *data, u32 size,
		    struct nouveau_object **pobject)
{
	struct nouveau_ofuncs *ofuncs = oclass->ofuncs;
	int ret;

	*pobject = NULL;

	ret = ofuncs->ctor(parent, engine, oclass, data, size, pobject);
	if (ret < 0) {
		if (ret != -ENODEV) {
			nv_error(parent, "failed to create 0x%08x, %d\n",
				 oclass->handle, ret);
		}

		if (*pobject) {
			ofuncs->dtor(*pobject);
			*pobject = NULL;
		}

		return ret;
	}

	nv_debug(*pobject, "created\n");
	return 0;
}