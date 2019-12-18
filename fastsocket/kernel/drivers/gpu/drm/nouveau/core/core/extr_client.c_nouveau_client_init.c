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
struct nouveau_client {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int nouveau_handle_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_debug (struct nouveau_client*,char*,...) ; 

int
nouveau_client_init(struct nouveau_client *client)
{
	int ret;
	nv_debug(client, "init running\n");
	ret = nouveau_handle_init(client->root);
	nv_debug(client, "init completed with %d\n", ret);
	return ret;
}