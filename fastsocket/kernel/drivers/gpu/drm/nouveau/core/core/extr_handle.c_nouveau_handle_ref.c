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
struct nouveau_object {struct nouveau_object* parent; } ;
struct nouveau_handle {int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_NAMEDB_CLASS ; 
 struct nouveau_handle* nouveau_namedb_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_namedb_put (struct nouveau_handle*) ; 
 int /*<<< orphan*/  nouveau_object_ref (int /*<<< orphan*/ ,struct nouveau_object**) ; 
 int /*<<< orphan*/  nv_iclass (struct nouveau_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_namedb (struct nouveau_object*) ; 

struct nouveau_object *
nouveau_handle_ref(struct nouveau_object *parent, u32 name)
{
	struct nouveau_object *object = NULL;
	struct nouveau_handle *handle;

	while (!nv_iclass(parent, NV_NAMEDB_CLASS))
		parent = parent->parent;

	handle = nouveau_namedb_get(nv_namedb(parent), name);
	if (handle) {
		nouveau_object_ref(handle->object, &object);
		nouveau_namedb_put(handle);
	}

	return object;
}