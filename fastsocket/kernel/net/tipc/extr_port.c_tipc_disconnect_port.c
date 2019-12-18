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
struct tipc_port {scalar_t__ connected; } ;
struct port {int /*<<< orphan*/  subscription; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int /*<<< orphan*/  tipc_nodesub_unsubscribe (int /*<<< orphan*/ *) ; 

int tipc_disconnect_port(struct tipc_port *tp_ptr)
{
	int res;

	if (tp_ptr->connected) {
		tp_ptr->connected = 0;
		/* let timer expire on it's own to avoid deadlock! */
		tipc_nodesub_unsubscribe(
			&((struct port *)tp_ptr)->subscription);
		res = 0;
	} else {
		res = -ENOTCONN;
	}
	return res;
}