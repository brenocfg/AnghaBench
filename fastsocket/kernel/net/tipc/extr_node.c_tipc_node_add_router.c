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
typedef  int u32 ;
struct tipc_node {int* routers; int last_router; } ;

/* Variables and functions */
 int tipc_max_nodes ; 
 int tipc_node (int) ; 

void tipc_node_add_router(struct tipc_node *n_ptr, u32 router)
{
	u32 r_num = tipc_node(router);

	n_ptr->routers[r_num / 32] =
		((1 << (r_num % 32)) | n_ptr->routers[r_num / 32]);
	n_ptr->last_router = tipc_max_nodes / 32;
	while ((--n_ptr->last_router >= 0) &&
	       !n_ptr->routers[n_ptr->last_router]);
}