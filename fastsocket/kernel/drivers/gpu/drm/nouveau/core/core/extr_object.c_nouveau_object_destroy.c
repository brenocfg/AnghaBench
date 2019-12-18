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
struct nouveau_object {int /*<<< orphan*/  parent; int /*<<< orphan*/  engine; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  _objlist_lock ; 
 int /*<<< orphan*/  kfree (struct nouveau_object*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_object_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
nouveau_object_destroy(struct nouveau_object *object)
{
#ifdef NOUVEAU_OBJECT_MAGIC
	spin_lock(&_objlist_lock);
	list_del(&object->list);
	spin_unlock(&_objlist_lock);
#endif
	nouveau_object_ref(NULL, &object->engine);
	nouveau_object_ref(NULL, &object->parent);
	kfree(object);
}