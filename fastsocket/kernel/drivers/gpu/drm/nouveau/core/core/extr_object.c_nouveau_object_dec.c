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
struct nouveau_object {int /*<<< orphan*/  usecount; } ;

/* Variables and functions */
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int nouveau_object_decf (struct nouveau_object*) ; 
 int nouveau_object_decs (struct nouveau_object*) ; 
 int /*<<< orphan*/  nv_trace (struct nouveau_object*,char*,int /*<<< orphan*/ ) ; 

int
nouveau_object_dec(struct nouveau_object *object, bool suspend)
{
	int ref = atomic_add_return(-1, &object->usecount);
	int ret;

	nv_trace(object, "use(-1) == %d\n", atomic_read(&object->usecount));

	if (ref == 0) {
		if (suspend)
			ret = nouveau_object_decs(object);
		else
			ret = nouveau_object_decf(object);

		if (ret) {
			atomic_inc(&object->usecount);
			return ret;
		}
	}

	return 0;
}