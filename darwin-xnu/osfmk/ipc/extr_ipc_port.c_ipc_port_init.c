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
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  ipc_space_t ;
typedef  TYPE_1__* ipc_port_t ;
struct TYPE_4__ {int /*<<< orphan*/  ip_messages; int /*<<< orphan*/  ip_send_turnstile; int /*<<< orphan*/  ip_sync_link_state; scalar_t__ ip_specialreply; scalar_t__ ip_impcount; scalar_t__ ip_strict_guard; scalar_t__ ip_guarded; scalar_t__ ip_tempowner; scalar_t__ ip_impdonation; scalar_t__ ip_spimportant; scalar_t__ ip_sprequests; scalar_t__ ip_context; int /*<<< orphan*/  ip_premsg; int /*<<< orphan*/  ip_requests; void* ip_pdrequest; void* ip_nsrequest; scalar_t__ ip_sorights; scalar_t__ ip_srights; scalar_t__ ip_mscount; int /*<<< orphan*/  ip_receiver_name; int /*<<< orphan*/  ip_receiver; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IKM_NULL ; 
 int /*<<< orphan*/  IPR_NULL ; 
 void* IP_NULL ; 
 int /*<<< orphan*/  PORT_SYNC_LINK_ANY ; 
 int /*<<< orphan*/  TURNSTILE_NULL ; 
 int /*<<< orphan*/  ipc_mqueue_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_ip_srp_bits (TYPE_1__*) ; 

void
ipc_port_init(
	ipc_port_t		port,
	ipc_space_t		space,
	mach_port_name_t	name)
{
	/* port->ip_kobject doesn't have to be initialized */

	port->ip_receiver = space;
	port->ip_receiver_name = name;

	port->ip_mscount = 0;
	port->ip_srights = 0;
	port->ip_sorights = 0;

	port->ip_nsrequest = IP_NULL;
	port->ip_pdrequest = IP_NULL;
	port->ip_requests = IPR_NULL;

	port->ip_premsg = IKM_NULL;
	port->ip_context = 0;

	port->ip_sprequests  = 0;
	port->ip_spimportant = 0;
	port->ip_impdonation = 0;
	port->ip_tempowner   = 0;

	port->ip_guarded      = 0;
	port->ip_strict_guard = 0;
	port->ip_impcount    = 0;

	port->ip_specialreply = 0;
	port->ip_sync_link_state = PORT_SYNC_LINK_ANY;

	reset_ip_srp_bits(port);

	port->ip_send_turnstile = TURNSTILE_NULL;

	ipc_mqueue_init(&port->ip_messages,
			FALSE /* !set */);
}