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
struct msm_rpc_server {scalar_t__ flags; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ FLAG_REGISTERED ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_server_list ; 
 int /*<<< orphan*/  rpc_server_list_lock ; 
 int /*<<< orphan*/  rpc_server_register (struct msm_rpc_server*) ; 
 scalar_t__ rpc_servers_active ; 

int msm_rpc_create_server(struct msm_rpc_server *server)
{
	/* make sure we're in a sane state first */
	server->flags = 0;
	INIT_LIST_HEAD(&server->list);

	mutex_lock(&rpc_server_list_lock);
	list_add(&server->list, &rpc_server_list);
	if (rpc_servers_active) {
		rpc_server_register(server);
		server->flags |= FLAG_REGISTERED;
	}
	mutex_unlock(&rpc_server_list_lock);

	return 0;
}