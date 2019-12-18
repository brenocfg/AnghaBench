#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nouveau_object {int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm; } ;
struct nouveau_cli {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nouveau_client_fini (TYPE_1__*,int) ; 
 int /*<<< orphan*/  nouveau_object_ref (int /*<<< orphan*/ *,struct nouveau_object**) ; 
 int /*<<< orphan*/  nouveau_vm_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nouveau_object* nv_object (struct nouveau_cli*) ; 

__attribute__((used)) static void
nouveau_cli_destroy(struct nouveau_cli *cli)
{
	struct nouveau_object *client = nv_object(cli);
	nouveau_vm_ref(NULL, &cli->base.vm, NULL);
	nouveau_client_fini(&cli->base, false);
	atomic_set(&client->refcount, 1);
	nouveau_object_ref(NULL, &client);
}