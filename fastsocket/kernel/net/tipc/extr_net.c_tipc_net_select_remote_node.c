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
struct tipc_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * zones; } ;

/* Variables and functions */
 TYPE_1__ tipc_net ; 
 size_t tipc_zone (int /*<<< orphan*/ ) ; 
 struct tipc_node* tipc_zone_select_remote_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct tipc_node *tipc_net_select_remote_node(u32 addr, u32 ref)
{
	return tipc_zone_select_remote_node(tipc_net.zones[tipc_zone(addr)], addr, ref);
}