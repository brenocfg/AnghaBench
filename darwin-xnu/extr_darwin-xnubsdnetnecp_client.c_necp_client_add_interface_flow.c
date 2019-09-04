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
typedef  int /*<<< orphan*/  uint32_t ;
struct necp_client_flow_registration {int /*<<< orphan*/  flow_list; int /*<<< orphan*/  interface_cb; int /*<<< orphan*/  interface_handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb; int /*<<< orphan*/  socket_handle; } ;
struct necp_client_flow {TYPE_1__ u; int /*<<< orphan*/  interface_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct necp_client_flow*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MCR_SLEEP ; 
 int /*<<< orphan*/  NECPLOG0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flow_chain ; 
 struct necp_client_flow* mcache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct necp_client_flow*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  necp_flow_cache ; 
 int /*<<< orphan*/  necp_if_flow_count ; 

__attribute__((used)) static struct necp_client_flow *
necp_client_add_interface_flow(struct necp_client_flow_registration *flow_registration,
							   uint32_t interface_index)
{
	struct necp_client_flow *new_flow = mcache_alloc(necp_flow_cache, MCR_SLEEP);
	if (new_flow == NULL) {
		NECPLOG0(LOG_ERR, "Failed to allocate interface flow");
		return NULL;
	}

	memset(new_flow, 0, sizeof(*new_flow));

	// Neither nexus nor socket
	new_flow->interface_index = interface_index;
	new_flow->u.socket_handle = flow_registration->interface_handle;
	new_flow->u.cb = flow_registration->interface_cb;

	OSIncrementAtomic(&necp_if_flow_count);

	LIST_INSERT_HEAD(&flow_registration->flow_list, new_flow, flow_chain);

	return new_flow;
}