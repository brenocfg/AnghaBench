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
struct nouveau_namedb {int /*<<< orphan*/  lock; } ;
struct nouveau_handle {int /*<<< orphan*/  node; struct nouveau_object* object; struct nouveau_namedb* namedb; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_object_ref (int /*<<< orphan*/ *,struct nouveau_object**) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

void
nouveau_namedb_remove(struct nouveau_handle *handle)
{
	struct nouveau_namedb *namedb = handle->namedb;
	struct nouveau_object *object = handle->object;
	write_lock_irq(&namedb->lock);
	list_del(&handle->node);
	write_unlock_irq(&namedb->lock);
	nouveau_object_ref(NULL, &object);
}