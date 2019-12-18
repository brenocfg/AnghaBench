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
struct bearer {int /*<<< orphan*/  link_req; int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  tipc_bcbearer_sort () ; 
 int /*<<< orphan*/  tipc_disc_update_link_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_nmap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void tipc_bearer_add_dest(struct bearer *b_ptr, u32 dest)
{
	tipc_nmap_add(&b_ptr->nodes, dest);
	tipc_disc_update_link_req(b_ptr->link_req);
	tipc_bcbearer_sort();
}