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
struct necp_client_flow_registration {int /*<<< orphan*/  interface_cb; struct mppcb* interface_handle; } ;
struct necp_client {int /*<<< orphan*/  proc_pid; } ;
struct mppcb {int /*<<< orphan*/  necp_cb; } ;
typedef  scalar_t__ proc_t ;

/* Variables and functions */
 scalar_t__ PROC_NULL ; 
 int /*<<< orphan*/  necp_flow_add_interface_flows (scalar_t__,struct necp_client*,struct necp_client_flow_registration*,int) ; 
 scalar_t__ proc_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_rele (scalar_t__) ; 

__attribute__((used)) static void
necp_client_add_multipath_interface_flows(struct necp_client_flow_registration *flow_registration,
										  struct necp_client *client,
										  struct mppcb *mpp)
{
	flow_registration->interface_handle = mpp;
	flow_registration->interface_cb = mpp->necp_cb;

	proc_t proc = proc_find(client->proc_pid);
	if (proc == PROC_NULL) {
		return;
	}

	// Traverse all interfaces and add a tracking flow if needed
	necp_flow_add_interface_flows(proc, client, flow_registration, true);

	proc_rele(proc);
	proc = PROC_NULL;
}