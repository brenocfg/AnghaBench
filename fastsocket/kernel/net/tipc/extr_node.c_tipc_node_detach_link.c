#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tipc_node {int /*<<< orphan*/  link_cnt; int /*<<< orphan*/ ** links; } ;
struct link {int /*<<< orphan*/  addr; TYPE_1__* b_ptr; } ;
struct TYPE_6__ {TYPE_2__** zones; } ;
struct TYPE_5__ {int /*<<< orphan*/  links; } ;
struct TYPE_4__ {size_t identity; } ;

/* Variables and functions */
 TYPE_3__ tipc_net ; 
 size_t tipc_zone (int /*<<< orphan*/ ) ; 

void tipc_node_detach_link(struct tipc_node *n_ptr, struct link *l_ptr)
{
	n_ptr->links[l_ptr->b_ptr->identity] = NULL;
	tipc_net.zones[tipc_zone(l_ptr->addr)]->links--;
	n_ptr->link_cnt--;
}