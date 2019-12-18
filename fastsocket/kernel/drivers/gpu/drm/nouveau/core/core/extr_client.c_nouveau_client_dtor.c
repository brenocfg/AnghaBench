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
struct nouveau_client {int /*<<< orphan*/  base; int /*<<< orphan*/  root; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_handle_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_namedb_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_object_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nouveau_client_dtor(struct nouveau_object *object)
{
	struct nouveau_client *client = (void *)object;
	nouveau_object_ref(NULL, &client->device);
	nouveau_handle_destroy(client->root);
	nouveau_namedb_destroy(&client->base);
}