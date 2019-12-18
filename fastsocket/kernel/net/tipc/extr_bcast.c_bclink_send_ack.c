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
struct tipc_node {int addr; struct link** active_links; } ;
struct link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_MSG ; 
 int /*<<< orphan*/  tipc_link_send_proto_msg (struct link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bclink_send_ack(struct tipc_node *n_ptr)
{
	struct link *l_ptr = n_ptr->active_links[n_ptr->addr & 1];

	if (l_ptr != NULL)
		tipc_link_send_proto_msg(l_ptr, STATE_MSG, 0, 0, 0, 0, 0);
}