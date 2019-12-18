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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct cluster {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROUTE_REMOVAL ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_set_remote_node (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_type (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_cltr_multicast (struct cluster*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* tipc_cltr_prepare_routing_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

void tipc_cltr_bcast_lost_route(struct cluster *c_ptr, u32 dest,
				u32 lower, u32 upper)
{
	struct sk_buff *buf = tipc_cltr_prepare_routing_msg(0, c_ptr->addr);
	struct tipc_msg *msg;

	if (buf) {
		msg = buf_msg(buf);
		msg_set_remote_node(msg, dest);
		msg_set_type(msg, ROUTE_REMOVAL);
		tipc_cltr_multicast(c_ptr, buf, lower, upper);
	} else {
		warn("Memory squeeze: broadcast of lost route failed\n");
	}
}