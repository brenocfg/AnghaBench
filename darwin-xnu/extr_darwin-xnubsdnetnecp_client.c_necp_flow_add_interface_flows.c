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
typedef  size_t u_int32_t ;
struct necp_client_interface_option {int /*<<< orphan*/  interface_index; } ;
struct necp_client_flow_registration {int /*<<< orphan*/  interface_handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct necp_client_flow {int viable; int /*<<< orphan*/  necp_flow_flags; int /*<<< orphan*/  interface_index; TYPE_1__ u; } ;
struct necp_client {size_t interface_option_count; struct necp_client_interface_option* extra_interface_options; struct necp_client_interface_option* interface_options; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  NECP_CLIENT_CBACTION_INITIAL ; 
 size_t NECP_CLIENT_INTERFACE_OPTION_STATIC_COUNT ; 
 struct necp_client_flow* necp_client_add_interface_flow_if_needed (struct necp_client*,struct necp_client_flow_registration*,int /*<<< orphan*/ ) ; 
 void* necp_client_flow_is_viable (int /*<<< orphan*/ ,struct necp_client*,struct necp_client_flow*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
necp_flow_add_interface_flows(proc_t proc,
							  struct necp_client *client,
							  struct necp_client_flow_registration *flow_registration,
							  bool send_initial)
{
	// Traverse all interfaces and add a tracking flow if needed
	for (u_int32_t option_i = 0; option_i < client->interface_option_count; option_i++) {
		if (option_i < NECP_CLIENT_INTERFACE_OPTION_STATIC_COUNT) {
			struct necp_client_interface_option *option = &client->interface_options[option_i];
			struct necp_client_flow *flow = necp_client_add_interface_flow_if_needed(client, flow_registration, option->interface_index);
			if (flow != NULL && send_initial) {
				flow->viable = necp_client_flow_is_viable(proc, client, flow);
				if (flow->viable && flow->u.cb) {
					bool viable = flow->viable;
					flow->u.cb(flow_registration->interface_handle, NECP_CLIENT_CBACTION_INITIAL, flow->interface_index, flow->necp_flow_flags, &viable);
					flow->viable = viable;
				}
			}
		} else {
			struct necp_client_interface_option *option = &client->extra_interface_options[option_i - NECP_CLIENT_INTERFACE_OPTION_STATIC_COUNT];
			struct necp_client_flow *flow = necp_client_add_interface_flow_if_needed(client, flow_registration, option->interface_index);
			if (flow != NULL && send_initial) {
				flow->viable = necp_client_flow_is_viable(proc, client, flow);
				if (flow->viable && flow->u.cb) {
					bool viable = flow->viable;
					flow->u.cb(flow_registration->interface_handle, NECP_CLIENT_CBACTION_INITIAL, flow->interface_index, flow->necp_flow_flags, &viable);
					flow->viable = viable;
				}
			}
		}
	}
}