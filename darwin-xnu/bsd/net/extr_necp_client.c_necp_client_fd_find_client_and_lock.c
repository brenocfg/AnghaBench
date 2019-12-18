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
typedef  int /*<<< orphan*/  uuid_t ;
struct necp_fd_data {int dummy; } ;
struct necp_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NECP_CLIENT_LOCK (struct necp_client*) ; 
 struct necp_client* necp_client_fd_find_client_unlocked (struct necp_fd_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct necp_client *
necp_client_fd_find_client_and_lock(struct necp_fd_data *client_fd, uuid_t client_id)
{
	struct necp_client *client = necp_client_fd_find_client_unlocked(client_fd, client_id);
	if (client != NULL) {
		NECP_CLIENT_LOCK(client);
	}

	return (client);
}