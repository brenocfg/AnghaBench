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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_portid {int /*<<< orphan*/  node; int /*<<< orphan*/  ref; } ;
struct TYPE_2__ {scalar_t__ connected; } ;
struct port {TYPE_1__ publ; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  port_peernode (struct port*) ; 
 int /*<<< orphan*/  port_peerport (struct port*) ; 
 struct port* tipc_port_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_port_unlock (struct port*) ; 

int tipc_peer(u32 ref, struct tipc_portid *peer)
{
	struct port *p_ptr;
	int res;

	p_ptr = tipc_port_lock(ref);
	if (!p_ptr)
		return -EINVAL;
	if (p_ptr->publ.connected) {
		peer->ref = port_peerport(p_ptr);
		peer->node = port_peernode(p_ptr);
		res = 0;
	} else
		res = -ENOTCONN;
	tipc_port_unlock(p_ptr);
	return res;
}