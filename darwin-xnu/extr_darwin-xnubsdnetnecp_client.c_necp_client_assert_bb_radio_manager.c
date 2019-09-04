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
struct necp_client {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NECPLOG0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NECP_CLIENT_TREE_LOCK_SHARED () ; 
 int /*<<< orphan*/  NECP_CLIENT_TREE_UNLOCK () ; 
 int /*<<< orphan*/  NECP_CLIENT_UNLOCK (struct necp_client*) ; 
 int necp_client_assert_bb_radio_manager_common (struct necp_client*,int) ; 
 struct necp_client* necp_find_client_and_lock (int /*<<< orphan*/ ) ; 

int
necp_client_assert_bb_radio_manager(uuid_t client_id, bool assert)
{
	struct necp_client *client;
	int error = 0;

	NECP_CLIENT_TREE_LOCK_SHARED();

	client = necp_find_client_and_lock(client_id);

	if (client) {
		// Found the right client!
		error = necp_client_assert_bb_radio_manager_common(client, assert);

		NECP_CLIENT_UNLOCK(client);
	} else {
		NECPLOG0(LOG_ERR, "Couldn't find client");
		error = ENOENT;
	}

	NECP_CLIENT_TREE_UNLOCK();

	return (error);
}