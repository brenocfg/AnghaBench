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
struct tipc_node {scalar_t__* active_links; } ;

/* Variables and functions */

int tipc_node_has_active_links(struct tipc_node *n_ptr)
{
	return (n_ptr &&
		((n_ptr->active_links[0]) || (n_ptr->active_links[1])));
}