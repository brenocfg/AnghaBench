#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct nouveau_object {int dummy; } ;
struct nouveau_client {int /*<<< orphan*/  debug; int /*<<< orphan*/  name; int /*<<< orphan*/  device; int /*<<< orphan*/  root; } ;
struct TYPE_4__ {int /*<<< orphan*/  usecount; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  NV_CLIENT_CLASS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nouveau_client_oclass ; 
 int /*<<< orphan*/  nouveau_dbgopt (char const*,char*) ; 
 scalar_t__ nouveau_device_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_device_sclass ; 
 int nouveau_handle_create (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int nouveau_namedb_create_ (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**) ; 
 int /*<<< orphan*/  nouveau_object_ref (struct nouveau_object*,int /*<<< orphan*/ *) ; 
 TYPE_1__* nv_object (struct nouveau_client*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 

int
nouveau_client_create_(const char *name, u64 devname, const char *cfg,
		       const char *dbg, int length, void **pobject)
{
	struct nouveau_object *device;
	struct nouveau_client *client;
	int ret;

	device = (void *)nouveau_device_find(devname);
	if (!device)
		return -ENODEV;

	ret = nouveau_namedb_create_(NULL, NULL, &nouveau_client_oclass,
				     NV_CLIENT_CLASS, nouveau_device_sclass,
				     0, length, pobject);
	client = *pobject;
	if (ret)
		return ret;

	ret = nouveau_handle_create(nv_object(client), ~0, ~0,
				    nv_object(client), &client->root);
	if (ret)
		return ret;

	/* prevent init/fini being called, os in in charge of this */
	atomic_set(&nv_object(client)->usecount, 2);

	nouveau_object_ref(device, &client->device);
	snprintf(client->name, sizeof(client->name), "%s", name);
	client->debug = nouveau_dbgopt(dbg, "CLIENT");
	return 0;
}