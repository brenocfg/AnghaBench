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
struct necp_client {int /*<<< orphan*/  lock; int /*<<< orphan*/  route_lock; struct necp_client* extra_interface_options; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct necp_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NECP ; 
 int /*<<< orphan*/  NECP_CLIENT_ASSERT_LOCKED (struct necp_client*) ; 
 int /*<<< orphan*/  NECP_CLIENT_UNLOCK (struct necp_client*) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  necp_fd_mtx_grp ; 

__attribute__((used)) static void
necp_client_free(struct necp_client *client)
{
	NECP_CLIENT_ASSERT_LOCKED(client);

	NECP_CLIENT_UNLOCK(client);

	FREE(client->extra_interface_options, M_NECP);
	client->extra_interface_options = NULL;

	lck_mtx_destroy(&client->route_lock, necp_fd_mtx_grp);
	lck_mtx_destroy(&client->lock, necp_fd_mtx_grp);

	FREE(client, M_NECP);
}