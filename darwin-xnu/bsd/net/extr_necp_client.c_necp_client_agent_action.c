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
typedef  scalar_t__* uuid_t ;
typedef  scalar_t__ u_int8_t ;
typedef  size_t u_int32_t ;
struct necp_tlv_header {int dummy; } ;
struct necp_fd_data {int /*<<< orphan*/  proc_pid; } ;
struct necp_client_nexus_parameters {int dummy; } ;
struct necp_client_action_args {size_t buffer_size; scalar_t__ client_id; int client_id_len; scalar_t__ buffer; } ;
struct necp_client {int /*<<< orphan*/  agent_handle; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int FALSE ; 
 int /*<<< orphan*/  FREE (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  M_NECP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NECPLOG (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  NECPLOG0 (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ NECP_CLIENT_PARAMETER_ASSERT_AGENT ; 
 scalar_t__ NECP_CLIENT_PARAMETER_TRIGGER_AGENT ; 
 scalar_t__ NECP_CLIENT_PARAMETER_UNASSERT_AGENT ; 
 int /*<<< orphan*/  NECP_CLIENT_UNLOCK (struct necp_client*) ; 
 int /*<<< orphan*/  NECP_FD_LOCK (struct necp_fd_data*) ; 
 int /*<<< orphan*/  NECP_FD_UNLOCK (struct necp_fd_data*) ; 
 size_t NECP_MAX_AGENT_ACTION_SIZE ; 
 scalar_t__ NETAGENT_MESSAGE_TYPE_CLIENT_ASSERT ; 
 scalar_t__ NETAGENT_MESSAGE_TYPE_CLIENT_TRIGGER ; 
 scalar_t__ NETAGENT_MESSAGE_TYPE_CLIENT_UNASSERT ; 
 int TRUE ; 
 scalar_t__* _MALLOC (size_t,int /*<<< orphan*/ ,int) ; 
 int copyin (scalar_t__,scalar_t__*,int) ; 
 size_t necp_buffer_get_tlv_length (scalar_t__*,size_t) ; 
 scalar_t__ necp_buffer_get_tlv_type (scalar_t__*,size_t) ; 
 scalar_t__* necp_buffer_get_tlv_value (scalar_t__*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  necp_client_add_assertion (struct necp_client*,scalar_t__*) ; 
 int /*<<< orphan*/  necp_client_copy_parameters_locked (struct necp_client*,struct necp_client_nexus_parameters*) ; 
 struct necp_client* necp_client_fd_find_client_and_lock (struct necp_fd_data*,scalar_t__*) ; 
 int /*<<< orphan*/  necp_client_remove_assertion (struct necp_client*,scalar_t__*) ; 
 int netagent_client_message_with_params (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct necp_client_nexus_parameters*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uuid_copy (scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
necp_client_agent_action(struct necp_fd_data *fd_data, struct necp_client_action_args *uap, int *retval)
{
	int error = 0;
	struct necp_client *client = NULL;
	uuid_t client_id;
	bool acted_on_agent = FALSE;
	u_int8_t *parameters = NULL;
	size_t parameters_size = uap->buffer_size;

	if (uap->client_id == 0 || uap->client_id_len != sizeof(uuid_t) ||
		uap->buffer_size == 0 || uap->buffer == 0) {
		NECPLOG0(LOG_ERR, "necp_client_agent_action invalid parameters");
		error = EINVAL;
		goto done;
	}

	error = copyin(uap->client_id, client_id, sizeof(uuid_t));
	if (error) {
		NECPLOG(LOG_ERR, "necp_client_agent_action copyin client_id error (%d)", error);
		goto done;
	}

	if (uap->buffer_size > NECP_MAX_AGENT_ACTION_SIZE) {
		NECPLOG(LOG_ERR, "necp_client_agent_action invalid buffer size (>%u)", NECP_MAX_AGENT_ACTION_SIZE);
		error = EINVAL;
		goto done;
	}

	if ((parameters = _MALLOC(uap->buffer_size, M_NECP, M_WAITOK | M_ZERO)) == NULL) {
		NECPLOG0(LOG_ERR, "necp_client_agent_action malloc failed");
		error = ENOMEM;
		goto done;
	}

	error = copyin(uap->buffer, parameters, uap->buffer_size);
	if (error) {
		NECPLOG(LOG_ERR, "necp_client_agent_action parameters copyin error (%d)", error);
		goto done;
	}

	NECP_FD_LOCK(fd_data);
	client = necp_client_fd_find_client_and_lock(fd_data, client_id);
	if (client != NULL) {
		size_t offset = 0;
		while ((offset + sizeof(struct necp_tlv_header)) <= parameters_size) {
			u_int8_t type = necp_buffer_get_tlv_type(parameters, offset);
			u_int32_t length = necp_buffer_get_tlv_length(parameters, offset);

			if (length > (parameters_size - (offset + sizeof(struct necp_tlv_header)))) {
				// If the length is larger than what can fit in the remaining parameters size, bail
				NECPLOG(LOG_ERR, "Invalid TLV length (%u)", length);
				break;
			}

			if (length > 0) {
				u_int8_t *value = necp_buffer_get_tlv_value(parameters, offset, NULL);
				if (length >= sizeof(uuid_t) &&
					value != NULL &&
					(type == NECP_CLIENT_PARAMETER_TRIGGER_AGENT ||
					 type == NECP_CLIENT_PARAMETER_ASSERT_AGENT ||
					 type == NECP_CLIENT_PARAMETER_UNASSERT_AGENT)) {

						uuid_t agent_uuid;
						uuid_copy(agent_uuid, value);
						u_int8_t netagent_message_type = 0;
						if (type == NECP_CLIENT_PARAMETER_TRIGGER_AGENT) {
							netagent_message_type = NETAGENT_MESSAGE_TYPE_CLIENT_TRIGGER;
						} else if (type == NECP_CLIENT_PARAMETER_ASSERT_AGENT) {
							netagent_message_type = NETAGENT_MESSAGE_TYPE_CLIENT_ASSERT;
						} else if (type == NECP_CLIENT_PARAMETER_UNASSERT_AGENT) {
							netagent_message_type = NETAGENT_MESSAGE_TYPE_CLIENT_UNASSERT;
						}

						// Before unasserting, verify that the assertion was already taken
						if (type == NECP_CLIENT_PARAMETER_UNASSERT_AGENT) {
							if (!necp_client_remove_assertion(client, agent_uuid)) {
								error = ENOENT;
								break;
							}
						}

						struct necp_client_nexus_parameters parsed_parameters = {};
						necp_client_copy_parameters_locked(client, &parsed_parameters);

						error = netagent_client_message_with_params(agent_uuid,
																	client_id,
																	fd_data->proc_pid,
																	client->agent_handle,
																	netagent_message_type,
																	&parsed_parameters,
																	NULL, NULL);
						if (error == 0) {
							acted_on_agent = TRUE;
						} else {
							break;
						}

						// Only save the assertion if the action succeeded
						if (type == NECP_CLIENT_PARAMETER_ASSERT_AGENT) {
							necp_client_add_assertion(client, agent_uuid);
						}
					}
			}

			offset += sizeof(struct necp_tlv_header) + length;
		}

		NECP_CLIENT_UNLOCK(client);
	}
	NECP_FD_UNLOCK(fd_data);

	if (!acted_on_agent &&
		error == 0) {
		error = ENOENT;
	}
done:
	*retval = error;
	if (parameters != NULL) {
		FREE(parameters, M_NECP);
		parameters = NULL;
	}

	return (error);
}