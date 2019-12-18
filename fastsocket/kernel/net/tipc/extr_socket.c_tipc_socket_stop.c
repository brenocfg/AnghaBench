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
struct TYPE_2__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  proto_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_unregister (int /*<<< orphan*/ ) ; 
 scalar_t__ sockets_enabled ; 
 TYPE_1__ tipc_family_ops ; 
 int /*<<< orphan*/  tipc_proto ; 

void tipc_socket_stop(void)
{
	if (!sockets_enabled)
		return;

	sockets_enabled = 0;
	sock_unregister(tipc_family_ops.family);
	proto_unregister(&tipc_proto);
}