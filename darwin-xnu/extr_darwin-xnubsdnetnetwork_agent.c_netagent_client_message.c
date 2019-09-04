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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int netagent_client_message_with_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
netagent_client_message(uuid_t agent_uuid, uuid_t necp_client_uuid, pid_t pid, void *handle, u_int8_t message_type)
{
	return (netagent_client_message_with_params(agent_uuid, necp_client_uuid, pid, handle, message_type, NULL, NULL, NULL));
}