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
struct nouveau_object {int dummy; } ;
struct nouveau_namedb {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct nouveau_handle {int /*<<< orphan*/  node; struct nouveau_namedb* namedb; int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_namedb_lookup (struct nouveau_namedb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_object_ref (struct nouveau_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

int
nouveau_namedb_insert(struct nouveau_namedb *namedb, u32 name,
		      struct nouveau_object *object,
		      struct nouveau_handle *handle)
{
	int ret = -EEXIST;
	write_lock_irq(&namedb->lock);
	if (!nouveau_namedb_lookup(namedb, name)) {
		nouveau_object_ref(object, &handle->object);
		handle->namedb = namedb;
		list_add(&handle->node, &namedb->list);
		ret = 0;
	}
	write_unlock_irq(&namedb->lock);
	return ret;
}