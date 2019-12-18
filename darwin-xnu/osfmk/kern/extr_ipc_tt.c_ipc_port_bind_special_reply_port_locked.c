#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* ipc_port_t ;
struct TYPE_8__ {int ip_specialreply; int /*<<< orphan*/  ip_sync_link_state; } ;
struct TYPE_7__ {TYPE_2__* ith_special_reply_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_SYNC_LINK_ANY ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  ip_reference (TYPE_2__*) ; 
 int /*<<< orphan*/  reset_ip_srp_bits (TYPE_2__*) ; 

__attribute__((used)) static void
ipc_port_bind_special_reply_port_locked(
	ipc_port_t port)
{
	thread_t thread = current_thread();
	assert(thread->ith_special_reply_port == NULL);

	ip_reference(port);
	thread->ith_special_reply_port = port;
	port->ip_specialreply = 1;
	port->ip_sync_link_state = PORT_SYNC_LINK_ANY;

	reset_ip_srp_bits(port);
}