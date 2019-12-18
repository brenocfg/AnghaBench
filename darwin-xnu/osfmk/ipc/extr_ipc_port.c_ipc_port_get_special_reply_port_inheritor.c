#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  turnstile_inheritor_t ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_4__ {int ip_sync_link_state; int /*<<< orphan*/  ip_sync_inheritor_ts; int /*<<< orphan*/ * ip_sync_inheritor_port; int /*<<< orphan*/  ip_messages; int /*<<< orphan*/  ip_specialreply; } ;

/* Variables and functions */
#define  PORT_SYNC_LINK_PORT 130 
#define  PORT_SYNC_LINK_WORKLOOP_KNOTE 129 
#define  PORT_SYNC_LINK_WORKLOOP_STASH 128 
 int /*<<< orphan*/  TURNSTILE_INHERITOR_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filt_machport_stashed_special_reply_port_turnstile (TYPE_1__*) ; 
 int /*<<< orphan*/  imq_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_send_turnstile (int /*<<< orphan*/ *) ; 

turnstile_inheritor_t
ipc_port_get_special_reply_port_inheritor(
	ipc_port_t port)
{
	assert(port->ip_specialreply);
	imq_held(&port->ip_messages);

	switch (port->ip_sync_link_state) {
	case PORT_SYNC_LINK_PORT:
		if (port->ip_sync_inheritor_port != NULL) {
			return port_send_turnstile(port->ip_sync_inheritor_port);
		}
		break;
	case PORT_SYNC_LINK_WORKLOOP_KNOTE:
		return filt_machport_stashed_special_reply_port_turnstile(port);
	case PORT_SYNC_LINK_WORKLOOP_STASH:
		return port->ip_sync_inheritor_ts;
	}
	return TURNSTILE_INHERITOR_NULL;
}