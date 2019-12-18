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
struct net_bridge_port {int /*<<< orphan*/  br; int /*<<< orphan*/  path_cost; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_configuration_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_port_state_selection (int /*<<< orphan*/ ) ; 

void br_stp_set_path_cost(struct net_bridge_port *p, u32 path_cost)
{
	p->path_cost = path_cost;
	br_configuration_update(p->br);
	br_port_state_selection(p->br);
}