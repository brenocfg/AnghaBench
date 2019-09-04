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
struct necp_fd_data {scalar_t__ update_count; int /*<<< orphan*/  update_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  update_type; } ;
struct necp_client_update {int update_length; TYPE_1__ update; int /*<<< orphan*/  client_id; } ;
struct necp_client_observer_update {int dummy; } ;
struct necp_client {int /*<<< orphan*/  client_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NECP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NECP_CLIENT_UPDATE_TYPE_REMOVE ; 
 int /*<<< orphan*/  NECP_FD_LOCK (struct necp_fd_data*) ; 
 int /*<<< orphan*/  NECP_FD_UNLOCK (struct necp_fd_data*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct necp_client_update*,int /*<<< orphan*/ ) ; 
 struct necp_client_update* _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  necp_fd_notify (struct necp_fd_data*,int) ; 
 scalar_t__ necp_observer_message_limit ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
necp_client_update_observer_remove_internal(struct necp_fd_data *observer_fd, struct necp_client *client)
{
	NECP_FD_LOCK(observer_fd);

	if (observer_fd->update_count >= necp_observer_message_limit) {
		NECP_FD_UNLOCK(observer_fd);
		return;
	}

	struct necp_client_update *client_update = _MALLOC(sizeof(struct necp_client_update),
													   M_NECP, M_WAITOK | M_ZERO);
	if (client_update != NULL) {
		client_update->update_length = sizeof(struct necp_client_observer_update);
		uuid_copy(client_update->client_id, client->client_id);
		client_update->update.update_type = NECP_CLIENT_UPDATE_TYPE_REMOVE;
		TAILQ_INSERT_TAIL(&observer_fd->update_list, client_update, chain);
		observer_fd->update_count++;

		necp_fd_notify(observer_fd, true);
	}

	NECP_FD_UNLOCK(observer_fd);
}