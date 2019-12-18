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

/* Variables and functions */
 scalar_t__ in_own_cluster (int /*<<< orphan*/ ) ; 

void tipc_disc_link_event(u32 addr, char *name, int up)
{
	if (in_own_cluster(addr))
		return;
	/*
	 * Code for inter cluster link setup here
	 */
}