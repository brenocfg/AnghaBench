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
struct nouveau_oclass {int /*<<< orphan*/  handle; } ;
struct nouveau_object {int /*<<< orphan*/  list; int /*<<< orphan*/  _magic; int /*<<< orphan*/  usecount; int /*<<< orphan*/  refcount; struct nouveau_oclass* oclass; int /*<<< orphan*/  engine; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NOUVEAU_OBJECT_MAGIC ; 
 int /*<<< orphan*/  _objlist ; 
 int /*<<< orphan*/  _objlist_lock ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_object_ref (struct nouveau_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int
nouveau_object_create_(struct nouveau_object *parent,
		       struct nouveau_object *engine,
		       struct nouveau_oclass *oclass, u32 pclass,
		       int size, void **pobject)
{
	struct nouveau_object *object;

	object = *pobject = kzalloc(size, GFP_KERNEL);
	if (!object)
		return -ENOMEM;

	nouveau_object_ref(parent, &object->parent);
	nouveau_object_ref(engine, &object->engine);
	object->oclass = oclass;
	object->oclass->handle |= pclass;
	atomic_set(&object->refcount, 1);
	atomic_set(&object->usecount, 0);

#ifdef NOUVEAU_OBJECT_MAGIC
	object->_magic = NOUVEAU_OBJECT_MAGIC;
	spin_lock(&_objlist_lock);
	list_add(&object->list, &_objlist);
	spin_unlock(&_objlist_lock);
#endif
	return 0;
}