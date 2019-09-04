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
struct necp_session {int last_policy_id; } ;
typedef  scalar_t__ necp_policy_id ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NECPLOG0 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static necp_policy_id
necp_policy_get_new_id(struct necp_session *session)
{
	session->last_policy_id++;
	if (session->last_policy_id < 1) {
		session->last_policy_id = 1;
	}

	necp_policy_id newid = session->last_policy_id;

	if (newid == 0) {
		NECPLOG0(LOG_ERR, "Allocate policy id failed.\n");
		return (0);
	}

	return (newid);
}