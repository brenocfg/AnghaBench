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
struct inpcb {int /*<<< orphan*/  necp_client_uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  necp_client_unregister_socket_flow (int /*<<< orphan*/ ,struct inpcb*) ; 
 int /*<<< orphan*/  uuid_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_is_null (int /*<<< orphan*/ ) ; 

void
necp_inpcb_remove_cb(struct inpcb *inp)
{
	if (!uuid_is_null(inp->necp_client_uuid)) {
		necp_client_unregister_socket_flow(inp->necp_client_uuid, inp);
		uuid_clear(inp->necp_client_uuid);
	}
}