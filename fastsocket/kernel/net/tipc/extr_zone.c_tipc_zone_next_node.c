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
struct cluster {int dummy; } ;

/* Variables and functions */
 struct cluster* tipc_cltr_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_cltr_next_node (struct cluster*,int /*<<< orphan*/ ) ; 

u32 tipc_zone_next_node(u32 addr)
{
	struct cluster *c_ptr = tipc_cltr_find(addr);

	if (c_ptr)
		return tipc_cltr_next_node(c_ptr, addr);
	return 0;
}