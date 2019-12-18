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
struct nouveau_handle {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  NV_NAMEDB_CLASS ; 
 int /*<<< orphan*/  nouveau_handle_destroy (struct nouveau_handle*) ; 
 int /*<<< orphan*/  nouveau_handle_fini (struct nouveau_handle*,int) ; 
 struct nouveau_object* nouveau_handle_ref (struct nouveau_object*,int /*<<< orphan*/ ) ; 
 struct nouveau_handle* nouveau_namedb_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_namedb_put (struct nouveau_handle*) ; 
 int /*<<< orphan*/  nouveau_object_ref (int /*<<< orphan*/ *,struct nouveau_object**) ; 
 int /*<<< orphan*/  nv_namedb (struct nouveau_object*) ; 
 struct nouveau_object* nv_pclass (struct nouveau_object*,int /*<<< orphan*/ ) ; 

int
nouveau_object_del(struct nouveau_object *client, u32 _parent, u32 _handle)
{
	struct nouveau_object *parent = NULL;
	struct nouveau_object *namedb = NULL;
	struct nouveau_handle *handle = NULL;

	parent = nouveau_handle_ref(client, _parent);
	if (!parent)
		return -ENOENT;

	namedb = nv_pclass(parent, NV_NAMEDB_CLASS);
	if (namedb) {
		handle = nouveau_namedb_get(nv_namedb(namedb), _handle);
		if (handle) {
			nouveau_namedb_put(handle);
			nouveau_handle_fini(handle, false);
			nouveau_handle_destroy(handle);
		}
	}

	nouveau_object_ref(NULL, &parent);
	return handle ? 0 : -EINVAL;
}